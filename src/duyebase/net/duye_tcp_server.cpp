/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_tcp_server.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-03-29
* @note 
*
* 1. 2016-03-29 duye Created this file
*/

#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_buffer.h>
#include <duye_tcp_server.h>

#define RECV_BUF_MAX_SIZE 4096

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.system.tcpserver";
    
TcpServer::TcpServer() : NetServer("TcpServer"), m_tcpServerUser(NULL) {}
TcpServer::~TcpServer() {}

bool TcpServer::initServer(TcpServerIf* user)
{
    NetServerPara serverPara;
    return initServer(serverPara, user);
}

bool TcpServer::initServer(const NetServerPara& serverPara, TcpServerIf* user)
{
    DUYE_INFO("start TcpServer::initServer");

    if (user == NULL)
        return false;
    
    if (serverStatus() != SERVER_UNINIT)
    {
        DUYE_WARN("server isn't SERVER_UNINIT status, ready to stoped server");
        if (!stopServer())
        {
            DUYE_ERROR("stopServer failed");
            return false;
        }
    }

	if (serverPara.recvBufSize > RECV_BUF_MAX_SIZE) {
        DUYE_ERROR("recvBufSize too large, setting 1 ~ %d, please.", RECV_BUF_MAX_SIZE);
        return false;
	}

    m_tcpServerUser = user;
    m_serverPara = serverPara;
    setServerStatus(SERVER_INIT);
    DUYE_INFO("TcpServer::initServer [ok]");
    
    return true;
}

bool TcpServer::startServer()
{
    DUYE_INFO("start TcpServer::startServer");
    
    if (serverStatus() != SERVER_INIT)
    {
        DUYE_ERROR("hcn server status isn't SERVER_INIT");
        return false;
    }
    
    if (!m_socket.open(IPPROTO_TCP, m_serverPara.localDevName, m_serverPara.isBlock))
    {
        DUYE_ERROR("open socket failed.");
        return false;
    }

    if (!m_serverPara.bindAddr.empty())
    {
        m_ipv4Addr.setIp(NetHelper::ipToInt(m_serverPara.bindAddr));
    }
    else if (!m_serverPara.localDevName.empty())
    {
        std::string ipAddr;
        if (!System::getIPAddrByDevName(m_serverPara.localDevName, ipAddr))
        {
            DUYE_ERROR("getIPAddrByDevName(%s) failed", m_serverPara.localDevName.c_str());
            return false;
        }

        DUYE_DEBUG("getIPAddrByDevName(%s) = %s", m_serverPara.localDevName.c_str(), ipAddr.c_str());
        m_ipv4Addr.setIp(NetHelper::ipToInt(ipAddr));
    }
    else
    {
        std::string ipAddr;
        if (!System::getFirstValidIPAddr(ipAddr))
        {
            DUYE_ERROR("getFirstValidIPAddr(%s) failed");
            return false;
        }

        if (ipAddr.empty())
        {
            DUYE_ERROR("getFirstValidIPAddr() is empty");
            return false;
        }

        DUYE_DEBUG("getFirstValidIPAddr() = %s", ipAddr.c_str());
        m_ipv4Addr.setIp(NetHelper::ipToInt(ipAddr));  
    }       

    DUYE_INFO("tcp service ip address is '%s'", m_ipv4Addr.ipStr());

    if (m_serverPara.port == 0)
    {
        DUYE_ERROR("tcp server port is 0");
        return false;
    } 

    DUYE_INFO("tcp service port is %d", m_serverPara.port);
    
    m_ipv4Addr.setPort(m_serverPara.port);
    
    bool ret = Transfer::bind(m_socket.sockfd(), (const struct sockaddr*)&m_ipv4Addr.addr(), m_ipv4Addr.addrLen());
    if (!ret)
    {
        DUYE_ERROR("bind socket failed, address:%s:%d", m_ipv4Addr.ipStr(), m_ipv4Addr.port());
        return false;       
    }
    
    ret = Transfer::listen(m_socket.sockfd(), m_serverPara.maxConn);
    if (!ret)
    {
        DUYE_ERROR("listen socket failed.");
        return false;           
    }

    if (!m_hcnServer.initServer(m_serverPara.maxConn))
        return false;

    if (!m_hcnServer.startServer())
        return false;   

    if (!m_hcnServer.registerListener(m_socket.sockfd(), this))
        return false;
        
    setServerStatus(SERVER_RUNNING);
    DUYE_INFO("TcpServer::startServer [ok]");
    
    return true;
}

bool TcpServer::stopServer()
{
    bool ret = m_socket.close();   
    ret = ret & m_hcnServer.stopServer();
    setServerStatus(SERVER_STOPED);
	DUYE_INFO("TcpServer.stopServer [OK]");
    
	return ret;
}

const IPv4Addr& TcpServer::ipv4Addr()
{
    return m_ipv4Addr;
}

bool TcpServer::registerListener(const int32 sockfd, HcnServerListener* listener) {
	return m_hcnServer.registerListener(sockfd, listener);
}

int64 TcpServer::send(const int32 clientSockfd, const int8* data, const uint64 len)
{
    return Transfer::send(clientSockfd, data, len, MSG_NOSIGNAL);
}

bool TcpServer::onNetEvent(HcnEvent* event)
{
    if (event == NULL)
        return false;

    DUYE_DEBUG("received net event, sockfd=%d", event->fd());
	if (event->fd() == m_socket.sockfd() && event->type() == RECV_FD)
	{
        return acceptClient();
	}

    switch (event->type())
    {
    case RECV_FD:
        readData(event);
        break;
    case SEND_FD:
        //writeData(event);
        break;
    case ERROR_FD:
        DUYE_WARN("socket error, fd = %d", event->fd());
        return false;
        break;
    default:
        DUYE_ERROR("unknown event type=%d sockfd=%d", event->type(), event->fd());
        return false;
        break;
    }

    return true;
}

bool TcpServer::acceptClient()
{
    //AutoLock autoLock(m_acceptMutex);
    
    DUYE_INFO("received client connection");
    
    IPv4Addr clientAddr;
    int32 clientSockfd = -1;
    if (!accept(clientAddr, clientSockfd))
    {
        DUYE_WARN("m_tcpServer.accept() failed.");   
        return false;
    }

    DUYE_INFO("accept client : %s:%d sockfd=%d", clientAddr.ipStr(), clientAddr.port(), clientSockfd);

	// add client socket to hcn server
    if (!m_hcnServer.registerListener(clientSockfd, this))
    {
        DUYE_ERROR("m_hcnServer.registerListener() failed.");
        return false;
    }

	return m_tcpServerUser->onNewcon(clientAddr, clientSockfd);
}

bool TcpServer::readData(HcnEvent* event)
{
    DUYE_DEBUG("received read event, sockfd=%d", event->fd());
    
    //AutoLock autoLock(m_readMutex);
    Buffer buffer(m_serverPara.recvBufSize);
    int64 msgLen = recv(event->fd(), buffer.data(), m_serverPara.recvBufSize);
    if (msgLen < 0)
    {
        DUYE_ERROR("Transfer::recv() failed : size = %d", msgLen);
        return false;
    }
    else if (msgLen == 0)
    {
        DUYE_WARN("sockfd=%d disconnected", event->fd());
        return m_tcpServerUser->onDiscon(event->fd());
    }

	buffer.setSize(msgLen);

    DUYE_TRACE("Transfer::recv() data : size = %d, content >>>> \n%s\n", msgLen, buffer.data());

    return m_tcpServerUser->onRecved(event->fd(), buffer.data(), buffer.size());
}

bool TcpServer::accept(IPv4Addr& clientAddr,  int32& clientSockfd, const bool isBlock)
{
    clientSockfd = Transfer::accept(m_socket.sockfd(), (struct sockaddr*)&clientAddr.addr(), clientAddr.addrLen(), isBlock);
    return clientSockfd > 0 ? true : false;
}

int64 TcpServer::recv(int32 clientSockfd, int8* buffer, const uint64 size, const bool isBlock)
{
    if (isBlock)
    {
    	return Transfer::recv(clientSockfd, buffer, size);
    }
    else
    {
    	return Transfer::recv(clientSockfd, buffer, size, MSG_DONTWAIT);
    }
    
    return -1;	
}

}

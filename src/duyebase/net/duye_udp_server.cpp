/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_udp_server.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-03-31
* @note 
*
* 1. 2016-03-31 duye Created this file
*/

#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_udp_server.h>

static const int8* DUYE_LOG_PREFIX = "duye.system.udpserver";

namespace duye {
    
UdpServer::UdpServer() : NetServer("UdpServer") {}
UdpServer::~UdpServer() {}

bool UdpServer::initServer(const NetServerPara& serverPara)
{
    if (serverStatus() != SERVER_UNINIT)
    {
        DUYE_WARN("server isn't SERVER_UNINIT status, ready to stoped server");
        if (!stopServer())
        {
            DUYE_ERROR("stopServer failed");
            return false;
        }
    }    
      
    m_serverPara = serverPara;
    setServerStatus(SERVER_INIT);
    
    return true;
}

bool UdpServer::startServer()
{
    if (serverStatus() != SERVER_INIT)
    {
        DUYE_ERROR("hcn server status isn't SERVER_INIT");
        return false;        
    }
        
    if (!m_socket.open(IPPROTO_UDP, m_serverPara.localDevName, m_serverPara.isBlock))
    {
        DUYE_ERROR(DUYE_LOG_PREFIX, "open socket failed.");
        return false;
    }

    m_ipv4Addr.setIp(NetHelper::ipToInt(m_serverPara.bindAddr));
    m_ipv4Addr.setPort(m_serverPara.port);    
    bool ret = ::bind(m_socket.sockfd(), (const struct sockaddr*)&m_ipv4Addr.addr(), m_ipv4Addr.addrLen()) < 0 ? false : true;
    if (!ret)
    {
        DUYE_ERROR(DUYE_LOG_PREFIX, "bind socket failed.");
        return false;       
    }

    setServerStatus(SERVER_RUNNING);
    
    return true;
}

bool UdpServer::stopServer()
{
    setServerStatus(SERVER_STOPED);
    return m_socket.close();    	
}

const IPv4Addr& UdpServer::ipv4Addr()
{
    return m_ipv4Addr;
}

int64 UdpServer::recvfrom(IPv4Addr& srcAddr, int8* buffer, const uint64 size, const bool isBlock)
{
    if (isBlock)
    {
    	return Transfer::recvfrom(m_socket.sockfd(), srcAddr, buffer, size);
    }
    else
    {
    	return Transfer::recvfrom(m_socket.sockfd(), srcAddr, buffer, size, MSG_DONTWAIT);
    }
    
    return -1;	
}

int64 UdpServer::sendto(IPv4Addr& dstAddr, const int8* data, const uint64 len)
{
    return Transfer::sendto(m_socket.sockfd(), dstAddr, data, len, MSG_NOSIGNAL);	
}

}

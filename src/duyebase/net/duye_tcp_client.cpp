/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_tcp_client.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-05
* @note 
*
* 1. 2016-04-05 duye Created this file
*/

#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_net_rw.h>
#include <duye_tcp_client.h>

static const int8* DUYE_LOG_PREFIX = "duye.system.tcpclient";

namespace duye {
    
TcpClient::TcpClient() : m_con_status(false) {}
TcpClient::~TcpClient() { disconnect(); }

bool TcpClient::connect(const std::string& serverIP, const uint16 serverPort, const uint32 timeout)
{
	if (m_con_status) {
		return true;
	}
	
    m_serverIpv4Addr.setIp(NetHelper::ipToInt(serverIP));
    m_serverIpv4Addr.setPort(serverPort);

    if (!m_clientSocket.isOpen())
    {
        if (!m_clientSocket.open(IPPROTO_TCP, false))
        {
            DUYE_ERROR("m_clientSocket.open() failed:%s");
            return false;
        }
    }

	uint32 times = 3;
    uint32 cycleTime = timeout / times; // millisecond
    for (uint32 i = 0; i < times; i++)
    {
        if (Transfer::connect(m_clientSocket.sockfd(), (const struct sockaddr*)&m_serverIpv4Addr.addr(), m_serverIpv4Addr.addrLen()))
        {
			m_con_status = true;
            return true;
        }    

		if (cycleTime) {
        	System::msleep(cycleTime);
		}
    }
	
	m_clientSocket.close();
    DUYE_ERROR("connect() failed");
    
    return false;
}

bool TcpClient::disconnect()
{
	if (!m_con_status) {
		return true;
	}

	bool ret = m_clientSocket.close();
	
	m_con_status = false;
	
    return ret;
}

int64 TcpClient::recv(Buffer& buffer, const bool isBlock)
{    
    NetRW::NetRWStatus status;
    int64 bytes = NetRW::read(m_clientSocket.sockfd(), buffer, status, isBlock);
    if (status == NetRW::RD_FINISHED) {
        return bytes;
    }

    if (status == NetRW::RD_OVERFLOW) {
        DUYE_ERROR("recv buffer size(%d) too small", buffer.capacity());
    } else if (status == NetRW::FD_CLOSEED) {
        DUYE_WARN("socket fd close");
        NetRW::close(m_clientSocket.sockfd());
        return 0;
    } else {
        DUYE_ERROR("recv other error");
    }

    return -1;
}

int64 TcpClient::recv(int8* buffer, const uint32 size, const bool isBlock)
{    
    NetRW::NetRWStatus status;
    int64 bytes = NetRW::read(m_clientSocket.sockfd(), buffer, size, status, isBlock);
    if (status == NetRW::RD_FINISHED) {
        return bytes;
    }

    if (status == NetRW::RD_OVERFLOW) {
        DUYE_ERROR("recv buffer size(%d) too small", size);
    } else if (status == NetRW::FD_CLOSEED) {
        DUYE_WARN("socket fd close");
        NetRW::close(m_clientSocket.sockfd());
        return 0;
    } else {
        DUYE_ERROR("recv other error");
    }

    return -1;
}

int64 TcpClient::send(const Buffer& buffer)
{
    NetRW::NetRWStatus status;
    int64 bytes = NetRW::write(m_clientSocket.sockfd(), buffer, status);
    if (status == NetRW::WR_FINISHED) {
        return bytes;
    } 

    if (status == NetRW::FD_CLOSEED) {
        DUYE_WARN("socket fd closed");
        NetRW::close(m_clientSocket.sockfd());
    } else {
        DUYE_WARN("NetRW::write() other unknown error");
    }

    return -1;
}

int64 TcpClient::send(const int8* data, const uint32 len)
{
    NetRW::NetRWStatus status;
    int64 bytes = NetRW::write(m_clientSocket.sockfd(), data, len, status);
    if (status == NetRW::WR_FINISHED) {
        return bytes;
    } 

    if (status == NetRW::FD_CLOSEED) {
        DUYE_WARN("socket fd closed");
        NetRW::close(m_clientSocket.sockfd());
    } else {
        DUYE_WARN("NetRW::write() other unknown error");
    }

    return -1;
}

const IPv4Addr& TcpClient::ipv4Addr()
{
    return m_serverIpv4Addr;
}

const Socket& TcpClient::socket()
{
    return m_clientSocket;
}

bool TcpClient::isCon() {
	return m_con_status;
}

}

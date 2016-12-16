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
#include <duye_tcp_client.h>

static const int8* DUYE_LOG_PREFIX = "duye.system.tcpclient";

namespace duye {
    
TcpClient::TcpClient() {}
TcpClient::~TcpClient() { disconnect(); }

bool TcpClient::connect(const std::string& serverIP, const uint16 serverPort, const uint32 timeout)
{
    m_serverIpv4Addr.setIp(NetHelper::ipToInt(serverIP));
    m_serverIpv4Addr.setPort(serverPort);

    if (!m_clientSocket.isOpen())
    {
        if (!m_clientSocket.open(IPPROTO_TCP))
        {
            DUYE_ERROR("m_clientSocket.open() failed:%s");
            return false;
        }
    }

    uint32 cycleTime = 100; // millisecond
    uint32 cycleTimes = timeout / 100;
    for (uint32 i = 0; i < cycleTimes; i++)
    {
        if (Transfer::connect(m_clientSocket.sockfd(), (const struct sockaddr*)&m_serverIpv4Addr.addr(), m_serverIpv4Addr.addrLen()))
        {
            return true;    
        }    

        System::msleep(cycleTime);  
    }

    DUYE_ERROR("connect() failed");
    
    return false;
}

bool TcpClient::disconnect()
{
    return m_clientSocket.close();
}

int64 TcpClient::recv(int8* buffer, const uint64 size, const bool isBlock)
{
    if (isBlock)
    {
    	return Transfer::recv(m_clientSocket.sockfd(), buffer, size);
    }
    else
    {
    	return Transfer::recv(m_clientSocket.sockfd(), buffer, size, MSG_DONTWAIT);
    }
    
    return -1;	
}

int64 TcpClient::send(const int8* data, const uint64 len)
{
    return Transfer::send(m_clientSocket.sockfd(), data, len, MSG_NOSIGNAL);	
}

const IPv4Addr& TcpClient::ipv4Addr()
{
    return m_serverIpv4Addr;
}

const Socket& TcpClient::socket()
{
    return m_clientSocket;
}

}

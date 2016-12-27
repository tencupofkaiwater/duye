/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_tcp_client.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-05
* @note 
*
* 1. 2016-04-05 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_socket.h>
#include <duye_buffer.h>

#define TCP_DATA_BUFFER_SIZE 2048

namespace duye {

/** 
 * @brief tcp client socket class
 */
class TcpClient 
{
public:
    TcpClient();
    ~TcpClient();
   
    /**
     * @brief connect to server
     * @param [out] serverIP : server ip address
     * @param [out] serverPort : server port
     * @param [in] timeout : connect timeout, default is 0, indicate return immediately, millisecond
     * @return true/false
     */
    bool connect(const std::string& serverIP, const uint16 serverPort, const uint32 timeout = 0);
    bool disconnect();

    /**
     * @brief receive data
     * @param [out] buffer : output buffer
     * @param [in] bufferSize : buffer size
     * @param [in] isBlock : block or unblock, default block
     * @return size/-1
     * @note 
     */	
    int64 recv(Buffer& buffer, const bool isBlock = false);
    int64 recv(int8* buffer, const uint32 size, const bool isBlock = false);
    
    /**
     * @brief send data
     * @param [in] data : send data
     * @param [in] len : data length
     * @return size/-1
     * @note 
     */		
    int64 send(const Buffer& buffer);
    int64 send(const int8* data, const uint32 len);

    /**
     * @brief get server IPv4 address
     * @return IPv4 address
     */
    const IPv4Addr& ipv4Addr();

    /**
     * @brief get server socket
     * @return socket
     */
    const Socket& socket();

	bool isCon();

private:
    Socket   m_clientSocket;
    IPv4Addr m_serverIpv4Addr;
	bool     m_con_status;
};

}

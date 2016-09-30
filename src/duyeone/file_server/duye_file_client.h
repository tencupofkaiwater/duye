/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_client.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-05
* @note 
*
* 1. 2016-04-05 duye Created this file
*/

#pragma once

#include <string>
#include <duye_type.h>
#include <duye_tcp_client.h>

namespace duye {

/**
 * @brief network file client
 */
class FileClient
{
public:
    FileClient();
    ~FileClient();    

    /**
     * @brief connect server
     * @param [in] serverIP : server ip address
     * @param [in] serverPort : server port
     * @return : true/false
     */
    bool connect(const std::string& serverIP, const uint16 serverPort);
    
    /**
     * @brief receive data
     * @param [out] buffer : output buffer
     * @param [in] bufferSize : buffer size
     * @param [in] isBlock : block or unblock, default block
     * @return size/-1
     * @note 
     */	
    int64 recv(int8* buffer, const uint64 size, const bool isBlock = true); 
    
    /**
     * @brief send data
     * @param [in] data : send data
     * @param [in] len : data length
     * @return size/-1
     * @note 
     */		
    int64 send(const int8* data, const uint64 len);

private:
    TcpClient  m_tcpClient;
    std::string     m_serverIP;
    uint16          m_serverPort;
    bool            m_isConnected;
};
}

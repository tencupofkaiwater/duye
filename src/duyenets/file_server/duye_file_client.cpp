/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_client.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-05
* @note 
*
* 1. 2016-04-05 duye Created this file
*/

#include <string>
#include <duye_logger.h>
#include <duye_file_client.h>

static const int8* DUYE_LOG_PREFIX = "duye.nets.file.client";

namespace duye {
    
FileClient::FileClient() : m_serverPort(0), m_isConnected(false) {}
FileClient::~FileClient() {}

bool FileClient::connect(const std::string& serverIP, const uint16 serverPort)
{   
    // millisecond
    const uint32 timeout = 10000;
    if (!m_tcpClient.connect(serverIP, serverPort, timeout))
    {
        DUYE_ERROR("m_tcpClient.connect() failed");
        return false;
    }

    return true;
}

int64 FileClient::recv(int8* buffer, const uint64 size, const bool isBlock)
{
    int64 recvSize = -1;

    
    return recvSize;    
}
  
int64 FileClient::send(const int8* data, const uint64 len)
{
    int64 sendSize = -1;
    
    return sendSize;
}

}

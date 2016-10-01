/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_transfer.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-01
* @note 
*
* 1. 2016-04-01 duye Created this file
*/

#pragma once

#include <map>
#include <string>
#include <duye_type.h>
#include <duye_socket.h>
#include <duye_file_stream.h>
#include <duye_hcn_server.h>

namespace duye {

// transfer temp message buffer 10K
static const uint32 TRANSFER_TEMP_BUF_SIZE = 10 * 1024; 

/**
 * @brief transfer status
 */
typedef enum 
{
    TRANSFER_INIT,
    TRANSFER_DOING,
    TRANSFER_STOPED,
    TRANSFER_CANCEL
} FileTranStatus;

/**
 * @brief file transfer
 */
class FileTransfer
{
public:
    FileTransfer();
    explicit FileTransfer(const IPv4Addr& clientAddr, 
        const AcceptSocket& clientSocket);
    virtual ~FileTransfer();

    /**
     * @brief handle client message
     * @param [in] data : client message
     * @param [in] len : message length
     * @return : true/false
     */   
     bool handleReq(const int8* data, const uint64 len);

private:
    /**
     * @brief handle client message
     * @param [in] clientMsg : client message
     * @param [in] msgLen : message length
     * @return : true/false
     */    
    bool handleClientGetReq(const int8* clientMsg, const uint32 msgLen);
    bool handleClientPutReq(const int8* clientMsg, const uint32 msgLen);
    bool handleClientGetComple(const int8* clientMsg, const uint32 msgLen);
    bool handleClientSuspend(const int8* clientMsg, const uint32 msgLen);
    bool handleClientCancel(const int8* clientMsg, const uint32 msgLen);    

private:
    IPv4Addr       m_clientAddr;
    AcceptSocket   m_clientSocket;
    std::string    m_filePath;
    FileStream     m_fileStream;
    FileTranStatus m_transferStatus;
    int8           m_transferTempBuf[TRANSFER_TEMP_BUF_SIZE];
};

}

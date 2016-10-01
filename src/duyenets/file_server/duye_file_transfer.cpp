/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_transfer.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-01
* @note 
*
* 1. 2016-04-01 duye Created this file
*/

#include <duye_logger.h>
#include <duye_file_protocol.h>
#include <duye_file_transfer.h>

static const int8* DUYE_LOG_PREFIX = "duyeone.file.transfer";

namespace duye {

FileTransfer::FileTransfer() {}
FileTransfer::FileTransfer(const IPv4Addr& clientAddr, 
    const AcceptSocket& clientSocket) 
    : m_clientAddr(clientAddr)
    , m_clientSocket(clientSocket)
    , m_transferStatus(TRANSFER_INIT) {}

FileTransfer::~FileTransfer()
{
    m_clientSocket.close();
}

bool FileTransfer::handleReq(const int8* data, const uint64 len)
{
    FileClientMsgType msgType = FileProtocolParser::getClientMsgType(data, len);    
    switch (msgType)
    {
    case FILE_CLI_GET_REQ:
        handleClientGetReq(data, len);
        break;
    case FILE_CLI_PUT_REQ:
        handleClientPutReq(data, len);
        break;
    case FILE_CLI_PUT_COMPLE:
        handleClientGetComple(data, len);
        break;
    case FILE_CLI_TRANSFER_SUSPEND:
        handleClientSuspend(data, len);
        break;
    case FILE_CLI_TRANSFER_CANCEL:
        handleClientCancel(data, len);
        break;       
    case FILE_CLI_UNKNOWN:
        DUYE_ERROR("FileProtocolParser::getClientMsgType() failed");
        return false;
        break;             
    default:
        return false;
    }
        
    return true;    
}

bool FileTransfer::handleClientGetReq(const int8* clientMsg, const uint32 msgLen)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;

    FilePathList filePathList;
    if (FileProtocolParser::parserClientGetReqMsg(clientMsg, msgLen, filePathList))
    {
        DUYE_ERROR("FileProtocolParser::parserClientGetReqMsg() failed");
        return false;
    }

    if (filePathList.empty())
    {
        DUYE_ERROR("filePathList.empty()");
        return false;        
    }
    
    return true;
}

bool FileTransfer::handleClientPutReq(const int8* clientMsg, const uint32 msgLen)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;    
    return true;
}

bool FileTransfer::handleClientGetComple(const int8* clientMsg, const uint32 msgLen)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;    
    return true;
}

bool FileTransfer::handleClientSuspend(const int8* clientMsg, const uint32 msgLen)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;    
    return true;
}

bool FileTransfer::handleClientCancel(const int8* clientMsg, const uint32 msgLen)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;    
    return true;
}

}

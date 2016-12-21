/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_rpc_proxy.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-11
* @note 
*
* 1. 2016-04-11 duye Created this file
*/
#include <duye_logger.h>
#include <duye_rpc_msg.h>
#include <duye_rpc_server.h>
#include <duye_rpc_proxy.h>

static const int8* DUYE_LOG_PREFIX = "duye.nets.rpc.proxy";

namespace duye {

RpcProxy::RpcProxy()
    : m_rpcServer(NULL)
    , m_proxyStatus(RPC_PROXY_INIT)
{
}

RpcProxy::RpcProxy(RpcServer* rpcServer,
    const IPv4Addr& clientAddr, 
    const AcceptSocket& clientSocket) 
    : m_rpcServer(rpcServer)
    , m_clientAddr(clientAddr)
    , m_clientSocket(clientSocket)
    , m_proxyStatus(RPC_PROXY_INIT)
{
    setStatus(RPC_PROXY_DOING);
}

RpcProxy::~RpcProxy()
{
}

bool RpcProxy::sendResponse(const int8* data, const uint32 len)
{
    if (m_proxyStatus != RPC_PROXY_DOING)
        return false;
    
    return sendResp(data, len);
}

bool RpcProxy::sendResponse(const std::string& respMsg)
{
    DUYE_TRACE("response >> \n%s", respMsg.c_str());
    return sendResponse(respMsg.c_str(), respMsg.length());
}

const IPv4Addr& RpcProxy::clientAddr() const
{
    return m_clientAddr;
}

void RpcProxy::setStatus(const RpcProxyStatus status)
{
    m_proxyStatus = status;
    DUYE_INFO("sockfd=%d status cheanged to %s", m_clientSocket.sockfd(), getStatusDesp(status));
}

bool RpcProxy::handleReq(const int8* data, const uint64 len)
{
    RpcReqMsg rpcReqMsg;
    //rpcReqMsg.orgData = (int8*)data;
    //rpcReqMsg.orgLen = len;
    
    uint32 errorID = 0;
    if (!RpcMsgParser::formatReqMsg(data, len, rpcReqMsg, errorID))
    {
        DUYE_ERROR("RpcMsgParser::verifyClientMsg() failed");
        return sendErrorResp(errorID);
    }

    if (m_rpcServer == NULL)
        return false;

    return m_rpcServer->notifyUser(this, &rpcReqMsg);
}

bool RpcProxy::sendErrorResp(const uint32 errorID)
{
    std::string xmlStr;
    if (!RpcMsgParser::formatRespErrorMsg(errorID, xmlStr))
    {
        DUYE_ERROR("RpcMsgParser::formatServerErrorRespMsg() failed");
        return false;
    }
    
    if (!sendResp(xmlStr.c_str(), xmlStr.length()))
    {
        DUYE_ERROR("Transfer::send() failed");
        return false;
    }

    DUYE_DEBUG("sendErrorResp successed");
    
    return true;
}

bool RpcProxy::sendResp(const int8* data, const uint32 len)
{
    int64 size = Transfer::send(m_clientSocket.sockfd(), data, len);
    if (size != len)
        return false;
    return true;
}

const char* RpcProxy::getStatusDesp(const RpcProxyStatus status)
{   
    switch (status)
    {
    case RPC_PROXY_INIT:
        return "RPC_PROXY_INIT";
        break;
    case RPC_PROXY_DOING:
        return "RPC_PROXY_DOING";
        break;
    case RPC_PROXY_STOPED:
        return "RPC_PROXY_STOPED";
        break;
    case RPC_PROXY_DESTROY:
        return "RPC_PROXY_DESTROY";
        break;
    default:
        return NULL;
        break;
    }
}

}

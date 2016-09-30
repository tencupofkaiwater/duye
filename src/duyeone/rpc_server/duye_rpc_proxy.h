/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_rpc_proxy.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-11
* @note 
*
* 1. 2016-04-11 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_lock.h>
#include <duye_net_server.h>

namespace duye {

/**
 * @brief transfer status
 */
typedef enum 
{
    RPC_PROXY_INIT,
    RPC_PROXY_DOING,
    RPC_PROXY_STOPED,
    // wait for destroy
    RPC_PROXY_DESTROY
} RpcProxyStatus;

class RpcServer;

/**
 * @brief file transfer
 */
class RpcProxy
{
public:
    RpcProxy();
    explicit RpcProxy(RpcServer* rpcServer, 
        const IPv4Addr& clientAddr, 
        const AcceptSocket& clientSocket);
    virtual ~RpcProxy();

    /**
     * @brief handle client request message
     * @param [in] data : client message
     * @param [in] len : message length
     * @return : true/false
     */   
    bool handleReq(const int8* data, const uint64 len);   

    /**
     * @brief send message to client
     * @param [in] data : client message
     * @param [in] len : message length
     * @return : true/false
     */   
    bool sendResponse(const int8* data, const uint32 len);
    bool sendResponse(const std::string& respMsg);

    /**
     * @brief get client address
     * @return : IPv4Addr
     */   
    const IPv4Addr& clientAddr() const;

private:
    // set proxy status
    void setStatus(const RpcProxyStatus status);    
    bool sendErrorResp(const uint32 errorID);
    bool sendResp(const int8* data, const uint32 len);
    const char* getStatusDesp(const RpcProxyStatus status);

private:
    RpcServer*     m_rpcServer;
    IPv4Addr       m_clientAddr;
    AcceptSocket   m_clientSocket;
    RpcProxyStatus m_proxyStatus;
};
}
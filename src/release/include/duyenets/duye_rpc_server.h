/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_rpc_server.h
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
#include <duye_msg_queue.h>
#include <duye_net_server.h>
#include <duye_tcp_server.h>
#include <duye_hcn_server.h>
#include <duye_rpc_msg.h>
#include <duye_rpc_proxy.h>

namespace duye {

class RpcServerUserIf
{
public:
    virtual ~RpcServerUserIf() {}
    virtual bool onMsg(RpcProxy* proxy, RpcReqMsg* rpcReqMsg) = 0;
};

class HcnServer;

/**
 * @brief network rpc server
 * @example:
 * RpcServer rpcServer;
 * if (rpcServer.initServer())
 * {
 *      return false;
 * }
 * if (rpcServer.startServer())
 * {
 *      return false;
 * }
 *
 * rpcServer.stopServer(fd);
 */
class RpcServer : public NetServer, public TcpServerIf, public ClientProxy<RpcProxy>
{
public:
    // <sockfd, RpcProxy*>
    typedef std::map<int32, RpcProxy*> RpcProxyMap;
    typedef std::list<int32> DestroyProxyList;
    
public:
    RpcServer();
    virtual ~RpcServer();

    /**
     * @brief start server, from NetServer
     * @param [in] user : RPC Server creater
     * @param [in] serverPara : server parameters
     * @return : true/false
     */
    bool initServer(RpcServerUserIf* user, const NetServerPara& serverPara);
    
    /**
     * @brief start server, from NetServer
     * @return : true/false
     */
    virtual bool startServer();

    /**
     * @brief stop server, from NetServer
     * @return : true/false
     */   
    virtual bool stopServer(); 

    /**
     * @brief regist message
     * @param [in] filePath : RPC xml conf file path
     * @return : true/false
     */   
    bool registRpcMsg(const std::string& filePath);  

protected:
    // implementation TcpServerIf interface
    virtual bool onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd);
    virtual bool onDiscon(const int32 clientSockfd); 
    virtual bool onRecved(const int32 clientSockfd, const int8* data, const uint64 len); 

private:
    // add new client
    bool acceptClient();
    // notify user data received
    bool notifyUser(RpcProxy* rpcProxy, RpcReqMsg* rpcReqMsg);

private:
    friend class RpcProxy;
    
    NetServerPara       m_serverPara;
    TcpServer           m_tcpServer;
    RpcServerUserIf*    m_user;  
    RpcFunMap           m_rpcFunMap;
};
}
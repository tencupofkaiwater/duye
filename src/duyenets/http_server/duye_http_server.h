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
* @date	    2016-12-12
* @note 
*
* 1. 2016-12-12 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_msg_queue.h>
#include <duye_net_server.h>
#include <duye_tcp_server.h>
#include <duye_hcn_server.h>

namespace duye {

class HttpServerUserIf
{
public:
    virtual ~HttpServerUserIf() {}
    virtual bool onMsg(void* proxy, void* rpcReqMsg) = 0;
};

class HcnServer;

/**
 * @brief network rpc server
 * @example:
 * HttpServer httpServer;
 * if (httpServer.initServer())
 * {
 *      return false;
 * }
 * if (httpServer.startServer())
 * {
 *      return false;
 * }
 *
 * httpServer.stopServer(fd);
 */
class HttpServer : public NetServer, public TcpServerIf
{
public:
    HttpServer();
    virtual ~HttpServer();

    /**
     * @brief start server, from NetServer
     * @param [in] user : RPC Server creater
     * @param [in] serverPara : server parameters
     * @return : true/false
     */
    bool initServer(HttpServerUserIf* user, const NetServerPara& serverPara);
    
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
    //bool registRpcMsg(const std::string& filePath);  

protected:
    // implementation TcpServerIf interface
    virtual bool onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd);
    virtual bool onDiscon(const int32 clientSockfd); 
    virtual bool onRecved(const int32 clientSockfd, const int8* data, const uint64 len); 

private:
    // add new client
    bool acceptClient();
    // notify user data received
    //bool notifyUser(RpcProxy* rpcProxy, RpcReqMsg* rpcReqMsg);

private:   
    NetServerPara       m_serverPara;
    TcpServer           m_tcpServer;
    HttpServerUserIf*   m_user;  
};

}
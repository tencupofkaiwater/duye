/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_server.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-25
* @note 
*
* 1. 2016-04-25 duye Created this file
*/
#pragma once

#include <duye_type.h>
#include <duye_net_server.h>
#include <duye_tcp_server.h>
#include <duye_cfg_mgr.h>
#include <duye_db_visitor.h>
#include <duye_db.h>

namespace duye {

/**
 * @brief db service
 */
class DBServer : public NetServer, public TcpServerIf, public ClientProxy<DBVisitor>
{
public:
    DBServer();
    ~DBServer();

    /**
     * @brief start server, from NetServer
     * @param [in] confFile : db service config file
     * @return : true/false
     */
    bool initServer(const int8* confFile);
    
    // implementation NetServer interface
    virtual bool startServer();
    virtual bool stopServer();    

protected:
    // implementation TcpServerIf interface
    virtual bool onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd);
    virtual bool onDiscon(const int32 clientSockfd); 
    virtual bool onRecved(const int32 clientSockfd, const int8* data, const uint64 len);
    
private:
    CfgMgr	    m_cfgMgr;
    TcpServer   m_tcpServer;      
    DatabaseMgr m_databaseMgr;
};

}

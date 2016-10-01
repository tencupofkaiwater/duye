/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duyetwo_server.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-08
* @note 
*
* 1. 2016-04-08 duye Created this file
*/

#pragma once

#include <duye_system.h>
#include <duye_cfg_mgr.h>
#include <duye_net_server.h>
#include <duye_db_client.h>
#include <duye_file_server.h>
#include <duye_rpc_server.h>

namespace duyetwo {

/**
 * @brief server
 */
class TwoServer : public duye::NetServer, public duye::RpcServerUserIf
{
public:
	TwoServer();
	virtual ~TwoServer();

	bool initServer();
	
	// implementation duye::NetServer
    virtual bool startServer();
    virtual bool stopServer();

protected:
    // implementation duye::RpcServerUserIf
    virtual bool onMsg(duye::RpcProxy* proxy, duye::RpcReqMsg* rpcReqMsg);

    // response
    bool respHearbeat(duye::RpcProxy* proxy, duye::RpcReqMsg* rpcReqMsg);
    bool respUserLoad(duye::RpcProxy* proxy, duye::RpcReqMsg* rpcReqMsg);    

private:
	duye::CfgMgr	    m_cfgMgr;
	duye::FileServer 	m_fileServer; 
    duye::RpcServer     m_rpcServer;
    duye::DBClient      m_dbClient;
};
}
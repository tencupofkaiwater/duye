/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duyetwo_server.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-08
* @note 
*
* 1. 2016-04-08 duye Created this file
*/
#include <duye_logger.h>
#include <duye_system.h>
#include <duye_process.h>
#include <duye_helper.h>
#include <duye_file_server.h>
#include <duye_rpc_server.h>
#include <duye_rpc_msg.h>
#include <duyetwo_server.h>

static const int8* DUYE_LOG_PREFIX = "duyetwo.server";

namespace duyetwo {

TwoServer::TwoServer() : duye::NetServer("TwoServer")
{
}

TwoServer::~TwoServer()
{
}

bool TwoServer::initServer()
{
    if (serverStatus() != duye::SERVER_UNINIT)
    {
        DUYE_WARN("server isn't SERVER_UNINIT status, ready to stoped server");
        if (!stopServer())
        {
            DUYE_ERROR("stopServer failed");
            return false;
        }    
    }

	// read conf
	if (!m_cfgMgr.load("/etc/duyetwo/duyetwo_sys.xml"))
	{
		DUYE_ERROR("load system config file '/etc/duyetwo/duyetwo_sys.xml' failed");
		return false;
	}	

	//m_cfgMgr.print();

	// check server address
	if (m_cfgMgr.getValue("duyetwo.server_ip").empty())
	{
		DUYE_WARN("server ip is empty");
	}

	// check main server port
	if (m_cfgMgr.getValue("duyetwo.server_port").empty())
	{
		DUYE_ERROR("main server port is empty");
		return false;		
	}	

	// check file server port
	if (m_cfgMgr.getValue("duyetwo.file_server_port").empty())
	{
		DUYE_ERROR("file server port is empty");
		return false;		
	}		
	
	setServerStatus(duye::SERVER_INIT);
	DUYE_INFO("TwoServer.initServer [OK]");
		
	return true;
}
	
bool TwoServer::startServer()
{
    if (serverStatus() != duye::SERVER_INIT)
    {
        DUYE_ERROR("hcn server status isn't SERVER_INIT");
        return false;        
    }
	
	duye::FileServerPara fileServerParm;
    fileServerParm.serverAddr = m_cfgMgr.getValue("duyetwo.server_ip");
    fileServerParm.serverPort = (uint16)duye::StrHelper::toInt(m_cfgMgr.getValue("duyetwo.file_server_port"));
    fileServerParm.concurrent = (uint32)duye::StrHelper::toInt(m_cfgMgr.getValue("duyetwo.max_con"));
	if (fileServerParm.concurrent == 0)
		fileServerParm.concurrent = 1000;
     
    if (!m_fileServer.initServer(fileServerParm))
    {
       DUYE_ERROR("m_fileServer.initServer failed");
       return -1;
    }

    if (!m_fileServer.startServer())
    {
       DUYE_ERROR("m_fileServer.startServer failed");
       return -1;
    }

	duye::NetServerPara rpcServerParm;
    rpcServerParm.bindAddr = m_cfgMgr.getValue("duyetwo.server_ip");
    rpcServerParm.port = (uint16)duye::StrHelper::toInt(m_cfgMgr.getValue("duyetwo.server_port"));
    rpcServerParm.maxConn = (uint32)duye::StrHelper::toInt(m_cfgMgr.getValue("duyetwo.max_con"));
	if (rpcServerParm.maxConn == 0)
		rpcServerParm.maxConn = 1000;
	rpcServerParm.isBlock = true;
	
    if (!m_rpcServer.initServer(this, rpcServerParm))
    {
       DUYE_ERROR("m_rpcServer.initServer failed");
       return -1;
    }

    if (!m_rpcServer.startServer())
    {
       DUYE_ERROR("m_rpcServer.startServer failed");
       return -1;
    }    

    if (!m_rpcServer.registRpcMsg(m_cfgMgr.getValue("duyetwo.rpc_fun_file")))
    {
       DUYE_ERROR("m_rpcServer.registRpcMsg failed, rpc_fun_file=%s", m_cfgMgr.getValue("duyetwo.rpc_fun_file").c_str());
       return -1;
    }   

    std::string dbAddr = m_cfgMgr.getValue("duyetwo.db_addr");
    uint16 dbPort = duye::StrHelper::toInt(m_cfgMgr.getValue("duyetwo.db_port"));
    std::string dbUser = m_cfgMgr.getValue("duyetwo.db_user");
    std::string dbPwd = m_cfgMgr.getValue("duyetwo.db_pwd");
    if (!m_dbClient.connect(dbAddr, dbPort, dbUser, dbPwd))
    {
       DUYE_ERROR("connect db service failed");
       return -1;        
    }
    
	DUYE_INFO("TwoServer.startServer [OK]");

	setServerStatus(duye::SERVER_RUNNING);
	
	return true;
}

bool TwoServer::stopServer()
{
	if (!m_fileServer.stopServer())
		DUYE_WARN("m_fileServer.stopServer failed");
	
	if (!m_rpcServer.stopServer())
		DUYE_WARN("m_rpcServer.stopServer failed");
	
	setServerStatus(duye::SERVER_STOPED);

	DUYE_INFO("TwoServer.stopServer [OK]");
	
	return true;
}

bool TwoServer::onMsg(duye::RpcProxy* proxy, duye::RpcReqMsg* rpcReqMsg)
{
    if (proxy == NULL || rpcReqMsg == NULL)
        return false;

    DUYE_INFO("received client(%s) message function=%s", proxy->clientAddr().ipStr(), rpcReqMsg->rpcFun.name.c_str());

    if (rpcReqMsg->rpcFun.name == "hearbeat")
    {
        return respHearbeat(proxy, rpcReqMsg);
    }
    else if (rpcReqMsg->rpcFun.name == "user_load")
    {
        return respUserLoad(proxy, rpcReqMsg);
    }    
    
    return true;
}

bool TwoServer::respHearbeat(duye::RpcProxy* proxy, duye::RpcReqMsg* rpcReqMsg)
{
    // get request parameter
    std::string clientIP;
    if (!rpcReqMsg->rpcFun.getInParaVal("clientip", clientIP))
    {
        DUYE_ERROR("to get client IP from hearbeat request message failed");
        return false;
    }
    
    rpcReqMsg->rpcFun.outParaMap.insert(std::make_pair("clientip", duye::RpcFunPara("clientip", "string", clientIP)));
    std::string respMsg;
    if (!duye::RpcMsgParser::formatRespMsg(*rpcReqMsg, respMsg))
       return false;
    
    if (!proxy->sendResponse(respMsg))
    {
       DUYE_ERROR("response hearbeat failed");
       return false; 
    }

    DUYE_INFO("send response message to %s successed", proxy->clientAddr().ipStr());
    
    return true;
}

bool TwoServer::respUserLoad(duye::RpcProxy* proxy, duye::RpcReqMsg* rpcReqMsg)
{
    // get request parameter
    std::string userName;
    std::string pwdMd5;
    if (!rpcReqMsg->rpcFun.getInParaVal("name", userName))
    {
        DUYE_ERROR("to get user name from hearbeat request message failed");
        return false;
    }

    if (!rpcReqMsg->rpcFun.getInParaVal("pwd_md5", pwdMd5))
    {
        DUYE_ERROR("to get pwd md5 from hearbeat request message failed");
        return false;
    }    

    std::string isLoad("true");
    int8 sqlBuf[256] = {0};
    duye::System::pformat(sqlBuf, sizeof(sqlBuf), "select * from tab_user where name='%s' and pwd_md5='%s'", 
        userName.c_str(), pwdMd5.c_str());
    if (!m_dbClient.query(sqlBuf))
    {
        isLoad.assign("false");
    }
    
    rpcReqMsg->rpcFun.outParaMap.insert(std::make_pair("isload", duye::RpcFunPara("isload", "bool", isLoad)));
    std::string respMsg;
    if (!duye::RpcMsgParser::formatRespMsg(*rpcReqMsg, respMsg))
       return false;
    
    if (!proxy->sendResponse(respMsg))
    {
       DUYE_ERROR("response hearbeat failed");
       return false; 
    }

    DUYE_INFO("send response message successed");
    
    return true;
}

}
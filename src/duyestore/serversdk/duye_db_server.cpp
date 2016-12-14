/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_server.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-25
* @note 
*
* 1. 2016-04-25 duye Created this file
*/
#include <string>
#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_db_server.h>

static const int8* DUYE_LOG_PREFIX = "duye.db.serversdk";

namespace duye {

static const uint16 DB_SERVICE_MIN_PORT = 1025;
static const uint16 DB_SERVICE_MAX_PORT = 65535;

DBServer::DBServer() : NetServer("DBServer") {}
DBServer::~DBServer() { stopServer(); }

bool DBServer::initServer(const int8* confFile)
{
    DUYE_INFO("start DBServer::initServer");

    if (confFile == NULL)
        return false;
    
    if (serverStatus() != SERVER_UNINIT)
    {
        DUYE_WARN("server isn't SERVER_UNINIT status, ready to stoped server");
        if (!stopServer())
        {
            DUYE_ERROR("stopServer failed");
            return false;
        }
    }

    // read conf
    if (!m_cfgMgr.load(confFile))
    {
        DUYE_ERROR("load system config file '%s' failed", confFile);
        return false;
    }   

    // check server_ip
    if (!m_cfgMgr.getValue("node:global.param:server_ip", "value").empty() && 
        !duye::StrHelper::isIpAddr(m_cfgMgr.getValue("node:global.param:server_ip", "value")))
    {
        DUYE_WARN("duyedbserver.server_ip format error");
        return false;
    }

    // check server_port
    uint16 port = 0;
    if (!m_cfgMgr.getValue("duyedbserver.server_port", port))
    {
        DUYE_ERROR("duyedbserver.server_port error : get server_port failed");
        return false;       
    }
    
    if (!duye::StrHelper::isPort(port))
    {
        DUYE_ERROR("duyedbserver.server_port(%d) error : should in 0x00 ~ 0xFFFF", port);
        return false;       
    }
    
    if (port < DB_SERVICE_MIN_PORT || port > DB_SERVICE_MAX_PORT)
    {
        DUYE_ERROR("server_port must in %d ~ %d", DB_SERVICE_MIN_PORT, DB_SERVICE_MAX_PORT);
        return false;       
    }       

    // check max_con
    if (!m_cfgMgr.getValue("duyedbserver.max_con").empty() &&
        !duye::StrHelper::isNums(m_cfgMgr.getValue("duyedbserver.max_con")))
    {
        DUYE_ERROR("duyedbserver.max_con isn't numbers");
        return false;
    }

    if (!m_cfgMgr.getValue("duyedbserver.max_con").empty())
    {
        uint32 maxCon = 0;
        m_cfgMgr.getValue("duyedbserver.max_con", maxCon);
        if (maxCon < 1 || maxCon > 100000)
        {
            DUYE_ERROR("max_con must in 1~100000");
            return false;
        }  
    }

    // check db_socket
    if (m_cfgMgr.getValue("duyedbserver.db_socket").empty())
    {
        DUYE_ERROR("duyedbserver.db_socket is empty");
        return false;       
    }     

    // check db_root
    if (m_cfgMgr.getValue("duyedbserver.db_root").empty())
    {
        DUYE_ERROR("duyedbserver.db_root is empty");
        return false;       
    }    

    // check db_size
    if (!duye::StrHelper::isNums(m_cfgMgr.getValue("duyedbserver.db_size")))
    {
        DUYE_ERROR("duyedbserver.db_size isn't numbers");
        return false;       
    }   

    uint32 dbSize = 0;
    m_cfgMgr.getValue("duyedbserver.db_size", dbSize);
    if (dbSize < 64 || dbSize > 16384)
    {
        DUYE_ERROR("db_size must in 64(MB)~16384(MB)(=16G)");
        return false;
    }

    setServerStatus(duye::SERVER_INIT);
    DUYE_INFO("DBServer::initServer [OK]");
        
    return true;
}

bool DBServer::startServer()
{
    DUYE_INFO("start DBServer::startServer");
    
    if (serverStatus() != SERVER_INIT)
    {
        DUYE_ERROR("hcn server status isn't SERVER_INIT");
        return false;        
    }

    //m_cfgMgr.print();

    NetServerPara serverPara;
    m_cfgMgr.getValue("duyedbserver.server_ip", serverPara.bindAddr);

    if (serverPara.bindAddr.empty())
        m_cfgMgr.getValue("duyedbserver.physical_nc", serverPara.localDevName);
    
    m_cfgMgr.getValue("duyedbserver.server_port", serverPara.port);    
    m_cfgMgr.getValue("duyedbserver.max_con", serverPara.maxConn);
    
    if (!m_tcpServer.initServer(serverPara, this))
        return false;       

    if (!m_tcpServer.startServer())
        return false;

    setServerStatus(SERVER_RUNNING);
    DUYE_INFO("DBServer::startServer [ok]");
    
    return true;
}

bool DBServer::stopServer()
{
    DUYE_INFO("start DBServer::stopServer");

    bool ret = true;
    if (!cleanProxy())
    {
        ret = false;
        DUYE_WARN("cleanProxy failed");
    }
        
    if (!m_tcpServer.stopServer())
    {
        ret = false;
        DUYE_WARN("m_tcpServer.stopServer failed");        
    }
    
    setServerStatus(SERVER_STOPED);

	DUYE_INFO("DBServer::stopServer [OK]");

    return ret;
}

bool DBServer::onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd)
{
    DUYE_INFO("accept client : %s:%d sockfd=%d", clientAddr.ipStr(), clientAddr.port(), clientSockfd);
    DBVisitor* visitor = new DBVisitor(clientAddr, AcceptSocket(clientSockfd));
    if (visitor == NULL)
    {
        DUYE_ERROR("create new db visitor failed.");
        return false;
    }
    
    return addProxy(clientSockfd, visitor);
}

bool DBServer::onDiscon(const int32 clientSockfd)
{
    return delProxy(clientSockfd);
}

bool DBServer::onRecved(const int32 clientSockfd, const int8* data, const uint64 len)
{
    DBVisitor* visitor = proxy(clientSockfd);
    if (visitor == NULL)
    {
        DUYE_ERROR("client sockfd=%d don't exist", clientSockfd);
        return false;
    }

    DUYE_TRACE("%s", data);
    
    return visitor->handleReq(data, len);
}

}

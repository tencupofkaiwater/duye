/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_server.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-12
* @note 
*
* 1. 2016-12-12 duye Created this file
*/

#include <duye_logger.h>
#include <duye_hcn_server.h>
#include <duye_http_server.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.nets.http.server";
    
HttpServer::HttpServer() : NetServer("HttpServer"), m_user(NULL) {}
HttpServer::~HttpServer() 
{ 
    stopServer();
}

bool HttpServer::initServer(HttpServerUserIf* user, const NetServerPara& fileServerPara)
{
    if (user == NULL)
        return false;

    m_user = user;
    
    DUYE_INFO("start HttpServer::initServer");
    m_serverPara = fileServerPara;
    DUYE_INFO("HttpServer::initServer [OK]");
    
    return true;
}

bool HttpServer::startServer()
{
    DUYE_INFO("start HttpServer::startServer");
    
    NetServerPara tcpServerPara;
    tcpServerPara.localDevName = m_serverPara.localDevName;
    tcpServerPara.bindAddr = m_serverPara.bindAddr;
    tcpServerPara.port = m_serverPara.port;
    tcpServerPara.maxConn = m_serverPara.maxConn;
	tcpServerPara.isBlock = true;
	
    if (!m_tcpServer.initServer(tcpServerPara, this))
    {
        DUYE_ERROR("init tcp server failed.");
        return false;
    }

    if (!m_tcpServer.startServer())
    {
        DUYE_ERROR("startup tcp server failed.");
        return false;
    }
    
    DUYE_INFO("HttpServer::startServer %s:%d [OK]", tcpServerPara.bindAddr.c_str(), tcpServerPara.port);
    
    return true;
}

bool HttpServer::stopServer()
{
    DUYE_INFO("start HttpServer::stopServer");

    bool ret = true;        
    if (!m_tcpServer.stopServer())
    {
        ret = false;
        DUYE_WARN("m_tcpServer.stopServer failed");        
    }
    
    setServerStatus(SERVER_STOPED);

	DUYE_INFO("HttpServer.stopServer [OK]");
	
    return ret;
}

/*
bool HttpServer::registRpcMsg(const std::string& filePath)
{
    DUYE_INFO("start HttpServer::registRpcMsg");
    
    XmlDocument xmlDoc;
    if (!xmlDoc.loadFile(filePath.c_str()))
    {
        DUYE_ERROR("HttpServer::registRpcMsg load xml file '%s' failed", filePath.c_str());
        return false;
    }

    // <duye_rpc> node
    XmlElement* rootElement = xmlDoc.rootElement();
    if (rootElement == NULL)
    {
        DUYE_ERROR("rootElement == NULL");
        return false;
    }

    // <function> node
    XmlElement* funElement = rootElement->firstChildElement();
    for (; funElement != NULL; funElement = funElement->nextSiblingElement())
    {
        RpcFun rpcFun;
        rpcFun.name = funElement->attribute("name");        
        XmlElement* funAttrElement = funElement->firstChildElement();
        for (; funAttrElement != NULL; funAttrElement = funAttrElement->nextSiblingElement())
        {
            if (funAttrElement->valueStr() == "para")
            {
                RpcFunPara para;
                para.name = funAttrElement->getText();
                para.type = funAttrElement->attribute("type");

                if (!(para.type == "bool" || para.type == "int" || para.type == "uint" || para.type == "string"))
                {
                    DUYE_ERROR("parameter type error:para.type = %s", para.type.c_str());
                    return false;
                }
                
                para.from = funAttrElement->attribute("from");
                if (para.from == "input")
                {
                    rpcFun.inParaMap.insert(std::make_pair(para.name, para));
                }
                else if (para.from == "output")
                {
                    rpcFun.outParaMap.insert(std::make_pair(para.name, para));
                }
                else
                {
                    DUYE_ERROR("parameter from error:para.from=%s", para.from.c_str());
                    return false;
                }
            }            
            else
            {
                return false;
            }        
        }

        m_rpcFunMap.insert(std::make_pair(rpcFun.name, rpcFun));
    }

    DUYE_INFO("HttpServer.registRpcMsg [OK]");
    
    return true;
}
*/

bool HttpServer::onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd)
{
    DUYE_INFO("accept client : %s:%d sockfd=%d", clientAddr.ipStr(), clientAddr.port(), clientSockfd);

	/*
    RpcProxy* rpcProxy = new RpcProxy(this, clientAddr, AcceptSocket(clientSockfd));
    if (rpcProxy == NULL)
    {
        DUYE_ERROR("create new rpc proxy failed.");
        return false;
    }
    
	return addProxy(clientSockfd, rpcProxy);
	*/

	return true;
}

bool HttpServer::onDiscon(const int32 clientSockfd)
{
    DUYE_DEBUG("HttpServer::onDiscon sockfd=%d", clientSockfd);
	/*
    RpcProxy* rpcProxy = proxy(clientSockfd);
    if (rpcProxy == NULL)
    {
        DUYE_ERROR("don't find sockfd=%d", clientSockfd);
        return false;
    }

    DUYE_DEBUG("client %s:%d disconnect, sockfd=%d", rpcProxy->clientAddr().ipStr(), rpcProxy->clientAddr().port(), clientSockfd);
    
    return delProxy(clientSockfd);
    */
    return true;
}

bool HttpServer::onRecved(const int32 clientSockfd, const int8* data, const uint64 len)
{
	/*
    RpcProxy* rpcProxy = proxy(clientSockfd);
    if (rpcProxy == NULL)
    {
        DUYE_ERROR("client sockfd=%d don't exist", clientSockfd);
        return false;
    }

    DUYE_TRACE("%s", data);
    
    return rpcProxy->handleReq(data, len);
    */
    return true;
}

/*
bool HttpServer::notifyUser(RpcProxy* rpcProxy, RpcReqMsg* rpcReqMsg)
{
    if (m_user == NULL || rpcProxy == NULL || rpcReqMsg == NULL)
        return false;   

    if (m_rpcFunMap.find(rpcReqMsg->rpcFun.name) == m_rpcFunMap.end())
    {
        DUYE_ERROR("function '%s' don't exsit", rpcReqMsg->rpcFun.name.c_str());
        return false;        
    }

    return m_user->onMsg(rpcProxy, rpcReqMsg);
}
*/

}

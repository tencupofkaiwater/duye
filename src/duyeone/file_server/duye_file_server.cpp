/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_server.cpp
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
#include <duye_file_server.h>

static const int8* DUYE_LOG_PREFIX = "duyeone.fileserver";

namespace duye {
    
FileServer::FileServer() : NetServer("FileServer") {}
FileServer::~FileServer() { stopServer(); }

bool FileServer::initServer(const FileServerPara& fileServerPara)
{
    DUYE_INFO("start FileServer::initServer");
    m_serverPara = fileServerPara;
    DUYE_INFO("FileServer::initServer [OK]");
    return true;
}

bool FileServer::startServer()
{
    DUYE_INFO("start FileServer::startServer");
    
    NetServerPara tcpServerPara;
    tcpServerPara.localDevName = m_serverPara.localDevName;
    tcpServerPara.bindAddr = m_serverPara.serverAddr;
    tcpServerPara.port = m_serverPara.serverPort;
    tcpServerPara.maxConn = m_serverPara.concurrent;
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

    DUYE_INFO("FileServer::startServer %s:%d [OK]", tcpServerPara.bindAddr.c_str(), tcpServerPara.port);
    
    return true;
}

bool FileServer::stopServer()
{
    DUYE_INFO("start FileServer::stopServer");
    	
	if (!m_tcpServer.stopServer())
		DUYE_WARN("m_tcpServer.stopServer failed");

	DUYE_INFO("FileServer::stopServer [OK]");

    cleanFileTransfer();
	
    return true;
}

bool FileServer::onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd)
{
    DUYE_INFO("accept client : %s:%d", clientAddr.ipStr(), clientAddr.port());
    
    FileTransfer* fileTransfer = new FileTransfer(clientAddr, AcceptSocket(clientSockfd));
    if (fileTransfer == NULL)
    {
        DUYE_ERROR("new FileTransfer failed.");
        return false;
    }
    
    return addFileTransfer(clientSockfd, fileTransfer);
}

bool FileServer::onDiscon(const int32 clientSockfd)
{
    return delFileTransfer(clientSockfd);
}

bool FileServer::onRecved(const int32 clientSockfd, const int8* data, const uint64 len)
{
    FileTransfer* transfer = fileTransfer(clientSockfd);
    if (transfer == NULL)
        return false;
    
    return transfer->handleReq(data, len);
}

bool FileServer::addFileTransfer(const int32 clientSockfd, FileTransfer* fileTransfer)
{
	AutoLock autoLock(m_fileTransferMapMutex);
	m_fileTransferMap.insert(std::make_pair(clientSockfd, fileTransfer));
	return true;
}

FileTransfer* FileServer::fileTransfer(const int32 clientSockfd)
{
	AutoLock autoLock(m_fileTransferMapMutex);
    FileTransferMap::iterator iter = m_fileTransferMap.find(clientSockfd);
	if (iter == m_fileTransferMap.end())
	{
		return NULL;
	}
    
	return iter->second;
}

bool FileServer::delFileTransfer(const int32 clientSockfd)
{
	AutoLock autoLock(m_fileTransferMapMutex);
	FileTransferMap::iterator iter = m_fileTransferMap.find(clientSockfd);
	if (iter == m_fileTransferMap.end())
	{
		return false;
	}

	if (iter->second)
		delete iter->second;
	
	m_fileTransferMap.erase(iter);
	
	return true;
}

bool FileServer::cleanFileTransfer()
{
	AutoLock autoLock(m_fileTransferMapMutex);
    FileTransferMap::iterator iter = m_fileTransferMap.begin();
    for (; iter != m_fileTransferMap.end(); ++iter)
    {
        if (iter->second)
        {
            delete iter->second;
            iter->second = NULL;
        }
    }    

	return true;
}

}

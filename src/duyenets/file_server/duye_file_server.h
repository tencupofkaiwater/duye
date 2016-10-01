/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_server.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-01
* @note 
*
* 1. 2016-04-01 duye Created this file
*/

#pragma once

#include <map>
#include <duye_type.h>
#include <duye_tcp_server.h>
#include <duye_net_server.h>

namespace duye {
  
/**
 * @brief network file server parameters
 */
class FileServerPara
{
public:
    FileServerPara() : serverPort(0), concurrent(100) {}

    // whether bind local net device, user not needed setting
    std::string localDevName;
    // local server ipv4, user not needed setting, default open socket on all net device
    std::string serverAddr;
    // local listener server port, user needed setting
    uint16      serverPort;
    // concurrent number for transfer files, user not needed setting, default is 100
    uint32      concurrent;
};

class FileTransfer;

/**
 * @brief network file server
 * @example:
 * FileServer fileServer;
 * if (fileServer.initServer())
 * {
 *      return false;
 * } 
 * if (fileServer.startServer())
 * {
 *      return false;
 * }
 *
 * fileServer.stopServer(fd);
 */
class FileServer : public NetServer, public TcpServerIf
{
public:
    // <sockfd, FileTransfer*>
    typedef std::map<int32, FileTransfer*> FileTransferMap;
    
public:
    FileServer();
    virtual ~FileServer();

    /**
     * @brief start server, from NetServer
     * @param [in] fileServerPara : file server parameters
     * @return : true/false
     */
    bool initServer(const FileServerPara& fileServerPara);
    
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

protected:
    // implementation TcpServerIf interface
    virtual bool onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd);
    virtual bool onDiscon(const int32 clientSockfd); 
    virtual bool onRecved(const int32 clientSockfd, const int8* data, const uint64 len);

private:
	// add/del/clean file client connect
	bool addFileTransfer(const int32 clientSockfd, FileTransfer* fileTransfer);
    FileTransfer* fileTransfer(const int32 clientSockfd);
	bool delFileTransfer(const int32 clientSockfd);
	bool cleanFileTransfer();

private:
    FileServerPara  m_serverPara;
    TcpServer       m_tcpServer;
    FileTransferMap m_fileTransferMap;
	Mutex		    m_fileTransferMapMutex;
};
}

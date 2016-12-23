/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_tcp_server.h
* @version     
* @brief      
* @author   duye
* @date	    2016-03-29
* @note 
*
* 1. 2016-03-29 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_socket.h>
#include <duye_hcn_server.h>
#include <duye_net_server.h>

namespace duye {

/** 
 * @brief tcp service interface
 */
class TcpServerIf
{
public:
    virtual ~TcpServerIf() {}

    /**
     * @brief accept client to connect
     * @param [out] clientAddr : output client address information
     * @param [out] clientSockfd : client sockfd
     * @return true/false
     */    
    virtual bool onNewcon(const IPv4Addr& clientAddr, const int32 clientSockfd) = 0;

    /**
     * @brief disconnect
     * @param [out] clientSockfd : client sockfd
     * @return true/false
     */    
    virtual bool onDiscon(const int32 clientSockfd) = 0;  

    /**
     * @brief receive data
     * @param [out] clientSockfd : client sockfd
     * @param [out] data : received data
     * @param [in] len : received data length
     * @return true/false
     * @note 
     */	
    virtual bool onRecved(const int32 clientSockfd, const int8* data, const uint64 len) = 0;  
};

/** 
 * @brief tcp server socket class
 */
class TcpServer : public NetServer, public HcnServerListener
{
public:
    TcpServer();
    virtual ~TcpServer();
    
    /**
     * @brief init tcp server
     * @param [in] serverPara : server information
     * @return true/false
     */
    bool initServer(TcpServerIf* user);
    bool initServer(const NetServerPara& serverPara, TcpServerIf* user);

    /**
     * @brief start tcp server, rewrite abstract interface from NetServer
     * @return true/false
     */
    virtual bool startServer();

    /**
     * @brief stop tcp server, implementation abstract interface for NetServer
     * @param [in] serverPara : server information
     * @return true/false
     */
    virtual bool stopServer();

    /**
     * @brief get server IPv4 address
     * @return IPv4 address
     */
    const IPv4Addr& ipv4Addr();

	bool addClient(const int32 sockfd);
    bool removeClient(const int32 sockfd);
	
    /**
     * @brief send data
     * @param [in] data : send data
     * @param [in] len : data length
     * @return size/-1
     * @note 
     */		
    int64 send(const int32 clientSockfd, const int8* data, const uint64 len);

protected:
    // implementation HcnServerListener
    virtual bool onNetEvent(HcnEvent* event);    

private:
    bool acceptClient();
    bool readData(HcnEvent* event);
    
    /**
     * @brief accept client to connect
     * @param [out] clientAddr : output client address information
     * @param [out] clientSockfd : client sockfd
     * @param [in] isBlock : block or unblock, default unblock
     * @return true/false
     */
    bool accept(IPv4Addr& clientAddr, int32& clientSockfd, const bool isBlock = false);

    /**
     * @brief receive data
     * @param [out] clientSockfd : client sockfd
     * @param [out] buffer : output buffer
     * @param [in] size : buffer size
     * @param [in] isBlock : block or unblock, default unblock
     * @return size/-1
     * @note 
     */	
    int64 recv(int32 clientSockfd, int8* buffer, const uint64 size, const bool isBlock = false);     

private:
    NetServerPara   m_serverPara;
    Socket          m_socket;
    IPv4Addr	    m_ipv4Addr;
    HcnServer       m_hcnServer;
    TcpServerIf*    m_tcpServerUser;
    Mutex			m_acceptMutex;
    Mutex           m_readMutex;
};

}

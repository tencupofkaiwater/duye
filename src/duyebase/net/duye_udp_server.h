/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_udp_server.h
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
#include <duye_net_server.h>

namespace duye {

/** 
 * @brief udp server socket class
 */
class UdpServer : public NetServer
{
public:
    UdpServer();
    virtual ~UdpServer();

    /**
     * @brief init udp server, rewrite abstract interface from NetServer
     * @param [in] serverPara : server information
     * @return true/false
     */
    bool initServer(const NetServerPara& serverPara);    

    /**
     * @brief start udp server, rewrite abstract interface from NetServer
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
    
    /**
     * @brief receive data
     * @param [out] srcAddr : source address
     * @param [out] buffer : output buffer
     * @param [in] size : buffer size
     * @param [in] isBlock : block or unblock, default block
     * @return : size on success, return the number of characters received. on error, return -1
     * @note 
     */
    int64 recvfrom(IPv4Addr& srcAddr, int8* buffer, const uint64 size, const bool isBlock = true);  

    /**
     * @brief send data for UDP protocol
     * @param [in] dstAddr : destination address
     * @param [in] data : send data
     * @param [in] len : data length
     * @return on success, return the number of characters sent. on error, return -1
     */
    int64 sendto(IPv4Addr& dstAddr, const int8* data, const uint64 len);

private:
    NetServerPara     m_serverPara;
    Socket         m_socket;
    IPv4Addr       m_ipv4Addr; 
};

}

/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_socket.h
* @version     
* @brief      
* @author   duye
* @date	    2014-02-16
* @note 
*
*  2. 2014-06-20 duye move to gohoop project 
*  1. 2014-02-16 duye Created this file
* 
*/
#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <string>
#include <memory>
#include <list>

#include <duye_sys.h>
#include <duye_type.h>

namespace duye {

/** 
 * @brief address family
 */
/*
typedef enum 
{
    // AF_INET
    G_AF_IPV4,
    // AF_INET6
    G_AF_IPV6,
    G_AF_LOCAL,
    G_AF_UNIX,
    G_AF_ROUTE,
    G_AF_PACKET
} AddrFamily;
*/

/** 
 * @brief transfer type
 */
/*
typedef enum 
{
    // tcp
    G_SOCK_STREAM,
    // udp
    G_SOCK_DGRAM,
    G_SOCK_SEQPACKET,
    G_SOCK_RAW,
    G_SOCK_RDM,
    G_SOCK_PACKET,
    G_SOCK_NONBLOCK,
    G_SOCK_CLOEXEC
} SockType;
*/

/** 
 * @brief network protocol
 */
typedef enum 
{ 
    // for SOCK_STREAM
    IPPROTO_TCP,
    // for SOCK_DGRAM
    IPPROTO_UDP,
    // not support
    //IPPROTO_SCTP,
    // not support
    //IPPROTO_TIPC
} NetProtocol;

/** 
 * @brief IPv4 address
 */
class IPv4Addr
{
public:
    /**
     * @brief auto get local address, and rand setting a port
     * @param [in] ip : ip address
     * @param [in] port : port, default is 0, will random generate
     */
    IPv4Addr();
    explicit IPv4Addr(const uint32 ip, const uint16 port = 0);
    ~IPv4Addr();
	
    /**
     * @brief set/get IP address
     * @return
     */
    void setIp(const uint32 ip);
    uint32 ip();
    const uint32 ip() const;
    uint8* ipStr();
    const uint8* ipStr() const;

    /**
     * @brief set/get port
     * @return 
     */
    void setPort(const uint16 port);
    uint16 port();
    const uint16 port() const;
	
    /**
     * @brief set/get sock addr
     * @return 
     */		
    sockaddr_in& addr();
    const sockaddr_in& addr() const;
    
    /**
     * @brief get sock address length
     * @return 
     */	    
    uint16 addrLen() const;
    
private:
    sockaddr_in	   m_addr;
    uint16         m_addrLen;
};

/** 
 * @brief IPv6 address
 */
class IPv6Addr
{
public:
    /**
     * auto get local address, and rand setting a port
     */
    IPv6Addr();
    explicit IPv6Addr(const uint8 ip[16], const uint16 port = 0);
    ~IPv6Addr();
	
    /**
     * @brief set/get IP address
     * @return
     */		
    uint8* ip();

    /**
     * @brief set/get port
     * @return 
     */		
    uint16 port();
	
    /**
     * @brief set/get sock addr
     * @return 
     */		
    sockaddr_in6& addr();
    
    /**
     * @brief get sock address length
     * @return 
     */	        
    uint16 addrLen() const;
        
private:
    // address
    sockaddr_in6    m_sockAddr;
    uint16         	m_addrLen;
};

class Error;

/** 
 * @brief server socket class
 */
class Socket
{
public:
    Socket();
    ~Socket();

    /**
     * @brief open socket
     * @param [in] protocol : network protocol
     * @param [in] ifName : interface name
     * @param [in] isBlock : block/unblock, default is block
     * @return true/false
     * @note 
     */		
    bool open(const NetProtocol& protocol, const bool isBlock = true); 
    bool open(const NetProtocol& protocol, const std::string& ifName, const bool isBlock = true);
    bool isOpen() const;
    
    /**
     * @brief shutdown connecting
     * @param [in] how : default is 2
     * @return true/false
     * @note 
     *     how = 0 : stop receive data
     *     how = 1 : stop send data
     *     how = 2 : both above way
     */	
    bool close(const int32 how = 2);
    
    /**
     * @brief get sock fd
     * @return sock fd
     */
    int32 sockfd() const;
	
    /**
     * @brief get last error string
     * @return error string
     * @note 
     */		
    uint8* error();
	
private:
    /**
     * @brief setting socket options 
     * @param [in] sockfd : sockfd
     * @param [in] ifName : interface name
     * @return true/false
     */		
    bool initOption(int32 sockfd, const std::string& ifName);
	
private:
    int32   m_sockfd;	
    bool    m_isInit;
	Error	m_error;
};

/**
 * @brief Multicast 
 */
class AcceptSocket
{
public:
    AcceptSocket();
    explicit AcceptSocket(const int32 sockfd);
    ~AcceptSocket();

    /**
     * @brief shutdown connecting
     * @param [in] how : default is 2
     * @return true/false
     * @note 
     *     how = 0 : stop receive data
     *     how = 1 : stop send data
     *     how = 2 : both above way
     */	
    bool close(const int32 how = 2);
    
    /**
     * @brief get sock fd
     * @return sock fd
     */
    int32 sockfd() const;

private:
    int32 m_sockfd;
};

/**
 * @brief Multicast 
 */
class Multicast
{
public:
    Multicast();
    ~Multicast();
    
private:

};

/**
 * @brief broadcast
 */
class Broadcast
{
public:
    Broadcast();
    ~Broadcast();
    
private:
    
};
	
/**
 * @brief transfer api
 */
class Transfer
{
public:	
    Transfer();
    ~Transfer();

    /**
     * @brief accept client to connect
     * @param [in] serverSockfd : output client address infomation
     * @param [in] clientAddr : client address
     * @param [in] addrLen : client length
     * @return On success, return true. On error, false is returned
     */
    static bool bind(const int32 serverSockfd, const struct sockaddr* clientAddr, const uint32 addrLen);

    /**
     * @brief accept client to connect
     * @param [in] serverSockfd : output client address infomation
     * @param [in] maxConnect : max connection numbers
     * @return On success, return true. On error, false is returned
     */
    static bool listen(const int32 serverSockfd, const uint32 maxConnect);

    /**
     * @brief accept client to connect
     * @param [in] serverSockfd : output client address infomation
     * @param [out] clientAddr : client address
     * @param [in] addrLen : client length
     * @param [in] isBlock : block/unblock, default is block
     * @return On success, return a nonnegative integer that is a descriptor for the accepted socket. On error, -1 is returned
     */
    static int32 accept(const int32 serverSockfd, struct sockaddr* clientAddr, const uint32 addrLen, const bool isBlock = true);	

    /**
     * @brief accept client to connect
     * @param [in] clientSockfd : client socketfd
     * @param [out] serverAddr : server address
     * @param [in] addrLen : client length
     * @return On success, return true. On error, return false
     */
    static bool connect(const int32 clientSockfd, const struct sockaddr* serverAddr, const uint32 addrLen);
    
    /**
     * @brief send data
     * @param [in] sockfd : socket fd
     * @param [in] data : send data
     * @param [in] len : data length
     * @param [in] flags : default is MSG_NOSIGNAL
     * @return on success, return the number of characters sent. on error, return -1
     * @note 
     */		
    static int64 send(const int32 sockfd, const int8* data, const uint64 len, const int32 flags = MSG_NOSIGNAL);
    static int64 sendmsg(const int32 sockfd, const struct msghdr* msg, const int32 flags = MSG_NOSIGNAL);
    static int64 sendto(const int32 sockfd, IPv4Addr& dstAddr, const int8* data, const uint64 len, const int32 flags = MSG_NOSIGNAL);
   
    /**
     * @brief receive data
     * @param [in] sockfd : socket fd
     * @param [out] buffer : output buffer
     * @param [in] size : buffer size
     * @param [in] flags : flags
     * @return on success, return the number of bytes received. on error, return -1, 
     *		The return value will be 0 when the peer has performed an orderly shutdown.
     * @note 
     */	
    static int64 recv(const int32 sockfd, int8* buffer, const uint64 size, const bool block = false);
    static int64 recvmsg(const int32 sockfd, struct msghdr* msg, const int32 flags = 0);
    static int64 recvfrom(const int32 sockfd, IPv4Addr& srcAddr, int8* buffer, const uint64 size, const int32 flags = 0);    
};

}

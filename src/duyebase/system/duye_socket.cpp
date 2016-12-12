/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_socket.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-2-16
* @note 
*
*  2. 2014-06-21 duye move to gohoop 
*  1. 2014-02-16 duye Created this file
* 
*/
#include <net/if.h>
#include <unistd.h>
#include <fcntl.h>
#include <duye_sys.h>
#include <duye_socket.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.socket";
const struct in6_addr IN6ADDR_ANY = IN6ADDR_ANY_INIT;

IPv4Addr::IPv4Addr() : IPv4Addr(INADDR_ANY, 0) {}
IPv4Addr::IPv4Addr(const uint32 ip, const uint16 port)
{
    m_addrLen = sizeof(sockaddr_in);
    bzero(&m_addr, m_addrLen);
    m_addr.sin_family = AF_INET; 
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = htonl(ip); 
}

IPv4Addr::~IPv4Addr() {}

void IPv4Addr::setIp(const uint32 ip)
{
    m_addr.sin_addr.s_addr = htonl(ip);	
}

uint32 IPv4Addr::ip()
{
    return ntohl(m_addr.sin_addr.s_addr);
}

const uint32 IPv4Addr::ip() const
{
    return ntohl(m_addr.sin_addr.s_addr);
}

uint8* IPv4Addr::ipStr()
{
    return (uint8*)inet_ntoa(m_addr.sin_addr);
}

const uint8* IPv4Addr::ipStr() const
{
    return (uint8*)inet_ntoa(m_addr.sin_addr);
}

void IPv4Addr::setPort(const uint16 port)
{
    m_addr.sin_port = htons(port);
}

uint16 IPv4Addr::port()
{
    return ntohs(m_addr.sin_port);
}

const uint16 IPv4Addr::port() const
{
    return ntohs(m_addr.sin_port);
}

sockaddr_in& IPv4Addr::addr()
{
    return m_addr;
}

const sockaddr_in& IPv4Addr::addr() const
{
    return m_addr;
}

uint16 IPv4Addr::addrLen() const
{
    return m_addrLen;
}

IPv6Addr::IPv6Addr()
{
    m_addrLen = sizeof(sockaddr_in6);
    bzero(&m_sockAddr, m_addrLen);
    m_sockAddr.sin6_family = AF_INET6; 
    m_sockAddr.sin6_port = 0; 
    m_sockAddr.sin6_addr = IN6ADDR_ANY;
}

IPv6Addr::IPv6Addr(const uint8 ip[16], const uint16 port)
{
    bzero(&m_sockAddr, sizeof(m_sockAddr));
    m_sockAddr.sin6_family = AF_INET6; 
    m_sockAddr.sin6_port = htons(port);
    memcpy(m_sockAddr.sin6_addr.s6_addr, ip, 16);
}

IPv6Addr::~IPv6Addr() {}

uint8* IPv6Addr::ip()
{
    return m_sockAddr.sin6_addr.s6_addr;
}

uint16 IPv6Addr::port()
{
    return ntohs(m_sockAddr.sin6_port);
}

sockaddr_in6& IPv6Addr::addr()
{
    return m_sockAddr;
}

uint16 IPv6Addr::addrLen() const
{
    return m_addrLen;
}

Socket::Socket() : m_sockfd(-1), m_isInit(false)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

Socket::~Socket() { close(); }

bool Socket::open(const NetProtocol& protocol, const bool isBlock)
{
    return open(protocol, "", isBlock);
}

bool Socket::open(const NetProtocol& protocol, const std::string& ifName, const bool isBlock)
{
    int32 domain = AF_INET;
    int32 sockType = -1;
    int32 sockProtocol = -1;
	
    switch (protocol)
    {
    	case IPPROTO_TCP:
    	{
            sockProtocol = IPPROTO_TCP;
            sockType = SOCK_STREAM;
            break;
    	}
    	case IPPROTO_UDP:
    	{
    	    sockProtocol = IPPROTO_UDP;
    	    sockType = SOCK_DGRAM;
    	    break;
    	}
    	//case IPPROTO_SCTP:
    	//{
    	    //sockProtocol = IPPROTO_SCTP;
    	    //ERROR_DUYE_LOG(argument protocol(%d) not support (%s:%s:%d)\n", protocol, __FUNCTION__, __FILE__, __LINE__);
    	    //break;
    	//}
    	//case IPPROTO_TIPC:
    	//{
    	    //sock_protocol = IPPROTO_TIPC;
    	    //ERROR_DUYE_LOG("[warn]argument protocol(%d) not support (%s:%s:%d)\n", protocol, __FUNCTION__, __FILE__, __LINE__);
    	    //break;
    	//}
    	default:
        {
    	    ERROR_DUYE_LOG("argument protocol(%d) invalid (%s:%s:%d)\n", protocol, __FUNCTION__, __FILE__, __LINE__);
    	    return false;
        }
    }	
	
    m_sockfd = ::socket(domain, sockType, sockProtocol);
    if (m_sockfd < 0)
    {
    	ERROR_DUYE_LOG("socket(%d, %d, %d) ret=%d invalid (%s:%s:%d)\n", 
    	    domain, sockType, sockProtocol, m_sockfd, __FUNCTION__, __FILE__, __LINE__);
        return false;
    }

    // set non-blocking
	if (!isBlock)
		fcntl(m_sockfd, F_SETFL, O_NONBLOCK);
    
    // init socket option
    m_isInit = initOption(m_sockfd, ifName);

    return m_isInit;
}

bool Socket::isOpen() const
{
    return m_isInit;
}

bool Socket::close(const int32 how)
{
    // SHUT_RD how = 0 : stop receive data
    // SHUT_WR how = 1 : stop send data
    // SHUT_RDWR how = 2 : both above way
    if (!m_isInit)
    {
    	return true;
    }

    //return (shutdown(m_sockfd, how) == 0 ? true : false);
    return ::close(m_sockfd) == 0 ? true : false;
}

int32 Socket::sockfd() const
{
    return m_sockfd;	
}

uint8* Socket::error()
{
    return m_error.error;
}

bool Socket::initOption(int32 sockfd, const std::string& ifName)
{
    bool ret = true;
    
    // setting specified interface
    if (!ifName.empty())
    {
	    struct ifreq interface;
	    strncpy(interface.ifr_ifrn.ifrn_name, ifName.c_str(), ifName.length());
	    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (char*)&interface, sizeof(interface)) == -1) 
	    {
	    	ERROR_DUYE_LOG("setting specified interface(%s) failed (%s:%s:%d)\n", ifName.c_str(), __FUNCTION__, __FILE__, __LINE__);
	    }    
    }
    
    // setting address reuse, address reuse flag, 1 reuse
    int32 reuse = 1;    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(int32)) == -1)
    {
    	ERROR_DUYE_LOG("setting address reuse failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    }

    // setting send time limit, unit ms
    int sendTime = 2000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&sendTime, sizeof(int)) == -1)
    {
    	ERROR_DUYE_LOG("setting send time limit failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    }

    // setting receive time limit, unit ms
    int recvTime = 2000;    
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&recvTime, sizeof(int)) == -1)
    {
    	ERROR_DUYE_LOG("setting receive time limit failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    }

    // setting send data buffer size 
    int32 sendBufSize = 0xFFFF;    
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&sendBufSize, sizeof(int32)) == -1)
    {
    	ERROR_DUYE_LOG("setting send data buffer size failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    }

    // setting receive data buffer size
    int32 recvBufSize = 0xFFFF;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)&recvBufSize, sizeof(int32)) == -1)
    {
    	ERROR_DUYE_LOG("setting receive data buffer size failed (%s:%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    }

    // don't copy data from system buffer to socket buffer when send data
    /*
    int32 is_copy = 0;    
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&is_copy, sizeof(int32)) == -1)
    {
    	ERROR_DUYE_LOG("%s:setsockopt() failed (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = false;
    }

    // don't copy data from system buffer to GSocket buffer when receive data
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)&is_copy, sizeof(int32)) == -1)
    {
    	ERROR_DUYE_LOG("%s:setsockopt() failed (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
    	ret = false;
    }
    */

    // let data send completly after execute close GSocket
    /*
    struct STR_Linger
    {
    	GInt16 l_onoff;
    	GInt16 l_linger;
    };

    STR_Linger linger;
    linger.l_onoff = 1;		// 1. allow wait; 0. force close
    linger.l_linger = 1;	// the time of waiting unit s
    if (setsockopt(m_sockfd, SOL_GSocket, SO_LINGER, (const char*)&linger, sizeof(STR_Linger)) == -1)
    {
        ret = false;
    }
    */

    return ret;
}

AcceptSocket::AcceptSocket() : m_sockfd(-1)
{
}

AcceptSocket::AcceptSocket(const int32 sockfd) : m_sockfd(sockfd)
{
}

AcceptSocket::~AcceptSocket()
{
    close();
}

bool AcceptSocket::close(const int32 how)
{
    // SHUT_RD how = 0 : stop receive data
    // SHUT_WR how = 1 : stop send data
    // SHUT_RDWR how = 2 : both above way
    if (m_sockfd != -1)
    {
    	return true;
    }
    
    return ::close(m_sockfd) == 0 ? true : false;
}

int32 AcceptSocket::sockfd() const
{
    return m_sockfd;	
}

bool Transfer::bind(const int32 serverSockfd, const struct sockaddr* clientAddr, const uint32 addrLen)
{
    return ::bind(serverSockfd, clientAddr, addrLen) == 0 ? true : false;
}

bool Transfer::listen(const int32 serverSockfd, const uint32 maxConnect)
{
    return ::listen(serverSockfd, maxConnect) == 0 ? true : false;
}

int32 Transfer::accept(const int32 sockfd, struct sockaddr* clientAddr, const uint32 addrLen, const bool isBlock)
{
    int32 clientSockfd = -1;
    uint32 len = addrLen;
    
    if (isBlock)
    {
        clientSockfd = ::accept(sockfd, clientAddr, &len);
    }
    else
    {
    	clientSockfd = ::accept4(sockfd, clientAddr, &len, SOCK_NONBLOCK);	
    }

    return clientSockfd;
}

bool Transfer::connect(const int32 clientSockfd, const struct sockaddr* serverAddr, const uint32 addrLen)
{
    return ::connect(clientSockfd, serverAddr, addrLen) == 0 ? true : false;
}

int64 Transfer::send(const int32 sockfd, const int8* data, const uint64 len, const int32 flags)
{
    return ::send(sockfd, data, len, flags);
}

int64 Transfer::sendmsg(const int32 sockfd, const struct msghdr* msg, const int32 flags)
{
    return ::sendmsg(sockfd, msg, flags);	
}

int64 Transfer::sendto(const int32 sockfd, IPv4Addr& dst_addr, const int8* data, const uint64 len, const int32 flags)
{
    return ::sendto(sockfd, data, len, flags, (const struct sockaddr*)&dst_addr.addr(), dst_addr.addrLen());	
}

int64 Transfer::recv(const int32 sockfd, int8* buffer, const uint64 size, const int32 flags)
{
    return ::recv(sockfd, buffer, size, flags);
}

int64 Transfer::recvmsg(const int32 sockfd, struct msghdr* msg, const int32 flags)
{
    return ::recvmsg(sockfd, msg, flags);	
}

int64 Transfer::recvfrom(const int32 sockfd, IPv4Addr& srcAddr, int8* buffer, const uint64 size, const int32 flags)
{
    uint32 addrLen = srcAddr.addrLen();
    return ::recvfrom(sockfd, buffer, size, flags, (struct sockaddr*)&srcAddr.addr(), &addrLen);	
}

}

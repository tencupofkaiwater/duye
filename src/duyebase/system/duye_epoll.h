/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_epoll.h
* @version     
* @brief      
* @author   duye
* @date	    2016-03-29
* @note 
*
* 1. 2016-03-29 duye Created this file
*/

#pragma once

#include <sys/epoll.h>
#include <stdio.h>
#include <list>
#include <duye_sys.h>
#include <duye_type.h>

namespace duye {
    
typedef enum
{
	RECV_UN,
	RECV_FD,
	SEND_FD,
	ERROR_FD
} EpollEventType;

class EpollEvent
{
public:
	EpollEvent() : m_fd(-1), m_type(RECV_UN) {}
	EpollEvent(const int32 fd, const EpollEventType type) : m_fd(fd), m_type(type) {}
	~EpollEvent() {}
	
	/**
	 * @brief get/set fd
	 * @return fd
	 */
	void setfd(const int32 fd) { m_fd = fd; }
	int32 fd() const { return m_fd; }
	
	/**
	 * @brief get/set events
	 * @return events
	 */
	void setType(const EpollEventType type) { m_type = type; }
	EpollEventType type() const { return m_type; }    
	
	/**
	 * @brief is received data
	 * @return true/false
	 */
	bool isRecv() { return m_type == RECV_FD ? true : false; }
	
	 /**
	 * @brief is sent data
	 * @return true/false
	 */
	bool isSend() { return m_type == SEND_FD ? true : false; }     
     
	/**
	 * @brief is disconnection
	 * @return true/false
	 */
	bool isDiscon() { return m_type == ERROR_FD ? true : false; }    
     
private:
	int32           m_fd;	
	EpollEventType  m_type;
};

/**
 * @brief epoll socket server
 */
class Epoll
{
public:
	typedef struct epoll_event SysEvent;
    typedef std::list<EpollEvent> EventList;
    
public:
    Epoll();
    ~Epoll();
    
    /**
     * @brief open epoll
     * @param [in] maxEvent : the number of the max events
     * @return true/false
     */
    bool open(const uint32 maxEvents = 1024);
    
     /**
     * @brief close epoll
     * @return true/false
     */
    bool close();   
    
    /**
     * @brief add fd
     * @param [in] fd : fd
     * @param [in] epollMode : epoll events(EPOLLIN, EPOLLOUT, EPOLLPRI, EPOLLERR, 
     * 		EPOLLHUP, EPOLLET, EPOLLONESHOT), default is EPOLLIN | EPOLLOUT
     * @return true/false
     */      
    bool addfd(const int32 fd, const uint32 epollMode = EPOLLIN | EPOLLOUT);
    
    /**
     * @brief modify fd
     * @param [in] fd : fd
     * @param [in] epollMode : epoll events(EPOLLIN, EPOLLOUT, EPOLLPRI, EPOLLERR, 
     * 		EPOLLHUP, EPOLLET, EPOLLONESHOT), default is EPOLLIN | EPOLLOUT
     * @return true/false
     */      
    bool modfd(const int32 fd, const uint32 epollMode = EPOLLIN | EPOLLOUT);
    
    /**
     * @brief delete fd
     * @param [in] fd : fd
     * @return true/false
     */
    bool delfd(const int32 fd);
    
    /**
     * @brief wait event
     * @param [out] eventList : return event
     * @param [in] timeout : wait time out, default is -1, indicate block, millisecond
     * @return true/false
     */
    bool wait(Epoll::EventList& eventList, const uint32 timeout = -1);
    
    /**
     * @brief get last error string
     * @return error string
     * @note 
     */		
    uint8* error();	
    
private:
    // create epoll
    bool create();
    
private:
    int32       m_epollfd; 
    uint32      m_maxEvents;
    SysEvent*	m_sysEvents;
	Error       m_error;	
};
}

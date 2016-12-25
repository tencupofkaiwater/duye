/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_epoll.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-03-29
* @note 
*
* 1. 2016-03-29 duye Created this file
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <duye_sys.h>
#include <duye_epoll.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.system.epoll";

Epoll::Epoll() : m_epollfd(-1)
    , m_maxEvents(0)
    , m_sysEvents(NULL)
{
    m_error.setPrefix(DUYE_LOG_PREFIX);
}

Epoll::~Epoll() 
{
    close();
    if (m_sysEvents != NULL)
    {
        free(m_sysEvents);
        m_sysEvents = NULL;
    }
}

bool Epoll::open(const uint32 maxEvents)
{   
    m_maxEvents = maxEvents;
    
    m_epollfd = epoll_create(m_maxEvents);
    if (m_epollfd == -1)
    {
    	ERROR_DUYE_LOG("%s:%d > epoll_create failed \n", __FILE__, __LINE__);
    	return false;
    }   

    m_sysEvents = (struct epoll_event*)calloc(m_maxEvents, sizeof(struct epoll_event));
    if (m_sysEvents == NULL) {
		ERROR_DUYE_LOG("%s:%d > calloc return NULL \n", __FILE__, __LINE__);
        return false;
    }
    
    return true;
}

bool Epoll::close()
{
    if (m_epollfd != -1)
    {
    	::close(m_epollfd);
    	m_epollfd = -1;
    }
    
    return true;
}

bool Epoll::addfd(const int32 fd, const uint32 epollMode)
{
    if (m_epollfd == -1) {
		ERROR_DUYE_LOG("%s:%d > m_epollfd == -1", __FILE__, __LINE__);
		return false;
    }
	
    struct epoll_event epollEvent;
    bzero(&epollEvent, sizeof(struct epoll_event));
    epollEvent.data.fd = fd;
    epollEvent.events = epollMode;
    
    int32 ret = epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &epollEvent);
    if (ret != 0) {
		ERROR_DUYE_LOG("[%s:%d] epoll_ctl() return = %d", __FILE__, __LINE__, ret);
		return false;
    }

	return true;
}

bool Epoll::modfd(const int32 fd, const uint32 epollMode)
{
    if (m_epollfd == -1) {
		ERROR_DUYE_LOG("[%s:%d] m_epollfd == -1", __FILE__, __LINE__);
		return false;
    }
	
    struct epoll_event epollEvent;
    bzero(&epollEvent, sizeof(struct epoll_event));
    epollEvent.data.fd = fd;
    epollEvent.events = epollMode;
    
    return epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &epollEvent) == 0 ? true : false;
}
	 
bool Epoll::delfd(const int32 fd)
{
    if (m_epollfd == -1) {
		ERROR_DUYE_LOG("[%s:%d] m_epollfd == -1", __FILE__, __LINE__);
		return false;
    }
    
    return epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, NULL) == 0 ? true : false;
}

bool Epoll::wait(Epoll::EventList& eventList, const uint32 timeout)
{
    if (m_epollfd == -1) {
		ERROR_DUYE_LOG("[%s:%d] m_epollfd == -1", __FILE__, __LINE__);
		return false;
    }
	
    int32 event_count = epoll_wait(m_epollfd, m_sysEvents, m_maxEvents, timeout);
    if (event_count <= 0)
    {
    	return false;
    }

    for (uint32 i = 0; i < (uint32)event_count; i++)   
    {
        if ((m_sysEvents[i].events & EPOLLERR) ||  
            (m_sysEvents[i].events & EPOLLHUP))
        {
            ERROR_DUYE_LOG("[%s:%d] epoll error, close fd \n", __FILE__, __LINE__);
            delfd(m_sysEvents[i].data.fd);
            eventList.push_back(EpollEvent(m_sysEvents[i].data.fd, ERROR_FD));
    	    continue;
        }
        else if (m_sysEvents[i].events & EPOLLIN)
        {
            eventList.push_back(EpollEvent(m_sysEvents[i].data.fd, RECV_FD));
        }
		else if (m_sysEvents[i].events & EPOLLOUT)
		{
		    eventList.push_back(EpollEvent(m_sysEvents[i].data.fd, SEND_FD));
		}
		else
		{
		    eventList.push_back(EpollEvent(m_sysEvents[i].data.fd, RECV_UN));
		}
    }
    
    return true;
}

uint8* Epoll::error()
{
    return m_error.error;
}

}

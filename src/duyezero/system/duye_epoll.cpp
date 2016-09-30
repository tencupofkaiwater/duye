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

#define ERROR_DUYE_LOG(args...) System::pformat(m_error->errorLog, m_error->errorBufSize, ##args);
static const int8* DUYE_LOG_PREFIX = "duye.system.epoll";

namespace duye {

Epoll::Epoll() : m_epollfd(-1)
    , m_maxEvents(0)
    , m_sysEvents(NULL)
    , m_error(NULL)
{
    m_error = new Error(DUYE_LOG_PREFIX);
}

Epoll::~Epoll() 
{
    close();
    if (m_sysEvents != NULL)
    {
        free(m_sysEvents);
        m_sysEvents = NULL;
    }

	if (m_error)
	{
		delete m_error;
		m_error = NULL;
	}
}

bool Epoll::open(const uint32 maxEvents)
{   
    m_maxEvents = maxEvents;
    
    m_epollfd = epoll_create(m_maxEvents);
    if (m_epollfd == -1)
    {
    	ERROR_DUYE_LOG("epoll_create failed %s:%d:%s\n", __FILE__, __LINE__, __FUNCTION__);
    	return false;
    }   

    m_sysEvents = (struct epoll_event*)calloc(m_maxEvents, sizeof(struct epoll_event));
    if (m_sysEvents == NULL)
        return false;
    
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
    if (m_epollfd == -1)
		return false;
	
    struct epoll_event epollEvent;
    bzero(&epollEvent, sizeof(struct epoll_event));
    epollEvent.data.fd = fd;
    epollEvent.events = epollMode;
    
    return epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &epollEvent) == 0 ? true : false;
}

bool Epoll::modfd(const int32 fd, const uint32 epollMode)
{
    if (m_epollfd == -1)
		return false;
	
    struct epoll_event epollEvent;
    bzero(&epollEvent, sizeof(struct epoll_event));
    epollEvent.data.fd = fd;
    epollEvent.events = epollMode;
    
    return epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &epollEvent) == 0 ? true : false;
}
	 
bool Epoll::delfd(const int32 fd)
{
    if (m_epollfd == -1)
		return false;
    
    return epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, NULL) == 0 ? true : false;
}

bool Epoll::wait(Epoll::EventList& eventList, const uint32 timeout)
{
    if (m_epollfd == -1)
		return false;
	
    int32 event_count = epoll_wait(m_epollfd, m_sysEvents, m_maxEvents, timeout);
    if (event_count <= 0)
    {
    	return false;
    }

    ERROR_DUYE_LOG("[trace]m_epoll.wait event:%d", event_count);

    for (uint32 i = 0; i < (uint32)event_count; i++)   
    {
        if ((m_sysEvents[i].events & EPOLLERR) ||  
            (m_sysEvents[i].events & EPOLLHUP))
        {
            ERROR_DUYE_LOG("[error]epoll error, close fd. %s:%d:%s\n", __FILE__, __LINE__, __FUNCTION__);
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

int8* Epoll::error()
{
    return m_error->error;
}

}

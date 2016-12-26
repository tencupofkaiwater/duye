/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_hcn_server.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-03-29
* @note 
*
* 1. 2016-03-29 duye Created this file
*/

#include <duye_logger.h>
#include <duye_system.h>
#include <duye_thread_pool.h>
#include <duye_hcn_server.h>

static const int8* DUYE_LOG_PREFIX = "duye.net.hcnserver";

namespace duye {

bool HcnServerListener::work(void* userData)
{
    DUYE_TRACE("start HcnServerListener::work");
    
    HcnEvent* event = (HcnEvent*)userData;
    if (event == NULL)
        return false;

    onNetEvent(event);

    delete event;
    event = NULL;

    DUYE_TRACE("end HcnServerListener::work");
     
    return true;
}

HcnServer::HcnServer() : NetServer("HcnServer")
{      
}

HcnServer::~HcnServer()
{
    uninitServer();
}

bool HcnServer::initServer(const uint32 maxConn)
{
    DUYE_INFO("start HcnServer::initServer");
    
    if (serverStatus() != SERVER_UNINIT)
    {
        DUYE_WARN("server isn't SERVER_UNINIT status, ready to stoped server");
        if (!stopServer())
        {
            DUYE_ERROR("stopServer failed");
            return false;
        }
    }
    
    if (!m_epoll.open(maxConn))
    {
        DUYE_ERROR("m_epoll.open failed");
    }   

    const uint32 threadNum = maxConn >= 10 ? maxConn / 10 : 1;
    if (!m_threadPool.init(threadNum))
    {
        DUYE_INFO("m_threadPool.init failed");
        return false;
    }

    setServerStatus(SERVER_INIT);
    DUYE_INFO("HcnServer::initServer [ok]");

    return true;
}

bool HcnServer::startServer()
{
    DUYE_INFO("start HcnServer::startServer");
    
    if (serverStatus() != SERVER_INIT)
    {
        DUYE_ERROR("hcn server status isn't SERVER_INIT");
        return false;        
    }

    setServerStatus(SERVER_RUNNING);
    DUYE_INFO("HcnServer::startServer [OK]");
    
    return this->startTask();    
}

bool HcnServer::stopServer()
{
    DUYE_INFO("start HcnServer::stopServer");
    setServerStatus(SERVER_STOPED);
    bool ret = uninitServer();   
	DUYE_INFO("HcnServer::stopServer [OK]");
	return ret;
}

bool HcnServer::registerListener(const int32 sockfd, HcnServerListener* listener)
{
    return registerListener(sockfd, listener, EPOLLET|EPOLLIN);
}

bool HcnServer::registerListener(const int32 sockfd, HcnServerListener* listener, const uint32 epollMode)
{
    if (!m_epoll.addfd(sockfd, epollMode))
    {
        DUYE_ERROR("m_epoll.addfd(%d) failed : %s", sockfd, m_epoll.error());
        return false;
    }    
    
    AutoLock autoLock(m_listenerMutex);
    if (m_listenerContainer.find(sockfd) == m_listenerContainer.end()) {
        m_listenerContainer.insert(std::make_pair(sockfd, listener));
    }
	
    return true;
}

bool HcnServer::unregisterListener(const int32 sockfd)
{
    if (!m_epoll.delfd(sockfd))
    {
        DUYE_WARN("m_epoll.delfd(%d) failed, had delete from epoll", sockfd);
        return false;
    }   
    
    AutoLock autoLock(m_listenerMutex);     
    m_listenerContainer.erase(sockfd);
    
    return true;
}

bool HcnServer::modifyMode(const int32 sockfd, const uint32 epollMode)
{
    if (!m_epoll.modfd(sockfd, epollMode))
    {
        DUYE_ERROR("m_epoll.modfd(%d) failed.", sockfd);
        return false;
    }    	

	return true;
}

bool HcnServer::uninitServer()
{
    m_epoll.close();
    return true;
}

bool HcnServer::run()
{
    DUYE_DEBUG("start HCN server thread ok, tid=%u", threadId());

    const uint32 timeout = 100;
    Epoll::EventList eventList;
    
    for (;;)
    {
        eventList.clear();
        if (!m_epoll.wait(eventList, timeout)) {
            continue;
        }

        DUYE_TRACE("m_epoll.wait event size = %d", eventList.size());
        Epoll::EventList::iterator iter = eventList.begin();
        for (; iter != eventList.end(); ++iter)
            notifyEvent(*iter);
    }

    return true;
}

bool HcnServer::notifyEvent(const EpollEvent& event)
{
    AutoLock autoLock(m_listenerMutex);    
    ListenerContainer::iterator iter = m_listenerContainer.find(event.fd());
    if (iter == m_listenerContainer.end())
    {
        DUYE_ERROR("can't find mapping listener for sockfd.");
        return false;
    }

    HcnEvent* hcnEvent = new HcnEvent(this, event.fd(), event.type());
    if (hcnEvent == NULL)
    {
        DUYE_ERROR("new hcnEvent failed.");
        return false;
    }

    ThreadJob* job = dynamic_cast<ThreadJob*>(iter->second);
    if (job == NULL)
    {
        DUYE_ERROR("dynamic_cast<ThreadJob*>(iter->second) failed.");
        return false;
    }

    DUYE_TRACE("will m_threadPool.doJob()");
    if (!m_threadPool.doJob(job, (void*)hcnEvent)) {
        DUYE_ERROR("call m_threadPool.doJob return failed");
        delete hcnEvent;
        hcnEvent = NULL;
        return false;
    }
    
    return true;
}

}

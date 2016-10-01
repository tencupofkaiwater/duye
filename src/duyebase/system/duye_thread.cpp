/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_thread.cpp
* @version     
* @brief      
* @author   duye
* @date	    2013-11-26
* @note 
*
*  1. 2013-11-26 duye Created this file
* 
*/
#include <duye_thread.h> 

namespace duye {

Thread::Thread(const bool autoRel) 
    : m_threadId(-1)
    , m_autoRel(autoRel)
    , m_runnable(NULL) {}
    
Thread::Thread(Runnable* runnable, const bool autoRel) 
    : m_threadId(-1)
    , m_autoRel(autoRel)
    , m_runnable(runnable) {}

Thread::~Thread() {}

bool Thread::start()
{
    pthread_attr_t* attributes = NULL;
    bool ret = pthread_create(&m_threadId, attributes, enterPoint, m_runnable);
    if (ret != 0)
    {
    	return false;
    }

    if (m_autoRel)
    {
    	pthread_detach(m_threadId);
    }

    return true;
}

bool Thread::start(Runnable* target, const bool autoRel)
{
    m_runnable = target;
    m_autoRel = autoRel;
    return start();
}

bool Thread::join()
{
    return pthread_join(m_threadId, NULL) == 0 ? true : false;
}

void Thread::exit()
{
    pthread_exit(NULL);
}   

uint32 Thread::threadId() const
{
    return (uint32)m_threadId;
}

void* Thread::enterPoint(void* argument)
{
    Runnable* runnable = static_cast<Runnable*>(argument);
    runnable->run();
    return NULL;
}

ThreadTask::ThreadTask(const bool autoRel) : m_autoRel(autoRel) {}

ThreadTask::~ThreadTask() {}

bool ThreadTask::startTask(const bool autoRel)
{
    return m_thread.start(this, autoRel);
}

bool ThreadTask::join()
{
   return m_thread.join();   
}

uint32 ThreadTask::threadId() const
{
	return m_thread.threadId();
}

int32 ThreadUtil::createThread(void* entry, void* argument, const bool autoRel)
{
    pthread_attr_t* attributes = NULL;
    pthread_t threadId = -1;

    int32 ret = pthread_create(&threadId, attributes, (ThreadFunPoint)entry, argument);
    if (ret != 0)
    {
    	return (int32)threadId;
    }

    if (autoRel)
    {
    	pthread_detach(threadId);
    }

    return (int32)threadId;
}
}

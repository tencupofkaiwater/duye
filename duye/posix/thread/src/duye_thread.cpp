/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_thread.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-11-26
* @note 
*
*  1. 2013-11-26 duye Created this file
* 
*/

#include <duye/posix/thread/inc/duye_thread.h> 

DUYE_POSIX_NS_BEG

/*---------------------------Thread class----------------------*/
Thread::Thread(Runnable* target, const bool autoRel) 
	: m_threadId(-1)
	, m_runnable(target)
	, m_autoRel(autoRel)
{
}

Thread::~Thread()
{
}

bool Thread::Start()
{
	pthread_attr_t* attributes = NULL;
	
	Int32_t ret = pthread_create(&m_threadId, attributes, EnterPoint, m_target);

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

pthread_id Thread::GetThreadId() const
{
	return m_threadId;
}

pthread_t Thread::Bind(void* entry, void* argument, const bool autoRel = true)
{
	pthread_attr_t* attributes = NULL;

	pthread_t threadId = -1;

	Int32_t ret = pthread_create(&threadId, attributes, entry, argument);

	if (ret != 0)
	{
		return tid;
	}

	if (autoRel)
	{
		pthread_detach(threadId);
	}

	return threadId;
}

void* Thread::EnterPoint(void* argument)
{
	Runnable* target = static_cast<Runnable*>(argument);

    target->Run();

	return NULL;
}

/*------------------class ThreadTask--------------*/
ThreadTask::ThreadTask(const bool autoRel) : m_threadId(-1), m_autoRel(autoRel)
{
}

ThreadTask::~ThreadTask()
{
}

bool ThreadTask::Start()
{
	pthread_attr_t* attributes = NULL;
	
	Int32_t ret = pthread_create(&m_threadId, attributes, EnterPoint, this);

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

void* ThreadTask::EnterPoint(void* argument)
{
	ThreadTask* threadTask = static_cast<ThreadTask*>(argument);

    threadTask->Run();

	return NULL;
}

DUYE_POSIX_NS_END

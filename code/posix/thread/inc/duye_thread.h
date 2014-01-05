/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_thread.h
* @version     
* @brief      
* @author   duye
* @date     2013-11-26
* @note 
*
*  1. 2013-11-26 duye Created this file
* 
*/

#pragma once

#include <pthread.h> 
#include <duye/posix/inc/duye_posix_def.h>

DUYE_POSIX_NS_BEG

// fn : thread state
enum ThreadState
{
	// thread running
	THR_STATE_RUN = 0,
	// thread stop
	THR_STATE_STOP,
	// thread exit
	THR_STATE_EXIT
};

typedef void* (*ThreadFunPoint_t)(void*);

// fn : thread entry interface, used in thread class
class Runnable
{
public:
	Runnable() {}
	virtual ~Runnable() {}
	virtual void Run() = 0;
};

// fn : thread class 
// example :
//		class MyWorkWithThread : public Runnable
//		{
//		public:
//			virtual ~MyThread() {}
//			virtual Run() 
//			{
//				for (;;)
//				{
//					thread loop
//				}
//			}
//		}
//
//		MyWorkWithThread work;
//		Thread myThread(&work);
class Thread
{
public:
    explicit Thread(Runnable* target, const bool autoRel = true);
    ~Thread();
	
	// fn : start thread 
	bool Start();

	// fn : get thread ID
	pthread_t GetThreadId() const;

	// fn : Create new thread
	// @entry : the fun of thread entry
	// @para : input parameter
	// ret : return true when create sucessed, else return  
	// example :
	//		Thread::Bind(EntryFun, argument);
	static pthread_t Bind(void* entry, void* argument, const bool autoRel = true);

private:
	Thread(const Thread&);
	void operator=(const Thread&);
	// fn : thread entry
	static void* EnterPoint(void* argument);

private:
	pthread_t	m_threadId;
	bool		m_autoRel;
	Runnable*	m_runnable;
};

// fn : thread class
// example:
//		class MyThreadTask : public ThreadTask
//		{
//		public:
//			MyThreadTask() { this->Start(); }
//			virtual ~MyThreadTask() {}
//
//		private:
//			virtual Int8_t* Run()
//			{
//				// thread loop
//				for (;;) {}
//
//				return NULL;	
//			}
//		};
class ThreadTask
{
public:
	explicit ThreadTask(const bool autoRel = true);
	virtual ~ThreadTask();

	bool Start();

	virtual void Run() = 0;

private:
	ThreadTask(const ThreadTask&);
	void operator=(const ThreadTask&);
	static void* EnterPoint(void* argument);	

private:
	pthread_t		m_threadId;	
	bool			m_autoRel;
};

DUYE_POSIX_NS_END

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

// brief:
//  线程状态枚举
enum ThreadState
{
	// 线程运行状态
	THR_STATE_RUN = 0,
	// 线程停止状态
	THR_STATE_STOP,
	// 线程退出状态
	THR_STATE_EXIT
};

// brief:
//  函数指针重命名
typedef void* (*ThreadFunPoint_t)(void*);

// brief:
//  线程使用接口类
//	
// usage:
//	class MyThread : public Runnable
//  {
//  public:
//      MyThread() {}
//      virtual ~MyThread() {}
//  
//      virtual void Run()
//      {
//          // my thread
//          for (;;) {}
//      }
//  }
class Runnable
{
public:
	virtual ~Runnable() {}
	virtual void Run() = 0;
};

// brief:
//  POSIX 线程API封装
//	
// usage:
//	class MyThread : public Runnable
//  {
//  public:
//      MyThread() {}
//      virtual ~MyThread() {}
//  
//      virtual void Run()
//      {
//          // my thread
//          for (;;) {}
//      }
//  }
//  
//  MyThread myThread;
//  Thread newThread(&myThread);
//  newThread.Start();
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

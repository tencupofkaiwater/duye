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
//  线程状态, 你好
enum ThreadState
{
	// 运行状态
	THR_STATE_RUN = 0,
	// 停止状态
	THR_STATE_STOP,
	// 退出状态
	THR_STATE_EXIT
};

// brief:
//  线程入口函数指针
typedef void* (*ThreadFunPoint_t)(void*);

// brief:
//  使用多线程者需继承的接口
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
//  POSIX 多线程封装
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
	
	// brief : 启动线程
	// @para
	// return true/false
	bool Start();

	// brief : 获取线程ID
	// @para
	// return 返回线程ID
	pthread_t GetThreadId() const;

	// brief : 创建线程
	// @para entry 线程入口函数指针
	// @para argument 线程参数
	// @para autoRel 是否与主线程分离
	// return 返回线程ID
	// usage :
	//  void MyEntryFun(void* argument)
	//	{
	//	    for (;;) {}
	//  }
	//		
	//	void* argument;
	//	Thread::CreateThread(MyEntryFun, argument);
	static pthread_t CreateThread(void* entry, void* argument, const bool autoRel = true);

private:
	// brief : 防止拷贝
	Thread(const Thread&);
	void operator=(const Thread&);
	
	// brief : 启动多线程入口
	// @para argument 线程参数
	// return void*
	static void* EnterPoint(void* argument);

private:
	// 线程ID
	pthread_t	m_threadId;
	// 是否与主线程分离，默认分离
	bool		m_autoRel;
	// 用户多线程入口对象
	Runnable*	m_runnable;
};

// brief : 多线程基类
// usage :
//	class MyThreadTask : public ThreadTask
//	{
//	public:
//		MyThreadTask() { this->Start(); }
//		virtual ~MyThreadTask() {}
//
//	private:
//		virtual Int8_t* Run()
//		{
//			// thread loop
//			for (;;) {}
//			return NULL;	
//		}
//	};
class ThreadTask
{
public:
	// brief : 构造函数
	// @para autoRel 是否与主线程分离
	explicit ThreadTask(const bool autoRel = true);
	virtual ~ThreadTask();

	// brief : 启动线程
	// @para
	// return true/false
	bool Start();

	// brief : 线程入口，子类实现
	// @para
	// note
	virtual void Run() = 0;

private:
	// brief : 防止拷贝
	ThreadTask(const ThreadTask&);
	void operator=(const ThreadTask&);
	
	// brief : 启动多线程入口
	// @para argument 线程参数
	// return void*
	static void* EnterPoint(void* argument);	

private:
	// 线程ID
	pthread_t	m_threadId;	
	// 是否与主线程分离，默认分离
	bool		m_autoRel;
};

DUYE_POSIX_NS_END

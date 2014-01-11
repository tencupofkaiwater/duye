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
//  �߳�״̬ö��
enum ThreadState
{
	// �߳�����״̬
	THR_STATE_RUN = 0,
	// �߳�ֹͣ״̬
	THR_STATE_STOP,
	// �߳��˳�״̬
	THR_STATE_EXIT
};

// brief:
//  ����ָ��������
typedef void* (*ThreadFunPoint_t)(void*);

// brief:
//  �߳�ʹ�ýӿ���
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
//  POSIX �߳�API��װ
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
	
	// brief : 开始线程
	// @para
	// return true/false
	bool Start();

	// brief : 获取线程ID
	// @para
	// return 线程ID
	pthread_t GetThreadId() const;

	// brief : 创建新线程
	// @para entry 线程入口函数
	// @para argument 线程参数
	// @para autoRel 线程与主线程是否分离，默认分离
	// return 线程ID 
	// usage :
	//		void MyEntryFun(void* argument)
	//		{
	//			for (;;) {}
	//		}
	//		
	//		void* argument;
	//		Thread::CreateThread(MyEntryFun, argument);
	static pthread_t CreateThread(void* entry, void* argument, const bool autoRel = true);

private:
	// brief : 防止拷贝
	Thread(const Thread&);
	void operator=(const Thread&);
	
	// brief : 启动线程入口static方法
	// @para argument 线程参数
	// return void*
	static void* EnterPoint(void* argument);

private:
	// 线程ID
	pthread_t	m_threadId;
	// 线程是否与主线程分离
	bool		m_autoRel;
	// 线程对象
	Runnable*	m_runnable;
};

// brief : 实现多线程基类
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
	// brief : 带参构造函数
	// @para autoRel 是否与主线程分离，默认是
	explicit ThreadTask(const bool autoRel = true);
	virtual ~ThreadTask();

	// brief : 开始线程，继承类调用
	// @para
	// return true/false
	bool Start();

	// brief : 继承类多线程入口
	// @para
	// note 继承类必须实现
	virtual void Run() = 0;

private:
	// brief : 防止拷贝
	ThreadTask(const ThreadTask&);
	void operator=(const ThreadTask&);
	
	// brief : 线程入口
	// @para argument 线程参数
	// return void*
	static void* EnterPoint(void* argument);	

private:
	// 线程ID
	pthread_t		m_threadId;	
	// 是否与主线程分离
	bool			m_autoRel;
};

DUYE_POSIX_NS_END

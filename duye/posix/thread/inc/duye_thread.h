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
//  �߳�״̬, ���
enum ThreadState
{
	// ����״̬
	THR_STATE_RUN = 0,
	// ֹͣ״̬
	THR_STATE_STOP,
	// �˳�״̬
	THR_STATE_EXIT
};

// brief:
//  �߳���ں���ָ��
typedef void* (*ThreadFunPoint_t)(void*);

// brief:
//  ʹ�ö��߳�����̳еĽӿ�
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
//  POSIX ���̷߳�װ
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
	
	// brief : �����߳�
	// @para
	// return true/false
	bool Start();

	// brief : ��ȡ�߳�ID
	// @para
	// return �����߳�ID
	pthread_t GetThreadId() const;

	// brief : �����߳�
	// @para entry �߳���ں���ָ��
	// @para argument �̲߳���
	// @para autoRel �Ƿ������̷߳���
	// return �����߳�ID
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
	// brief : ��ֹ����
	Thread(const Thread&);
	void operator=(const Thread&);
	
	// brief : �������߳����
	// @para argument �̲߳���
	// return void*
	static void* EnterPoint(void* argument);

private:
	// �߳�ID
	pthread_t	m_threadId;
	// �Ƿ������̷߳��룬Ĭ�Ϸ���
	bool		m_autoRel;
	// �û����߳���ڶ���
	Runnable*	m_runnable;
};

// brief : ���̻߳���
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
	// brief : ���캯��
	// @para autoRel �Ƿ������̷߳���
	explicit ThreadTask(const bool autoRel = true);
	virtual ~ThreadTask();

	// brief : �����߳�
	// @para
	// return true/false
	bool Start();

	// brief : �߳���ڣ�����ʵ��
	// @para
	// note
	virtual void Run() = 0;

private:
	// brief : ��ֹ����
	ThreadTask(const ThreadTask&);
	void operator=(const ThreadTask&);
	
	// brief : �������߳����
	// @para argument �̲߳���
	// return void*
	static void* EnterPoint(void* argument);	

private:
	// �߳�ID
	pthread_t	m_threadId;	
	// �Ƿ������̷߳��룬Ĭ�Ϸ���
	bool		m_autoRel;
};

DUYE_POSIX_NS_END

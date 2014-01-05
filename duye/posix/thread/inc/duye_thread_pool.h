/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_thread_pool.h
* @version     
* @brief      
* @author   duye
* @date     2013-12-10
* @note 
*
*  1. 2013-12-10 duye Created this file
* 
*/

#pragma once

#include <duye/stl/inc/duye_list.h>
#include <duye/posix/inc/duye_posix_def.h>
#include <duye/posix/thread/inc/duye_thread.h>
#include <duye/posix/thread/inc/duye_condition.h>

DUYE_POSIX_NS_BEG

// default the count of thread pool
static const D_UInt32 g_DefThreadCount = 20;

class ThreadWorker;
class ThreadJob;

// fn : class ThreadPool
//		thread pool implemention
class ThreadPool
{
public:
	typedef duye::stl::List<ThreadWorker*> ThreadWorkerList;

public:
	explicit ThreadPool(const D_UInt32 threadCount = g_DefThreadCount);
	~ThreadPool();

	bool DoJob(ThreadJob* threadJob);
	D_UInt32 GetThreadCount() const;

private:
	void InitThreadPool();
	void MoveToIdleList(const D_UInt32 workerId);
	void MoveToBusyList(const D_UInt32 workerId);

private:
	D_UInt32			m_threadCount;
	ThreadWorkerList		m_idleThreadWorkerList;
	ThreadWorkerList		m_busyThreadWorkerList;
};

// fn : class ThreadWorker
//		thread worker for thread pool
class ThreadWorker : public ThreadTask
{
public:
	explicit ThreadWorker(const D_UInt32 workerId);
	virtual ~ThreadWorker();

	D_UInt32 GetWorkerId() const;
	D_Bool DoWork(ThreadJob* threadJob, void* userData);		

private:
	ThreadWorker(const ThreadWorker&);
	void operator=(const ThreadWorker&);
	
	// fn : work function	
	void Run();

private:
	D_UInt32		m_workerId;
	Condition		m_condition;
	
	ThreadJob*		m_threadJob;	
	void*			m_userData;	
};

// fn : class ThreadJob
//		thread job interface for user inherit
class ThreadJob
{
public:
	~ThreadJob();
	virtual void Work(void* para) = 0;
};

// example :
//

DUYE_POSIX_NS_END

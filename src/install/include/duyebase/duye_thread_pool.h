/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_thread_pool.h
* @version     
* @brief      
* @author   duye
* @date	    2013-12-10
* @note 
*
*  1. 2013-12-10 duye created this file
* 
*/
#pragma once

#include <list>
#include <map>
#include <duye_system.h>
#include <duye_thread.h>
#include <duye_condition.h>

namespace duye {

// default the count of thread pool
static const uint32 MIN_THREAD_COUNT = 2;
static const uint32 DEF_THREAD_COUNT = 20;
static const uint32 MAX_THREAD_COUNT = 100;

/**
 * @brief thread job, be inherited by user
 */
class ThreadJob
{
public:
    ~ThreadJob() {}

    /**
     * @brief do user work
     * @param [in] userData : user data
     * @return true/false
     */  	
    virtual bool work(void* userData) = 0;
};

class ThreadWorker;

/** 
 * @brief thread pool implemention
 */
class ThreadPool
{
public:
    /**
     * @brief thread worker queue
     */      
    typedef std::list<ThreadWorker*> ThreadWorkerList;
    // <workerId, threadWorker*>
    typedef std::map<uint32, ThreadWorker*> ThreadWorkerMap;

public:
    ThreadPool();
    ~ThreadPool();

    /**
     * @brief init thread pool
     * @param [in] threadCount : thread pool count
     * @return true/false
     */       
    bool init(const uint32 threadCount = DEF_THREAD_COUNT);    

    /**
     * @brief start to do user job
     * @param [in] threadJob : user job object
     * @param [in] userData : user data
     * @return true/false
     */       
    bool doJob(ThreadJob* threadJob, void* userData);

    /**
     * @brief get thread count
     * @param [in] threadJob : user job object
     * @param [in] userData : user data
     * @return the count of thread pool
     */ 	
    uint32 getThreadCount() const;
    uint32 getIdleThreadCount() const;
    uint32 getBusyThreadCount() const;

private:
    /**
     * @brief prevent copying
     */     
    ThreadPool(const ThreadPool&);
    void operator=(const ThreadPool&);

    /**
     * @brief initialize thread pool
     * @return true/false
     */       
    bool initThreadPool();

    /**
     * @brief uninitialize thread pool
     * @return true/false
     */  	
    bool uninitThreadPool();

   /**
    * @brief find a idle worker thread
    * @return worker thread ID
    */    
    ThreadWorker* fetchIdleWorker();

    /**
     * @brief move idle thread worker from busy queue to idle queue
     * @param [in] workerId : thread worker ID
     * @return worker moved thread worker
     */ 	
    ThreadWorker* moveToIdleList(const uint32 workerId);

    /**
     * @brief move busy thread worker from idle queue to busy queue
     * @param [in]workerId : thread worker ID
     * @return worker moved thread worker
     */ 	
    ThreadWorker* moveToBusyList();

private:
    friend class ThreadWorker;

    // whether is init thread pool
    bool               m_isInit;
    // thread pool size
    uint32             m_threadCount;
    // the idle queue
    ThreadWorkerList   m_idleThreadWorkerList;
    // the busy queue
    ThreadWorkerMap    m_busyThreadWorkerMap;
    // the worker list mutex
    Mutex              m_workerIdleListMutex;
    Mutex              m_workerBusyMapMutex;
};

/** 
 * @brief thread worker, class ThreadPool depend on 
 */
class ThreadWorker : public ThreadTask
{
public:
    /**
     * @brief constructor
     * @param [in] workerId : worker ID
     */       
    explicit ThreadWorker(ThreadPool* threadPool, const uint32 workerId);
    virtual ~ThreadWorker();

    /**
     * @brief get thread worker ID
     * @param [in] workerId : worker ID
     * @return thread worker ID
     */     
    uint32 workerId() const;

    /**
     * @brief to do work
     * @param [in] threadJob : user thread job
     * @param [in] userData : user data
     * @return true/false
     */  	
    bool doWork(ThreadJob* threadJob, void* userData);		

private:
    /**
     * @brief prevent copying
     */     
    ThreadWorker(const ThreadWorker&);
    void operator=(const ThreadWorker&);

    /**
     * @brief thread entry function
     * @return true/false
     * @note 
     */	
    bool run();

private:
    ThreadPool*     m_threadPool;
    // thread worker ID, setting by external
    uint32       	m_workerId;
    // waitting condition
    Condition  m_condition;
    // current running job
    ThreadJob*      m_threadJob;	
    // current running user data
    void*         	m_userData;	
};
}

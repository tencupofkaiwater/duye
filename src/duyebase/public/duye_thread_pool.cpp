/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_thread_pool.cpp
* @version     
* @brief      
* @author   duye
* @date	    2013-12-10
* @note 
*
* 2. 2014-01-12 duye Modify implemention    
* 1. 2013-12-10 duye Created this file
* 
*/
#include <duye_logger.h>
#include <duye_thread_pool.h> 

static const int8* DUYE_LOG_PREFIX = "duye.public.threadpool";

namespace duye {

ThreadPool::ThreadPool() : m_isInit(false), m_threadCount(0)
{    
}

ThreadPool::~ThreadPool()
{
    uninitThreadPool();   
}

bool ThreadPool::init(const uint32 threadCount)
{
    if (threadCount < MIN_THREAD_COUNT)
    {
        DUYE_WARN("user want to create thread numbers lower than default min numbers, will create min %d threads", MIN_THREAD_COUNT);
        m_threadCount = MIN_THREAD_COUNT;
    }
    else if (threadCount > MAX_THREAD_COUNT)
    {
        DUYE_WARN("user want to create thread numbers over than default max numbers, will create max %d threads", MAX_THREAD_COUNT);
        m_threadCount = MAX_THREAD_COUNT;
    }    
    else
    {
        m_threadCount = threadCount;
    }
    
    m_isInit = initThreadPool();   
    if (m_isInit)
        DUYE_INFO("create thread numbers %d for thread pool", m_threadCount);
    else
        DUYE_ERROR("create thread numbers %d for thread pool failed", m_threadCount);

    return m_isInit;
}

bool ThreadPool::doJob(ThreadJob* threadJob, void* userData)
{
    if (!m_isInit)
        return false;

    DUYE_TRACE("will to find idle worker");
    ThreadWorker* worker = fetchIdleWorker();
    if (worker == NULL)
    {
        DUYE_ERROR("have no idle worker to do current job");
        return false;
    }

    DUYE_TRACE("will to do work");
    return worker->doWork(threadJob, userData);
}

uint32 ThreadPool::getThreadCount() const
{
    return m_threadCount;
}

uint32 ThreadPool::getIdleThreadCount() const
{
    return m_idleThreadWorkerList.size();
}

uint32 ThreadPool::getBusyThreadCount() const
{
    return m_busyThreadWorkerMap.size();
}

bool ThreadPool::initThreadPool()
{
    for (uint32 i = 0; i < m_threadCount; i++)
    {
        ThreadWorker* worker = new ThreadWorker(this, i);
        if (worker != NULL)
        {
    	    m_idleThreadWorkerList.push_back(worker);
            //DUYE_TRACE("create thread worker(id=%d) for thread pool, new thread id = %u", i, worker->threadId());
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool ThreadPool::uninitThreadPool()
{
    {
        AutoLock autoLock(m_workerIdleListMutex);
        ThreadWorkerList::iterator iter = m_idleThreadWorkerList.begin();
        for (; iter != m_idleThreadWorkerList.end(); ++iter)
        {
            if ((*iter) != NULL)
                delete (*iter);
        }
    }

    {
        AutoLock autoLock(m_workerBusyMapMutex);
        ThreadWorkerMap::iterator iter = m_busyThreadWorkerMap.begin();
        for (; iter != m_busyThreadWorkerMap.end(); ++iter)
        {
            if (iter->second != NULL)
            {
                delete (iter->second);
                iter->second = NULL;
            }
        }
    }
    
    return true;    
}

ThreadWorker* ThreadPool::fetchIdleWorker()
{
    uint32 tryTimes = 0;
    // after try 1000 times
    uint32 maxTryTimes = 10;
    
    for (;;)
    {
        if (tryTimes == maxTryTimes)
            return NULL;

        if (m_idleThreadWorkerList.size() > 0)
            break;

        System::msleep(10);
        tryTimes++;
    }

    return moveToBusyList();
}

ThreadWorker* ThreadPool::moveToIdleList(const uint32 workerId)
{
    ThreadWorker* movedWorker = NULL;

    // remove out from busy map
    {
        AutoLock autoLock(m_workerBusyMapMutex);
        ThreadWorkerMap::iterator iter = m_busyThreadWorkerMap.find(workerId);
        if (iter == m_busyThreadWorkerMap.end())
        {
            DUYE_ERROR("can't found thread worker.");
            return NULL;
        }

        movedWorker = iter->second;
        m_busyThreadWorkerMap.erase(iter);
    }   

    // insert to idle list
    {
        AutoLock autoLock(m_workerIdleListMutex);
        m_idleThreadWorkerList.push_back(movedWorker);
    }    

    return movedWorker;
}

ThreadWorker* ThreadPool::moveToBusyList()
{
    ThreadWorker* movedWorker = NULL;   

    // remove out from idle list
    {
        AutoLock autoLock(m_workerIdleListMutex);
        movedWorker = m_idleThreadWorkerList.front();
        m_idleThreadWorkerList.pop_front();
    }

    // insert to busy map
    {
        AutoLock autoLock(m_workerBusyMapMutex);
        m_busyThreadWorkerMap.insert(std::make_pair(movedWorker->workerId(), movedWorker));
    }

    return movedWorker;
}

ThreadWorker::ThreadWorker(ThreadPool* threadPool, const uint32 workerId) 
    : m_threadPool(threadPool)
    , m_workerId(workerId)
    , m_threadJob(NULL)
{
    this->startTask();
}

ThreadWorker::~ThreadWorker() {}

uint32 ThreadWorker::workerId() const
{
    return m_workerId;
}

bool ThreadWorker::doWork(ThreadJob* threadJob, void* userData)
{
    if (threadJob == NULL)
        return false;
    
    m_threadJob = threadJob;
    m_userData = userData;
    return m_condition.signal();
}

bool ThreadWorker::run()
{
    for (;;)
    {
    	m_condition.wait();
        DUYE_TRACE("start do work");
        m_threadJob->work(m_userData);
        DUYE_TRACE("end do work");
        m_threadJob = NULL;
        m_userData = NULL;
        m_threadPool->moveToIdleList(m_workerId);
    }

    return true;
}
}

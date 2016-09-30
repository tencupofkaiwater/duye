/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_thread.h
* @version     
* @brief      
* @autho    duye
* @date	    2013-11-26
* @note 
*
* 2. 2014-01-12 duye Add comments   
* 1. 2013-11-26 duye Created this file
* 
*/
#pragma once

#include <pthread.h> 

#include <duye_type.h>

namespace duye {
	
/** 
 * @brief thread state
 */
enum ThreadState
{
    /** 
     * @brief running state
     */	
    THR_STATE_RUN = 0,
    /** 
     * @brief stoped state
     */		
    THR_STATE_STOP,
    /** 
     * @brief exit state
     */		
    THR_STATE_EXIT
};

/** 
 * @brief the pointer of thread enter
 */
typedef void* (*ThreadFunPoint)(void*);

/** 
 * @brief be inherited ty user
 */
class Runnable
{
public:
    virtual ~Runnable() {}

    /**
     * @brief user thread entry function
     * @return true/false
     * @note 
     */			
    virtual bool run() = 0;
};

/** 
 * @brief POSIX thread wrapper
 */
class Thread
{
public:
    
    /**
     * @brief constructor
     * @param [in] target : user run target object
     * @param [in] autoRel : whether support automatic release, default is yes
     * @note 
     */		
    explicit Thread(const bool autoRel = true);
    explicit Thread(Runnable* target, const bool autoRel = true);
    ~Thread();

    /**
     * @brief startup thread
     * @return true/false
     * @note 
     */		
    bool start();
    bool start(Runnable* target, const bool autoRel = true);
    
    /**
     * @brief join thread
     */
    bool join();
    
    /**
     * @brief exit thread
     */
    void exit();

    /**
     * @brief get thread ID
     * @return thread ID
     * @note 
     */		
    uint32 threadId() const;

private:
    Thread(const Thread&);
    void operator=(const Thread&);
    static void* enterPoint(void* argument);

private: 
    // thread ID
    pthread_t    m_threadId;
    // indicate whether is detached with main thread default is detached
    bool         m_autoRel;
    // user thread object
    Runnable*	 m_runnable;
};

/** 
 * @brief thread base class, be inherited by user
 */
class ThreadTask : public Runnable
{
public:
    /**
     * @brief constructor
     * @para [in] autoRel : whether is detached with main thread, default is detached
     * @note 
     */		
    explicit ThreadTask(const bool autoRel = true);
    virtual ~ThreadTask();
  
    /**
     * @brief startup thread
     * @param [in] autoRel : whether is detached from main thread, default is detached
     * @return true/false
     * @note 
     */		
    bool startTask(const bool autoRel = true);
    
    /**
     * @brief join
     * @return true/false
     */
    bool join();

    /**
     * @brief get thread ID
     * @return thread ID
     */		
    uint32 threadId() const;	

    /**
     * @brief thread entry function
     * @return true/false
     * @note 
     */			
    virtual bool run() = 0;

private:
    // brief : prevate copying
    ThreadTask(const ThreadTask&);
    void operator=(const ThreadTask&);

private:
    Thread m_thread;	
    // whether is detached with main thread, default is ture, 
    // indicate detached with main thread
    bool   m_autoRel;
};

/** 
 * @brief POSIX thread static API used outside
 */
class ThreadUtil
{
public:
    /**
     * @brief create thread
     * @param [in] entry : thread entry fucntion pointer
     * @param [in] argument : user data
     * @param [in] autoRel : whether support automatic release, default is yes
     * @return thread ID / -1
     * @note 
     */		
    static int32 createThread(void* entry, void* argument, const bool autoRel = true);
};
}

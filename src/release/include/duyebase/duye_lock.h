/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_lock.h
* @version     
* @brief      
* @author   duye
* @date	    2013-11-26
* @note 
*
* 4. 2014-06-20 duye move to gohoop project
* 3. 2014-01-09 duye Add comments
* 2. 2014-01-04 duye 
*     a. Modify mutex function trylock to trylock()
*     b. Add function trylock() for class orgLock
*     c. Modify trylock class implimenting
*
* 1. 2013-11-26 duye Created this file
*/

#pragma once

#include <pthread.h>
#include <unistd.h>

#include <duye_type.h>

namespace duye {
	
/** 
 * @brief POSIX mutex wrapper
 */
class Mutex
{
public:
    /**
     * @brief constructor
     * @note default mutex type is PTHREAD_MUTEX_RECURSIVE
     */	
     Mutex();
	
    /**
     * @brief constructor
     * @param [in] kind : mutex type
     * @note have four mutex type, are PTHREAD_MUTEX_NORMAL PTHREAD_MUTEX_RECURSIVE
     * PTHREAD_mutex_ERRORCHECK PTHREAD_MUTEX_DEFAULT
     */		
    explicit Mutex(const int32 kind);

    virtual ~Mutex();
    /**
     * @brief lock mutex, enter to awaited state
     * @return true/false
     * @note 
     */		
    bool lock();
	
    /**
     * @brief try to lock mutex, failure return immediately  
     * @return true/false
     * @note 
     */		
    bool tryLock();
	
    /**
     * @brief release lock
     * @return true/false
     * @note 
     */		
    bool unlock();

private:
    /**
     * @brief to prevent copying
     * @note 
     */			
    Mutex(const Mutex&); 
	
    void operator=(const Mutex&);	
	
    /**
     * @brief initialize mutex
     * @param [in] kind : mutex type, reference constructor function
     * @note 
     */		
    void init(const int32 kind);
    
private:
    pthread_mutex_t	m_mutex;	
};

/** 
 * try lock wrapper
 */
class TryLock
{
public:
    /**
     * @brief constructor
     * @param [in] mutex : mutex
     * @param [in] autoUnlock : whether release lock automatic
     * @note 
     */		
    TryLock(Mutex& Mutex, const bool autoUnlock = true);
	
    ~TryLock();

    /**
     * @brief try lock
     * @param [in] timeout : try lock timeout, default is zero, indicate try once, 
     * then return immediately
     * @return true/false
     * @note 
     */		
    bool lock(const uint32 timeout = 0);

    /**
     * @brief release lock
     * @return true/false
     * @note if construct a release lock, invoke invalid
     */			
    bool unlock();

private:
    /**
     * @brief prevent copying
     * @note
     */	
    TryLock(const TryLock&); 

    /**
     * @brief prevent copying
     * @note
     */		
    void operator=(const TryLock&);	
    
private:
    Mutex&	m_mutex;
    bool	m_autoUnlock;
};

/** 
 * @brief auto lock wrapper
 */
class AutoLock
{
public:
    /**
     * @brief constructor
     * @param [in]mutex : mutex
     * @note 
     */			
    explicit AutoLock(Mutex& mutex);
    ~AutoLock();

private:
    /**
     * @brief prevent copying
     * @note
     */		
    AutoLock(const AutoLock&);

    /**
     * @brief prevent copying
     * @note
     */			
    void operator=(const AutoLock&);

private:
    Mutex&      m_mutex;
};
}

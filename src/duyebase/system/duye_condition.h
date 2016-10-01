/************************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_condition.h
* @version     
* @brief      
* @author   duye
* @date     2014-06-20
* @note 
*
*  1. 2014-06-20 duye Created this file
* 
*/

#pragma once

#include <sys/time.h>
#include <pthread.h>

#include <duye_type.h>

namespace duye {
	
/** 
 * POSIX condition wrapper
 */
class Condition 
{
public:
    Condition();
    ~Condition();

    /**
     * @brief wake up the waitting thread, only wake up one thread,
     * according to the thread priority and waitting time.
     * @return true/false
     * @note 
     */ 
    bool signal();
	 
    /**
     * @brief wake up all waitting threads
     * @return true/false
     * @note 
     */		
    bool broadcast();

    /**
     * @brief let current thread has reached the awaited state, utill be wake up
     * @return true/false
     * @note 
     */		
    bool wait();

    /**
     * @brief let current thread has reached the awaited state,
     * utill be wake up or timeout return
     * @param [in] timeout : waitting timeout
     * @return true/false
     * @note 
     */	
    bool wait(const uint32 timeout);

private: 
    /**
     * @brief for to prevent copying
     * @return true/false
     * @note 
     */		
    Condition(const Condition&); 

    /**
     * @brief prevent copying
     * @note
     */	
    void operator=(const Condition&);	
    
private:
    pthread_cond_t    m_condition;
    pthread_mutex_t   m_mutex;	
};
}

/***************************************************************************
**  
*    @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_condition.h
* @version     
* @brief      
* @author   duye
* @date     2013-12-22
* @note 
*
*  1. 2013-12-22 duye Created this file
* 
*/

#pragma once

#include <sys/time.h>
#include <pthread.h>
#include <duye/posix/inc/duye_posix_def.h> 
#include <duye/posix/thread/inc/duye_lock.h> 

DUYE_POSIX_NS_BEG

class Condition 
{
public:
	Condition();
	~Condition();

	// fn : wake up one waitting thread by the thread priority 
	bool Signal();
	
	// fn : wake up all waitting thread
	bool Broadcast();
	
	// fn : to wait condition changed
	bool Wait();
	
	// fn : to wait condition changed with timeout
	bool Wait(const D_UInt32 timeout);

private:
	Condition(const Condition&); 
	void operator=(const Condition&);	
    
private:
	pthread_cond_t		m_condition;
	pthread_mutex_t		m_mutex;	
};

DUYE_POSIX_NS_END

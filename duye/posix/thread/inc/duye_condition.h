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
*  2. 2014-01-09 duye Add comments
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

// brief:POSIX 条件变量封装
//	
// usage:
//	Condition myCond;
//  
//  void ThreadOne()
//  {
//      if (!myCond.Wait())
//      {
//          return;
//      }
//      
//      // to do
//  }
//
//  void ThreadTwo()
//  {
//      sleep(1);
//      myCond.Signal();
//  }
// 
class Condition 
{
public:
	Condition();
	~Condition();

	// brief:唤醒等待线程，只能唤醒一个等待线程，根据线程优先级和等待时长选择
	// @para
	// @return true/false
	// note:
	bool Signal();
	
	// brief:唤醒所有等待线程
	// @para
	// @return true/false
	// note:
	bool Broadcast();
	
	// brief:使当前线程进入等待状态，直到被唤醒
	// @para
	// @return true/false
	// note:
	bool Wait();
	
	// brief:使当前线程进入等待状态，直到被唤醒或超时返回
	// @para [in] timeout 等待超时时间
	// @return true/false
	// note:
	bool Wait(const D_UInt32 timeout);

private:
	// brief:防拷贝
	// @para 
	// @return 
	// note:
	Condition(const Condition&); 
	void operator=(const Condition&);	
    
private:
	pthread_cond_t		m_condition;
	pthread_mutex_t		m_mutex;	
};

DUYE_POSIX_NS_END

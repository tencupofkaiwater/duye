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

// brief:POSIX ����������װ
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

	// brief:���ѵȴ��̣߳�ֻ�ܻ���һ���ȴ��̣߳������߳����ȼ��͵ȴ�ʱ��ѡ��
	// @para
	// @return true/false
	// note:
	bool Signal();
	
	// brief:�������еȴ��߳�
	// @para
	// @return true/false
	// note:
	bool Broadcast();
	
	// brief:ʹ��ǰ�߳̽���ȴ�״̬��ֱ��������
	// @para
	// @return true/false
	// note:
	bool Wait();
	
	// brief:ʹ��ǰ�߳̽���ȴ�״̬��ֱ�������ѻ�ʱ����
	// @para [in] timeout �ȴ���ʱʱ��
	// @return true/false
	// note:
	bool Wait(const D_UInt32 timeout);

private:
	// brief:������
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

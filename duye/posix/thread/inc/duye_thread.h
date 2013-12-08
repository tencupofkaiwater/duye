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
#include <duye/posix/thread/inc/duye_lock.h>

DUYE_POSIX_NS_BEG

class Thread
{
public:
    Thread();
    ~Thread();

	bool Start();
	bool Stop();
	bool Kill();

	virtual void* Run(void* para) = 0;
	
	// fn : Create new thread
	// @entry : the fun of thread entry
	// @para : input parameter
	// ret : return true when create sucessed, else return  
	static bool Create(void* entry, void* para);
};

DUYE_POSIX_NS_END

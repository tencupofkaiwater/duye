/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_thread.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-11-26
* @note 
*
*  1. 2013-11-26 duye Created this file
* 
*/

#include <duye/posix/thread/inc/duye_thread.h> 

DUYE_POSIX_NS_BEG

Thread::Thread() 
{
}

Thread::~Thread()
{
}

bool Thread::Start()
{
	return true;
}

bool Thread::Stop()
{
	return true;
}

bool Thread::Kill()
{
	return true;
}

bool Thread::Create(void* entry, void* para)
{
	return true;
}

DUYE_POSIX_NS_END

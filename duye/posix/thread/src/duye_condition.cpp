/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_condition.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-12-22
* @note 
*
*  1. 2013-12-22 duye Created this file
* 
*/

#include <duye/posix/thread/inc/duye_condition.h>

DUYE_POSIX_NS_BEG

//----------------------------class Condition-------------------------//
Condition::Condition()
{
	pthread_cond_init(&m_condition, NULL);
	pthread_mutex_init(&m_mutex, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&m_condition);
	pthread_mutex_destroy(&m_mutex);
}

DUYE_POSIX_NS_END

/************************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_semaphore.cpp
* @version     
* @brief      
* @author   duye
* @date     2014-06-20
* @note 
*
*  1. 2014-06-20 duye created this file
* 
*/
#include <time.h>
#include <duye_semaphore.h>

namespace duye {
	
Semaphore::Semaphore()
{
    // 2st paramater not equal to zero indicate shared in process
    // otherwise shared in all thread in current process
    // 3st paramater is the initialization value of semaphore
    sem_init(&m_sem, 0, 0);
}

Semaphore::~Semaphore()
{
    sem_destroy(&m_sem);
}

bool Semaphore::wait()
{
    return sem_wait(&m_sem) == 0 ? true : false;
}

bool Semaphore::tryWait()
{
    return sem_trywait(&m_sem) == 0 ? true : false;
}

bool Semaphore::timedWait(const uint64 timeout)
{
    struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
	        return false;
	
    ts.tv_sec += timeout / 1000;
    ts.tv_nsec += (timeout % 1000) * 1000000;
    return sem_timedwait(&m_sem, &ts) == 0 ? true : false;	
}

bool Semaphore::post()
{
    return sem_post(&m_sem) == 0 ? true : false;
}

}

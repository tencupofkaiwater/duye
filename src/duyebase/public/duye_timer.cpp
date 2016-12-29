/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_timer.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-19
* @note 
*
*  1. 2016-04-19 duye created this file
* 
*/
#include <duye_sys.h>
#include <duye_logger.h>
#include <duye_timer.h>

static const int8* DUYE_LOG_PREFIX = "duye.public.timer";

namespace duye {

TimerServer::TimerServer() : m_isRunning(false) {}
TimerServer::~TimerServer() {}

TimerServer& TimerServer::instance()
{
    static TimerServer ins;
    return ins;
}

bool TimerServer::startServer()
{
    if (m_isRunning)
        return true;
    
    this->startTask();
    return true;
}

bool TimerServer::registerTimer(TimerIf* timerIf, const uint32 timeout)
{
    if (timerIf == NULL)
        return false;

    AutoLock autoLock(m_timerDataListMutex);
    m_timerUserMap.erase(timerIf);
    m_timerUserMap.insert(std::make_pair(timerIf, TimerData(timeout, timerIf)));

    return true;
}

bool TimerServer::cancelTimer(TimerIf* timerIf) {
    if (timerIf == NULL)
        return false;
	
    AutoLock autoLock(m_timerDataListMutex);
    m_timerUserMap.erase(timerIf);
	return true;
}

bool TimerServer::updateTimer(TimerIf* timerIf, const uint32 timeout) {
    AutoLock autoLock(m_timerDataListMutex);
    TimerUserMap::iterator iter = m_timerUserMap.find(timerIf);
    if (iter == m_timerUserMap.end()) {
        return false;
    }

    iter->second.timeout = timeout;
    iter->second.incTime = 0;
    return true;    
}

bool TimerServer::run()
{
    DUYE_INFO("TimerServer Thread:%u start", threadId());

    m_isRunning = true;

    // millisecond
    uint32 period = 10;
    
    for (;;)
    {
        System::msleep(period);
        if (m_timerUserMap.empty()) {
            continue;
        }

        AutoLock autoLock(m_timerDataListMutex);
        TimerUserMap::iterator iter = m_timerUserMap.begin();
        while (iter != m_timerUserMap.end())
        {
            if (iter->second.incTime >= iter->second.timeout)
            {
                iter->first->onTimeout(iter->second.timeout);
                iter = m_timerUserMap.erase(iter);
                continue;
            }

            iter->second.incTime += period;
            iter++;
        }
    }

	return true;
}

}

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
#include <duye_timer.h>

namespace duye {

TimerServer::TimerServer() { startServer(); }
TimerServer::~TimerServer() {}

TimerServer& TimerServer::instance()
{
    static TimerServer ins;
    return ins;
}

bool TimerServer::startServer()
{
    this->startTask();
    return true;
}

bool TimerServer::registerTimer(TimerIf* timerIf, const uint32 timeout)
{
    if (timerIf == NULL)
        return false;

    AutoLock autoLock(m_timerDataListMutex);
    m_timerDataList.push_back(TimerData(timeout, timerIf));

    return true;
}

bool TimerServer::run()
{
    // millisecond
    uint32 period = 10;
    
    for (;;)
    {
        System::msleep(period);
        AutoLock autoLock(m_timerDataListMutex);
        TimerDataList::iterator iter = m_timerDataList.begin();
        while (iter != m_timerDataList.end())
        {
            if (iter->incTime == iter->timeout)
            {
                iter->user->onTimeout(iter->timeout);
                m_timerDataList.erase(++iter);
                continue;
            }

            iter->incTime -= period;
            iter++;
        }
    }

	return true;
}

}

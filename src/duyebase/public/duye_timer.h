/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_timer.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-19
* @note 
*
*  1. 2016-04-19 duye created this file
* 
*/
#pragma once

#include <map>
#include <duye_type.h>
#include <duye_lock.h>
#include <duye_thread.h>

namespace duye {

class TimerIf
{
public:
    virtual ~TimerIf() {}
    virtual bool onTimeout(const uint32 timeout) = 0;
};

class TimerData
{
public:
    TimerData() : timeout(0), incTime(0), user(NULL) {}
    TimerData(const uint32 intimeout, TimerIf* inuser) 
        : timeout(intimeout), incTime(0), user(inuser) {}
    ~TimerData() {}

    uint32     timeout;
    uint32     incTime;
    TimerIf*   user;
};


/**
 * @brief string extend function
 * @note
 */
class TimerServer : public ThreadTask
{
public:
    typedef std::map<TimerIf*, TimerData> TimerUserMap;
    
public:
	TimerServer();
    ~TimerServer();

    static TimerServer& instance();

    /**
     * @brief register timer
     * @param [in] timeout : time out
     * @param [in] userData : user data
     */
    bool startServer();
     
    /**
     * @brief register timer
     * @param [in] timerIf : user
     * @param [in] timeout : time out, millisecond     
     */
    bool registerTimer(TimerIf* timerIf, const uint32 timeout);
	
    /**
     * @brief cancel timer
     * @param [in] timerIf : user
     */
	bool cancelTimer(TimerIf* timerIf);

    /**
     * @brief update timer
     * @param [in] timerIf : user
     */
    bool updateTimer(TimerIf* timerIf, const uint32 timeout);

private:
    // implementation from ThreadTask
    virtual bool run();

private:
    TimerUserMap   m_timerUserMap;
    Mutex          m_timerDataListMutex;
    bool           m_isRunning;
};

}

/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_process.h
* @version     
* @brief      
* @author   duye
* @date	    2014-10-11
* @note 
*
*  1. 2014-10-11 duye created this file
* 
*/
#pragma once

#include <list>
#include <duye_system.h>
#include <duye_singleton.h>

namespace duye {

/**
 * @brief process monitor interface
 */
class ProcessIf
{
public:
    virtual ~ProcessIf() {}
    virtual void onSegFault() = 0;
    virtual void onCtrlC() = 0;
    virtual void onOther(const int32 sig) = 0;
};

typedef enum 
{
	PROCESS_RUNING,
	PROCESS_EXIT
} ProcessStatus;

/**
 * @biref process
 */
class Process : public Singleton<Process>, public ProcessSysCallbackObserver
{
public:
    typedef std::list<ProcessIf*> ProcessIfList;
    
public:    
    Process();
    ~Process();
    
    /**
     * @brife addition process  
     * @param [in] observer : process observer
     */
    void addObserver(ProcessIf* observer);

    /**
     * @brief remove process 
     * @param [in] observer : process observer
     */
    void removeObserver(ProcessIf* observer);
    
    /**
     * @brief setting the number of one process can open files
     * @param [in] num : can open file number
     * @return true/false
     */
    void setLimitFile(const uint32 num);
    uint32 limitFile() const;
    
    /**
     * @brief wait process exit
     * @param [in] timeout : wait time, default is 10 seconds
     * @return On process exit, return true, else if return false
     */
    bool wait(const uint32 timeout = 10);
    
    /**
     * @brief wakeup all current thread
     */
    void wakeup();
    
private:
    // inherit from base class system::ProcessSysCallbackObserver 
    // system signal handler
    void onSignalHandler(const SignalType sigType);
    
private:    
    ProcessSysCallback 	m_processSysCallback;
    ProcessIfList       m_observerList;
	Mutex				m_observerListMutex;
    Condition           m_exitCondition;
    SysProcess          m_sysProcess;
	ProcessStatus		m_processStatus;
};

}

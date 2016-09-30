/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_sys_process.h
* @version     
* @brief      
* @author   duye
* @date	    2014-09-28
* @note 
*
*  1. 2014-09-28 duye Created this file
* 
*/
#pragma once

#include <duye_type.h>

namespace duye {
    
/**
 * @brief signal type
 */
typedef enum
{
    D_SIGSEGV,
    D_SIGINT,
    D_SIG
} SignalType;

/**
 * @brief system callback observer
 */
class SysProcess
{
public:
    SysProcess();
    ~SysProcess();
    
    /**
     * @brief setting the number of one process can open files
     * @param [in] limitFile : can open file number
     * @return true/false
     */
    bool setLimitFile(const uint32 limitFile);  
    uint32 limitFile() const;
    
private:
    uint32    m_limitFile;
};

/**
 * @brief system callback observer
 */
class ProcessSysCallbackObserver
{
public:
    virtual ~ProcessSysCallbackObserver() {}

    /**
     * @brief system signal handler
     * @param [in] sig : signal
     */    
    virtual void onSignalHandler(const SignalType sig) = 0;
};

/**
 * @biref process monitor for system API callback
 */
class ProcessSysCallback
{
public:
    ProcessSysCallback();
    ~ProcessSysCallback();
    
    /**
     * @brief regist process system callback observer
     * @param [in] observer : observer
     */
    void registObserver(ProcessSysCallbackObserver* observer);
    
    /**
     * @brief system signal callback
     * @param [in] sig : signal
     */
    static void signalHandler(const int32 sig);

private:
    static ProcessSysCallbackObserver*  m_observer;
};

}

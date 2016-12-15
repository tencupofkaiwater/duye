/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_sys_process.cpp
* @version     
* @brief      
* @author   duye
* @date     2014-09-28
* @note 
*
*  1. 2014-09-28 duye Created this file
* 
*/
#include <signal.h>
#include <unistd.h>
#include <sys/resource.h>

#include <duye_sys_process.h>

namespace duye {

static const uint32 DEF_LIMIT_FILE = 10240;

ProcessSysCallbackObserver* ProcessSysCallback::m_observer = NULL;

SysProcess::SysProcess()
{
    setLimitFile(DEF_LIMIT_FILE);   	
}

SysProcess::~SysProcess() {}

bool SysProcess::setLimitFile(const uint32 limitFile)
{
    m_limitFile = limitFile;
	
    struct rlimit rt;
    rt.rlim_max = rt.rlim_cur = m_limitFile;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
    {
        return false;
    }    	
    
    return true;
}

uint32 SysProcess::limitFile() const
{
    return m_limitFile;	
}

ProcessSysCallback::ProcessSysCallback()
{
    // segmentation fault
    signal(SIGSEGV, ProcessSysCallback::signalHandler);
	
    // ctrl + c
    signal(SIGINT, ProcessSysCallback::signalHandler);
}

ProcessSysCallback::~ProcessSysCallback() {}

void ProcessSysCallback::registObserver(ProcessSysCallbackObserver* observer)
{
    m_observer = observer;
}

void ProcessSysCallback::signalHandler(const int32 sig)
{
    if (m_observer == NULL)
    	return;

	SignalType signalType = D_SIG;
	switch (sig)
	{
	case SIGSEGV:
		signalType = D_SIGSEGV;
		break;
	case SIGINT:
		signalType = D_SIGINT;
		break;
	default:
		signalType = D_SIG;
		break;
	}
	
    m_observer->onSignalHandler(signalType);
}

}

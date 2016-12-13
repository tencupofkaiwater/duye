/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_process.cpp
* @version     
* @brief      
* @author   duye
* @date     2014-10-11
* @note 
*
*  1. 2014-10-11 duye created this file
* 
*/
#include <duye_process.h>

namespace duye {

Process::Process() : m_processStatus(PROCESS_RUNING)
{
    m_processSysCallback.registObserver(this);
}

Process::~Process()
{
    m_observerList.clear();
}

void Process::addObserver(ProcessIf* observer)
{
    if (observer == NULL)
		return;
	
    AutoLock autoLock(m_observerListMutex); 
    ProcessIfList::iterator iter = m_observerList.begin();
    for (; iter != m_observerList.end(); ++iter)
    {
        if (*iter == observer)
        {
            return;
        }
    }   
    
    m_observerList.push_back(observer);
}

void Process::removeObserver(ProcessIf* observer)
{
    if (observer == NULL)
		return;
		
    AutoLock autoLock(m_observerListMutex);
    m_observerList.remove(observer);
}

void Process::setLimitFile(const uint32 num)
{
    m_sysProcess.setLimitFile(num);   
}

uint32 Process::limitFile() const
{
    return m_sysProcess.limitFile();
}

bool Process::wait(const uint32 timeout)
{
    m_exitCondition.wait(timeout * 1000);
	return m_processStatus == PROCESS_EXIT ? true : false;
}

void Process::wakeup()
{
    m_exitCondition.broadcast();
}
    
void Process::onSignalHandler(const SignalType sigType)
{
    AutoLock autoLock(m_observerListMutex);
    ProcessIfList::iterator iter = m_observerList.begin();
    for (; iter != m_observerList.end(); ++iter)
    {
    	switch (sigType)
        {
	    case D_SIGSEGV:
	    	(*iter)->onSegFault();
			m_processStatus = PROCESS_EXIT;
	    	break;
	    case D_SIGINT:
	    	(*iter)->onCtrlC();
			m_processStatus = PROCESS_EXIT;
	     	break;
	    default:
	    	(*iter)->onOther(sigType);
	    	break;
        }
    }    

	wakeup();
}
}

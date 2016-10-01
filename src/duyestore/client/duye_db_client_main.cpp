/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_client_main.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-26
* @note 
*
* 1. 2016-04-26 duye Created this file
*/
#include <duye_logger.h>
#include <duye_system.h>
#include <duye_process.h>
#include <duye_db_client.h>

static const int8* DUYE_LOG_PREFIX = "duyefour.db.client";

class DBClientProcessSignal : public duye::ProcessIf
{
public:
	DBClientProcessSignal() {}
	virtual ~DBClientProcessSignal() {}
	
    virtual void onSegFault()
	{
		DUYE_WARN("process received a segmentation fault, program exit.");
	}
	
    virtual void onCtrlC()
	{
		DUYE_WARN("process received exit at Ctrl+C, program exit.");
	}
	
    virtual void onOther(const int32 sig)
	{
		DUYE_WARN("process received a signal %d", sig);	
	}
};

int main(int argc, char **argv)
{
    DBClientProcessSignal signal;
    duye::Process process;
    process.addObserver(&signal);
    
    if (!DUYE_LOG_INIT(NULL))
    {
        printf("%s \n", DUYE_LOG_EDESP());
        return -1;
    }

    duye::DBClient dbClient;
    while (!process.wait());
    
    DUYE_INFO("TwoServer process exit");
    DUYE_LOG_UNINIT();

    return 0;
}

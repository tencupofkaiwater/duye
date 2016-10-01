/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_file_server_test.h
* @version     
* @brief      
* @author   duye
* @date     2016-04-05
* @note 
*
*  1. 2016-04-05 duye Created this file
* 
*/
#include <duye_logger.h>
#include <duye_system.h>
#include <duye_process.h>
#include <duyetwo_server.h>

static const int8* DUYE_LOG_PREFIX = "duyetwo.main";

class TwoServerProcessSignal : public duye::ProcessIf
{
public:
	TwoServerProcessSignal() {}
	virtual ~TwoServerProcessSignal() {}
	
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

int main()
{
	TwoServerProcessSignal signal;
	duye::Process process;
	process.addObserver(&signal);
	
	if (!DUYE_LOG_INIT("/etc/duyetwo/duyetwo_log.xml"))
    {
        printf("%s \n", DUYE_LOG_EDESP());
        return -1;
	}

	duyetwo::TwoServer twoServer;
	if (!twoServer.initServer())
    {
       DUYE_ERROR("twoServer.initServer() failed, program exit.");
       return -1;
    }
	
	if (!twoServer.startServer())
    {
       DUYE_ERROR("twoServer.startServer() failed, program exit.");
       return -1;
    }

	while (!process.wait());
	
	twoServer.stopServer();
	DUYE_INFO("TwoServer process exit");
 	DUYE_LOG_UNINIT();
    
    return 0;
}

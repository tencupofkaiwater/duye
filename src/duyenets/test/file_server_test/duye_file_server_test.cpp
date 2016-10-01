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
#include <duye_file_server.h>

static const int8* DUYE_LOG_PREFIX = "duyeone.test.fileserver";

class FileServerProcessSignal : public duye::ProcessIf
{
public:
	FileServerProcessSignal() {}
	virtual ~FileServerProcessSignal() {}
	
    virtual void onSegFault()
	{
		DUYE_ERROR("process a segmentation fault");
	}
	
    virtual void onCtrlC()
	{
		DUYE_ERROR("process exit at Ctrl+C");
	}
	
    virtual void onOther(const int32 sig)
	{
		DUYE_ERROR("process generate a signal %d", sig);	
	}
};

int main()
{
	if (!DUYE_LOG_INIT("/root/work/duyeone/test/file_server_test/test_file_server_log.xml"))
    {
        printf("%s \n", DUYE_LOG_EDESP());
        return -1;
    }

	FileServerProcessSignal signal;
	duye::Process process;
	process.addObserver(&signal);
	
    DUYE_INFO("Test File Server Start");

    duye::FileServerPara serverParm;
    serverParm.serverAddr = "192.168.1.146";
    serverParm.serverPort = 10000;
    serverParm.concurrent = 1000;
    
    duye::FileServer fileServer;   
    if (!fileServer.initServer(serverParm))
    {
       DUYE_ERROR("fileServer.initServer failed");
       return -1;
    }

    DUYE_INFO("fileServer.initServer %s:%d OK", serverParm.serverAddr.c_str(), serverParm.serverPort);

    if (!fileServer.startServer())
    {
       DUYE_ERROR("fileServer.startServer failed");
       return -1;
    }    

    DUYE_INFO("fileServer.startServer OK");

	while (process.wait()) break;
	
    DUYE_ERROR("Test File Server Stoped");
    
    DUYE_LOG_UNINIT();
    
    return 0;
}

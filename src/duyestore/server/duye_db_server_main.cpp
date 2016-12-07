/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_server_main.cpp
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
#include <duye_db_server.h>

static const int8* DUYE_LOG_PREFIX = "duye.db.server.main";

// db service system config file full path
static const int8* DB_SERVICE_CONF_FILE = "/etc/duyedbserver/duyedbserver.xml";

// db service system log config file full path
static const int8* DUYE_LOG_CONF_FILE = "/etc/duyedbserver/duyedbserver_log.xml";

class DBServerProcessSignal : public duye::ProcessIf
{
public:
	DBServerProcessSignal() {}
	virtual ~DBServerProcessSignal() {}
	
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
    DBServerProcessSignal signal;
    duye::Process process;
    process.addObserver(&signal);
    
    if (!DUYE_LOG_INIT(DUYE_LOG_CONF_FILE))
    {
        printf("%s \n", DUYE_LOG_EDESP());
        return -1;
    }

    DUYE_INFO("DBServer process start");
    
    duye::DBServer dbServer;
    if (!dbServer.initServer(DB_SERVICE_CONF_FILE))
    {
       DUYE_ERROR("dbserver.initServer() failed");
       return -1;
    }
    
    if (!dbServer.startServer())
    {
       DUYE_ERROR("dbserver.startServer() failed");
       return -1;
    }

    while (!process.wait());
    
    dbServer.stopServer();
    DUYE_INFO("DBServer process exit");
    DUYE_LOG_UNINIT();
    
	return 0;
}

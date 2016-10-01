/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		logger_test.cpp
* @version     
* @brief      
* @author	duye
* @date		2016-03-31
* @note 
*
*  1. 2016-03-31 duye created this file
* 
*/
#include <stdarg.h>
#include <duye_system.h>
#include <duye_logger.h>

static const int8* DUYE_LOG_PREFIX = "duye.test.logger";

int main()
{
	if (!DUYE_LOG_INIT("/root/work/duyezero/test/logger_test/test_log_conf.xml"))
    {
        printf("%s \n", DUYE_LOG_EDESP());
        return -1;
    }

	uint32 a = 10;
	const int8* test = "asdfasdfasdf";
	
    DUYE_ERROR("error log %d", a);  
	DUYE_ERROR("error log %s", test);
    DUYE_WARN("warn log %d", a);   
	DUYE_WARN("warn log %s", test); 
    DUYE_INFO("info log %d", a);   
	DUYE_INFO("info log %s", test); 
    DUYE_DEBUG("debug log %d", a);   
	DUYE_DEBUG("debug log %s", test); 
    DUYE_TRACE("trance log %d", a);   
	DUYE_TRACE("trance log %s", test); 

    DUYE_LOG_UNINIT();
    
    return 0;
}

/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_sys.h
* @version     
* @brief      
* @author   duye
* @date	    2014-03-04
* @note 
*
*  1. 2014-03-04 duye Created this file
* 
*/
#pragma once

#include <string.h>
#include <string>
#include <map>

#include <duye_type.h>

#define ERROR_DUYE_LOG(args...) System::pformat((char*)m_error.errorLog, m_error.errorBufSize, ##args);
#define ERROR_DUYE_LOGE(err, args...) System::pformat((char*)err.errorLog, err.errorBufSize, ##args);

namespace duye {

class Error
{
public:
	Error() : errorLog(NULL), errorBufSize(0) {
		uint32 size = snprintf((char*)error, ERROR_BUF_SIZE, "\033[1;31;40m[error]\033[0m");	
		error[size] = 0;
		errorBufSize = ERROR_BUF_SIZE - size - 1;
		errorLog = error + size;
	}
	
	~Error() {}

	void setPrefix(const int8* prefix) {
		if (prefix == NULL) return;
		
		uint32 size = snprintf((char*)error, ERROR_BUF_SIZE, "\033[1;31;40m[error]\033[0m<%s>", prefix);		
		error[size] = 0;
		errorBufSize = ERROR_BUF_SIZE - size - 1;
		errorLog = error + size;
	}

	uint8	error[ERROR_BUF_SIZE];	
	uint8*	errorLog;
	uint32  errorBufSize;
};

class System
{
public:
    /**
     * @brief sleep
     * @param [in] time : second
     * @note 
     */		
    static void sleep(const uint64& time);

    /**
     * @brief usleep
     * @param [in] time : millisecond
     * @note 
     */		
    static void msleep(const uint64& time);    
    
    /**
     * @brief usleep
     * @param [in] time : microsecond
     * @note 
     */		
    static void usleep(const uint64& time);
    
    /**
     * @brief format
     * @param [out] buffer : out buffer
     * @param [in] size : out buffer size
     * @param [in] args : parameters
     * @return string size, error : -1
     * @note 
     */		
    static int64 pformat(int8* buffer, const uint64 size, const int8* args, ...);   
    
    /**
     * @brief execute shell command
     * @param [in] cmd : shell command
     * @param [out] result : output buffer
     * @param [in] result_size : output buffer size
     * @return : On success, return the number of read bytes. The number equals to zero when shell 
     *	         execute print empty. or -1 if an error occurred.
     */
    static int32 shell(const int8* cmd, int8* result , const uint32 result_size);
	
    /**
     * @brief execute shell command
     * @param [out] cmd_len : command length
     * @param [out] result : output buffer
     * @param [in] result_size : output buffer size
     * @param [in] args : args list
     * @return : On success, return the number of read bytes. The number equals to zero when shell 
     *	         execute print empty. or -1 if an error occurred.
     */	
    static int32 shell(const int8* args, ...);
	static int32 shell(const uint32 cmd_len, const int8* args, ...);
	static int32 shell(std::string& result, const int8* args, ...);
	static int32 shell(const uint32 cmd_len, std::string& result, const int8* args, ...);
	static int32 shell(const uint32 cmd_len, int8* result, const uint32 result_size, const int8* args, ...);
	
    /**
     * @brief get system time
     * @return time(microsecond)
     * @note 
     */		
    static uint64 sysTime();
    
    /**
     * @brief get options
     * @param [in] argc : argument count
     * @param [in] argv : argument list
     * @param [in] cmd : need parser command
     * @param [out] value : out value
     * @return true/false
     */
    static bool optArg(int32 argc, int8** argv, int8* cmd, int64& value);
    static bool optArg(int32 argc, int8** argv, int8* cmd, uint64& value);
    static bool optArg(int32 argc, int8** argv, int8* cmd, std::string& value);

    /**
     * @brief create daemon process
     * @note 
     */		
    static void daemonize();

    /**
     * @brief limit process CPU resource usage
     * @param [in] process_name : process name
     * @param [in] cpu_percent : CPU limit percent
     * @return true/false
     * @note 
     */	
    static bool limitCpu(const char* process_name, const uint16 cpu_percent);
    
    /**
     * @brief get ip address by physical network card name
     * @param [in] phyCardName : physical network card name
     * @param [out] ipAddr : ip address
     * @return true/false
     * @note 
     */	
    static bool getIPAddrByDevName(const std::string& phyCardName, std::string& ipAddr);

    /**
     * @brief get first valid ip address
     * @param [out] ipAddr : ip address
     * @return true/false
     * @note 
     */	
    static bool getFirstValidIPAddr(std::string& ipAddr);

    /**
     * @brief get first valid ip address
     * @param [out] networkCards : <network_card_name, ip_address>
     * @return true/false
     * @note 
     */	
    static bool getNetworkCards(std::map<std::string, std::string>& networkCards);

	static uint32 getPid();
	static uint32 getPPid();
};
}

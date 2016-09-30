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

namespace duye {

class Error
{
public:
	explicit Error(const int8* prefix) : errorLog(NULL), errorBufSize(0) 
	{
		uint32 size = 0;
		if (prefix != NULL)
			size = snprintf(error, ERROR_BUF_SIZE, "\033[1;31;40m<error>\033[0m<%s>", prefix);
		else
			size = snprintf(error, ERROR_BUF_SIZE, "\033[1;31;40m<error>\033[0m");
		
		error[size] = 0;
		errorBufSize = ERROR_BUF_SIZE - size - 1;
		errorLog = error + size;	
	}
	
	~Error() {}

	int8	error[ERROR_BUF_SIZE];	
	int8*	errorLog;
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
     * @brief usleep
     * @param [out] buffer : out buffer
     * @param [in] size : out buffer size
     * @param [in] args : parameters
     * @return string size, error : -1
     * @note 
     */		
    static int64 pformat(int8* buffer, const uint64 size, const int8* args, ...);   
    
    /**
     * @brief execute system command line
     * @param [in] cmd : command
     * @param [out] buffer : output buffer
     * @param [in] size : output buffer size
     * @return true/false
     */
    static bool shell(const int8* cmd, int8* buffer = NULL, const uint32 size = 0);   
    
    /**
     * @brief get system time
     * @return time(microsecond)
     * @note 
     */		
    static uint64 sysTime();
    
    /**
     * @brief getopt
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
     * @brief get system time
     * @return time(microsecond)
     * @note 
     */		
    static void daemonize();
    
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
};
}

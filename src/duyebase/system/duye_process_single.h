/***********************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		duye_process_single.h
* @version     
* @brief      
* @author   wangwei
* @date     2015-4-21
* @note 
*
*  1. 2015-4-21 wangwei created this file
* 
*/
#pragma once

#include <string>

namespace duye {

/*
 * @brief : process single
 */
class ProcessSingle {
public:
	ProcessSingle();
	~ProcessSingle();

	/*
	 * @brief: Check whether there is a process in the system.
	 * @param [in] process_name: process name.
	 * @return : On has the process, return true, or false.
	 */
	bool hasProcess(const char* process_name);

	/*
	 * @brief: Synchronization PID, when the process crearte daemon process, need to call this 
	 * 		   function to synchronize PID to configuration.
	 * @return : On success, return true, or false.
	 */
	bool syncPid();

private:
	std::string m_process_name;
	bool m_is_release;
};
}

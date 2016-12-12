/***********************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		duye_process_single.cpp
* @version     
* @brief      
* @author   wangwei
* @date     2015-4-21
* @note 
*
*  1. 2015-4-21 wangwei created this file
* 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <duye_sys.h>
#include <duye_file.h>
#include <duye_process_single.h>

namespace duye {

const static char* g_process_single = "/tmp/process_single/";

ProcessSingle::ProcessSingle() : m_is_release(false) {
	if (!FileUtil::isExist(g_process_single)) {
		FileUtil::createDir(g_process_single);
	}
}

ProcessSingle::~ProcessSingle() {
	if (m_is_release) {
		FileUtil::removeFile(std::string(g_process_single + m_process_name + ".pid").c_str());
	}
}

bool ProcessSingle::hasProcess(const char* process_name) {
	m_process_name = process_name;	
	std::string conf_file = std::string(g_process_single) + process_name + ".pid";
	if (FileUtil::isExist(conf_file.c_str())) {
		std::string pid;
		if (System::shell(pid, "cat %s", conf_file.c_str()) < 0) {
			printf("[error] cat %s error.", conf_file.c_str());
			return false;
		}

		std::string result;
		if (System::shell(result, "ps aux | grep -v grep | grep %s | grep %s", process_name, pid.c_str()) > 0) {
			printf("[info] has exist process %s pid:%s \n", process_name, pid.c_str());
			return true;
		}
	}

	syncPid();
	m_is_release = true;
	
	return false;
}

bool ProcessSingle::syncPid() {
	pid_t pid = getpid();
	std::string conf_file = g_process_single + m_process_name + ".pid";
	if (System::shell("echo %d > %s", pid, conf_file.c_str()) < 0) {
		return false;
	}

	return true;
}
}

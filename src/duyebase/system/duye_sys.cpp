/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_sys.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-03-04
* @note 
*
*  1. 2014-03-04 duye Created this file
* 
*/
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <duye_sys.h>
#include <duye_logger.h>
#include <duye_helper.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.system.sys";

void System::sleep(const uint64& time)
{
	//struct timespec slptm;
	//slptm.tv_sec = time;
	//slptm.tv_nsec = 0;
    //::nanosleep(&slptm, NULL);
    ::sleep(time);
}

void System::msleep(const uint64& time)
{
	//struct timespec slptm;
	//slptm.tv_sec = 0;
	//slptm.tv_nsec = time * 1000 * 1000;
    //::nanosleep(&slptm, NULL);
    ::usleep(time * 1000);
}

void System::usleep(const uint64& time)
{
	//struct timespec slptm;
	//slptm.tv_sec = 0;
	//slptm.tv_nsec = time * 1000;
    //::nanosleep(&slptm, NULL);
    ::usleep(time);
}

int64 System::pformat(int8* buffer, const uint64 size, const int8* args, ...)
{
	if (buffer == NULL || size == 0)
		return -1;

    va_list vaList;
    va_start(vaList, args);
    uint64 strLen = vsnprintf(buffer, size, args, vaList);
    va_end(vaList);	
	buffer[strLen] = 0;
	
    return strLen; 
}

int32 System::shell(const int8* cmd, int8* buffer, const uint32 size)
{
    if (cmd == NULL) {
    	DUYE_ERROR("cmd == NULL");
        return -1;
    }

    FILE* file = popen(cmd, "r");
    if (file == NULL) {
    	DUYE_ERROR("file == NULL");
        return -1;
    }

    if (buffer == NULL || size == 0) {
    	DUYE_DEBUG("buffer == NULL || size == 0");
        pclose(file);
        return 0;
    }

    memset(buffer, 0, size);
    size_t bytes = fread(buffer, sizeof(char), size, file);
    pclose(file);

    return bytes;
}

int32 System::shell(const int8* args, ...) {
	int8 cmd[1024] = {0};
	
    va_list vaList;
    va_start(vaList, args);
    uint64 strLen = vsnprintf(cmd, 1024, args, vaList);
    va_end(vaList);	
	cmd[strLen] = 0;

	return System::shell(cmd, NULL, 0);
}

int32 System::shell(const uint32 cmd_len, const int8* args, ...) {
	int8* cmd = new int8[cmd_len];
	memset(cmd, 0, cmd_len);
	
    va_list vaList;
    va_start(vaList, args);
    uint64 strLen = vsnprintf(cmd, cmd_len, args, vaList);
    va_end(vaList);	
	cmd[strLen] = 0;

	return System::shell(cmd, NULL, 0);
}

int32 System::shell(std::string& result, const int8* args, ...) {
	int8 cmd[1024] = {0};
	
    va_list vaList;
    va_start(vaList, args);
    uint64 strLen = vsnprintf(cmd, 1024, args, vaList);
    va_end(vaList);	
	cmd[strLen] = 0;

	int8 ret[4096] = {0};
	int32 len = System::shell(cmd, ret, sizeof(ret));
	if (len > 0) {
		result.assign(ret);
	}
	
	return len;
}

int32 System::shell(const uint32 cmd_len, std::string& result, const int8* args, ...) {
	int8* cmd = new int8[cmd_len];
	memset(cmd, 0, cmd_len);
	
    va_list vaList;
    va_start(vaList, args);
    uint64 strLen = vsnprintf(cmd, cmd_len, args, vaList);
    va_end(vaList);	
	cmd[strLen] = 0;

	int8 ret[4096] = {0};
	int32 len = System::shell(cmd, ret, sizeof(ret));
	if (len > 0) {
		result.assign(ret);
	}
	
	delete [] cmd;
	return len;
}

int32 System::shell(const uint32 cmd_len, int8* result, const uint32 result_size, const int8* args, ...) {
	int8* cmd = new int8[cmd_len];
	memset(cmd, 0, cmd_len);
	
    va_list vaList;
    va_start(vaList, args);
    uint64 strLen = vsnprintf(cmd, cmd_len, args, vaList);
    va_end(vaList);	
	cmd[strLen] = 0;
	
	int32 len = System::shell(cmd, result, result_size);
	delete [] cmd;
	return len;
}

uint64 System::sysTime()
{
    struct timeval now;
    struct timezone tz;
    if (gettimeofday(&now, &tz) < 0)
    {
    	return 0;
    }
	
    return (uint64)(now.tv_sec) * 1000000 + now.tv_usec;
}

bool System::optArg(int32 argc, int8** argv, int8* cmd, int64& value)
{
	if (argv == NULL || cmd == NULL)
		return false;
	
    if (getopt(argc, argv, cmd) != cmd[0])
    {
    	return false;
    }
	
    const std::string tempStr(optarg);
    value = (int64)std::stoi(tempStr);
    return true;
}

bool System::optArg(int32 argc, int8** argv, int8* cmd, uint64& value)
{
	if (argv == NULL || cmd == NULL)
		return false;
	 
    if (getopt(argc, argv, cmd) != cmd[0])
    {
    	return false;
    }
    
    const std::string temp_str(optarg);
    value = (uint64)std::stoi(temp_str);	
    return true;
}

bool System::optArg(int32 argc, int8** argv, int8* cmd, std::string& value)
{
	if (argv == NULL || cmd == NULL)
		return false;
	
    if (getopt(argc, argv, cmd) != cmd[0])
    {
    	return false;
    }
	
    value.assign(optarg);
    return true;
}

void System::daemonize()
{
	// Clear file creation mask.
	umask(0);
	
	// Get maximum number of file descriptors.
	struct rlimit rl;
	getrlimit(RLIMIT_NOFILE, &rl);
	
	// Become a session leader to lose controlling TTY.
	pid_t pid = -1;
	if ((pid = fork()) < 0)
	{
		//
	}
	else if (pid != 0)
	{
        // parent
		exit(0);
	}
    
	// Ensure future opens won't allocate controlling TTYs
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGHUP, &sa, NULL);

	if ((pid = fork()) < 0)
	{
		//
	}
	else if (pid != 0)
	{
        // parent
		exit(0);
	}
	
	// Change the current working directory to the root so
	// we won't prevent file systems from being unmounted.
	if (chdir("/") < 0)
	{
		//
	}
	
	// Close all open file descriptors
	if (rl.rlim_max == RLIM_INFINITY)
	{
		rl.rlim_max = 1024;
	}
    
	for (uint32 i = 0; i < rl.rlim_max; i++)
	{
		close(i);
	}

	// Attach file descriptors 0, 1, and 2 to /dev/null
	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);
}

bool System::limitCpu(const char* process_name, const uint16 cpu_percent) {
	if (cpu_percent < 1 || cpu_percent > 99) {
        return false;
    }
	
	std::string conf_dir_base;
	if (access("/sys/fs/cgroup/cpu/cpu.cfs_period_us", F_OK) == 0) {
		conf_dir_base = "/sys/fs/cgroup/cpu/";
	} else if (access("/cgroup/cpu/cpu.cfs_period_us", F_OK) == 0) {
		conf_dir_base = "/cgroup/cpu/";
	} else {
		return false;
	}

	pid_t pid = getpid();
    std::string conf_dir = conf_dir_base + process_name;
    uint32 quota = cpu_percent * 1000;

    return System::shell("mkdir -p %s; echo %u > %s/cpu.cfs_quota_us; echo %d > %s/tasks",
		conf_dir.c_str(), quota, conf_dir.c_str(), pid, conf_dir.c_str()) == 0;
}

bool System::getIPAddrByDevName(const std::string& phyCardName, std::string& ipAddr)
{
    int32 sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        return false;

    struct ifreq req;
    bzero(&req, sizeof(struct ifreq));
    strcpy(req.ifr_name, phyCardName.c_str());
    if (ioctl(sockfd, SIOCGIFADDR, &req) == -1)
        return false;
    
    struct sockaddr_in* host = (struct sockaddr_in*)&req.ifr_addr;
    ipAddr.assign(inet_ntoa(host->sin_addr));
    close(sockfd);
 
    return true;
}

bool System::getFirstValidIPAddr(std::string& ipAddr)
{
    std::map<std::string, std::string> networkCards;
    if (!getNetworkCards(networkCards))
        return false;
    if (networkCards.empty())
        return false;

    ipAddr = networkCards.begin()->second;
    
    return true;
}

bool System::getNetworkCards(std::map<std::string, std::string>& networkCards)
{
    int32 sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        return false;

    int8 buff[BUFSIZ] = {0};
    struct ifconf conf;
    conf.ifc_len = BUFSIZ;
    conf.ifc_buf = buff;
    ioctl(sockfd, SIOCGIFCONF, &conf);

    int32 num = conf.ifc_len / sizeof(struct ifreq);
    struct ifreq* ifr = conf.ifc_req;
    for (int32 i = 0; i < num; i++)
    {
        struct sockaddr_in *sin = (struct sockaddr_in *)(&ifr->ifr_addr);
        ioctl(sockfd, SIOCGIFFLAGS, ifr);
        if (((ifr->ifr_flags & IFF_LOOPBACK) == 0) && (ifr->ifr_flags & IFF_UP))
        {
            networkCards[ifr->ifr_name] = inet_ntoa(sin->sin_addr);
        }
        ifr++;
    }    
    
    return true;
}

uint32 System::getPid() {
	return (uint32)getpid();
}

uint32 System::getPPid() {
	return (uint32)getppid();
}

bool System::getSysInfo(std::string& name, std::string& version) {
	// start get system name 
	const int8* sys_list[] = {"ubuntu", "centos", "fedora", "rhel", "suse", "asianux", "debian", "oraclelinux"};
	int8 desc_str[1024] = {0};
	if (shell("cat /etc/issue", desc_str, sizeof(desc_str)) <= 0) {
		DUYE_ERROR("cat /etc/issue <= 0");
		return false;
	}

	bool found = false;
	StrHelper::strlwr(desc_str);
	std::string lower_desc(desc_str);
	const int8* rhel = "red hat enterprise linux";
	for (uint32 i = 0; i < sizeof(sys_list)/sizeof(int8*); i++) {
		const int8* temp = sys_list[i];
		if (strcmp(temp, "rhel") == 0) {
			temp = rhel;
		}
	
		if (lower_desc.find(temp) != std::string::npos) {
			name.assign(sys_list[i]);
			found = true;
		}
	}

	if (!found) {
		if (shell("cat /etc/redhat-release", desc_str, sizeof(desc_str)) <= 0) {
			DUYE_ERROR("cat /etc/redhat-release <= 0");
			return false;
		}

		StrHelper::strlwr(desc_str);
		std::string lower_desc(desc_str);
		const int8* rhel = "red hat enterprise linux";
		for (uint32 i = 0; i < sizeof(sys_list)/sizeof(int8*); i++) {
			const int8* temp = sys_list[i];
			if (strcmp(temp, "rhel") == 0) {
				temp = rhel;
			}
		
			if (lower_desc.find(temp) != std::string::npos) {
				name.assign(sys_list[i]);
				found = true;
			}
		}
	} 

	if (!found) {
		DUYE_ERROR("don't found system name");
		return false;
	}

	// end get system name

	// start get system version
	int8 version_temp[32] = {0};
	uint32 ver_len = 0;
	if (name == "ubuntu") {
		// ubuntu centos oracle
		if ((ver_len = shell("cat /etc/lsb-release | grep DISTRIB_RELEASE | awk -F '=' '{print $2}'", 
			version_temp, sizeof(version_temp))) <= 0) {
			DUYE_ERROR("[cat /etc/lsb-release | grep DISTRIB_RELEASE | awk -F '=' '{print $2}'] <= 0");
			return false;
		}
	} else {
		if ((ver_len = shell("cat /etc/issue | grep release | awk '{for (i = 1; i < NF; i++) if ($i == \"release\") print $(i+1)}'", 
				version_temp, sizeof(version_temp))) <= 0) {

			DUYE_TRACE("[cat /etc/issue | grep release | awk '{for (i = 1; i < NF; i++) if ($i == \"release\") print $(i+1)}'] <= 0");
			if ((ver_len = shell("cat /etc/redhat-release | grep release | awk '{for (i = 1; i < NF; i++) if ($i == \"release\") print $(i+1)}'", 
				version_temp, sizeof(version_temp))) <= 0) {
				DUYE_ERROR("[cat /etc/redhat-release | grep release | awk '{for (i = 1; i < NF; i++) if ($i == \"release\") print $(i+1)}'] <= 0");
				return false;
			}
		}
	}

	version_temp[ver_len - 1] = 0;
	version.assign(version_temp);
	// end get system version

	return true;
}

void System::manMalloc() {
	malloc_trim(0);
}

}

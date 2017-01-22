/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_net_rw.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-27
* @note 
*
* 1. 2016-12-27 duye Created this file
*/

#pragma once

#include <duye_buffer.h>

namespace duye {

class NetRW {
public:
	typedef enum {
		// init status
		RW_INIT,	
		// read finished
		RD_FINISHED,
		// buffer overflow
		RD_OVERFLOW,
		// write finished
		WR_FINISHED,	
		// socket fd closeed
		FD_CLOSEED
	} NetRWStatus;

public:
	/**
	 * @brief read data from socket fd
	 * @param [in] fd : socket fd
	 * @param [out] buffer : save read data
	 * @param [in] size : buffer size
	 * @aaram [out] status : socket fd status
	 * @param [in] block : default nonblock
	 * @return read size / -1
	 * @note 
	 */
	static int64 read(const int32 fd, Buffer& buffer, NetRWStatus& status, const bool block = false);
	static int64 read(const int32 fd, int8* buffer, const uint32 size, NetRWStatus& status, const bool block = false);
	/**
	 * @brief write data to socket fd
	 * @param [in] fd : socket fd
	 * @param [in] data : send data
	 * @param [in] len : data len
	 * @aaram [out] status : socket fd status
	 * @param [in] block : default nonblock
	 * @return read size / -1
	 * @note 
	 */
	static int64 write(const int32 fd, const Buffer& data, NetRWStatus& status);
	static int64 write(const int32 fd, const int8* data, const uint32 len, NetRWStatus& status);

	/**
	 * @brief close socket fd
	 * @param [in] fd : socket fd
	 * @return true/false
	 * @note 
	 */
	static bool close(const int32 fd);
};

}


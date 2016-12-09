/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_buffer.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-9
* @note 
*
* 1. 2016-12-9 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_sys.h>

namespace duye {

class Buffer {
public:
	Buffer();
	Buffer(const uint32 size);
	Buffer(Buffer Buffer& buffer);
	~Buffer();

	bool init(const uint32 size);
	uint8* data();
	uint32 size();
	bool empty();
	uint8* copy(uint8* buffer, const uint32 size);
	
	/**
	 * @brief get error description.
	 * @return error description.
	 */
	uint8* getError();

private:
	Error m_error;
	uint8* m_data;
	uint32 m_size;
};

}
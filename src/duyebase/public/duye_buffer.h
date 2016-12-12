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
	Buffer(const Buffer& buffer);
	~Buffer();

	bool init(const uint32 size);
	int8* data();
	int8* data() const;
	uint32 size();
	uint32 size() const;
	bool empty();
	bool empty() const;
	int8* copy(int8* buffer, const uint32 size);
	int8* copy(int8* buffer, const uint32 size) const;
	
	/**
	 * @brief get error description.
	 * @return error description.
	 */
	uint8* getError();

private:
	Error m_error;
	int8* m_data;
	uint32 m_size;
};

}
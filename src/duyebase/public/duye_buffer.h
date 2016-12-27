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

namespace duye {

class Buffer {
public:
	Buffer();
	Buffer(const uint32 capacity);
	Buffer(const int8* data, const uint32 len);
	Buffer(const Buffer& buffer);
	~Buffer();

	bool resize(const uint32 capacity);
	bool append(const int8* data, const uint32 len);
	int8* data();
	int8* data() const;
	uint32 size();
	uint32 size() const;
	uint32 capacity();
	uint32 capacity() const;
	bool empty();
	bool empty() const;

private:
	int8* m_data;
	uint32 m_capacity;
	uint32 m_size;
};

}
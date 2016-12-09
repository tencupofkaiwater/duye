/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_buffer.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-9
* @note 
*
* 1. 2016-12-9 duye Created this file
*/
#include <string.h>
#include <duye_buffer.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyebase.buffer";

Buffer::Buffer() : m_data(NULL), m_size(0) {}

Buffer::Buffer(const uint32 size) : m_data(NULL), m_size(0) {
	init(size);
}

Buffer::Buffer(Buffer Buffer& buffer) {
	if (init(buffer.m_size)) {
		m_size = buffer.m_size;
		buffer.copy(m_data, m_size);
	}	
}

Buffer::~Buffer() {
	if (!m_data) {
		delete [] m_data;
		m_data = NULL;
	}
}

bool Buffer::init(const uint32 size) {
	m_data = new uint8[size];
	if (!m_data) {
		ERROR_DUYE_LOG("new memory failed");
	} else {
		m_size = size;
	}	
}

uint8* Buffer::data() {
	return m_data;
}

uint32 Buffer::size() {
	return m_size;
}

bool Buffer::empty() {
	return m_size == 0;
}

uint8* Buffer::copy(int8* buffer, const uint32 size) {
	if (!buffer) {
		ERROR_DUYE_LOG("input parameter 'buffer' is NULL");
		return NULL;
	}
	
	if (size == 0) {
		ERROR_DUYE_LOG("input parameter 'size' is 0");
		return NULL;
	}

	if (!m_data) {
		ERROR_DUYE_LOG("member 'm_data' is NULL");
		return NULL;		
	}

	if (m_size == 0) {
		ERROR_DUYE_LOG("member 'm_size' is 0");
		return NULL;		
	}	
	
	memcpy(m_data, buffer, size > m_size ? m_size : size);
	
	return buffer;
}

uint8* Buffer::getError() {
	return m_error.error;
}

}
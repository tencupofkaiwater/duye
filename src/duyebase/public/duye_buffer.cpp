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

Buffer::Buffer() : m_data(NULL), m_capacity(0), m_size(0)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

Buffer::Buffer(const uint32 size) : m_data(NULL), m_capacity(0), m_size(0) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
	init(size);	
}

Buffer::Buffer(const Buffer& buffer) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
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

bool Buffer::init(const uint32 capacity) {
	m_data = new int8[capacity];
	if (!m_data) {
		ERROR_DUYE_LOG("new memory failed");
		return false;
	} else {
		m_capacity = capacity;
	}

	return true;
}

bool Buffer::append(const int8* data, const uint32 len) {
	if (m_size + len >= m_capacity) {
		ERROR_DUYE_LOG("Buffer capacity(%d) too small", m_capacity);
		return false;
	}

	memcpy(m_data + m_size, data, len);
	m_size += len;
	return true;
}

int8* Buffer::data() {
	return m_data;
}

int8* Buffer::data() const {
	return m_data;
}

uint32 Buffer::size() {
	return m_size;
}

uint32 Buffer::size() const {
	return m_size;
}

bool Buffer::empty() {
	return m_size == 0;
}

bool Buffer::empty() const {
	return m_size == 0;
}

int8* Buffer::copy(int8* buffer, const uint32 size) {
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

int8* Buffer::copy(int8* buffer, const uint32 size) const {
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

uint8* Buffer::error() {
	return m_error.error;
}

}
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
#include <duye_logger.h>
#include <duye_buffer.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyebase.buffer";
static const uint32 DEF_CAPACITY_SIZE = 1024;

Buffer::Buffer() : m_data(NULL), m_capacity(DEF_CAPACITY_SIZE), m_size(0) {
	resize(m_capacity);
}

Buffer::Buffer(const uint32 capacity) : m_data(NULL), m_capacity(capacity), m_size(0) {
	resize(capacity);
}

Buffer::Buffer(const int8* data, const uint32 len) : m_data(NULL), m_capacity(DEF_CAPACITY_SIZE), m_size(0) {
	m_capacity = (m_capacity >= len ? m_capacity : len);
	if (resize(m_capacity)) {
		append(data, len);
	}	
}

Buffer::Buffer(const Buffer& buffer) : m_data(NULL), m_capacity(DEF_CAPACITY_SIZE), m_size(0) {
	if (resize(buffer.m_capacity)) {
		append(buffer.data(), buffer.size());
	}	
}

Buffer::~Buffer() {
	if (!m_data) {
		delete [] m_data;
		m_data = NULL;
	}
}

bool Buffer::resize(const uint32 capacity) {
	if (m_data) {
		delete [] m_data;
		m_data = NULL;
		m_capacity = 0;
		m_size = 0;
	}
	
	m_data = new int8[capacity];
	if (!m_data) {
		DUYE_ERROR("malloc memory failed");
		return false;
	} else {
		memset(m_data, 0, capacity);
		m_capacity = capacity;
	}

	return true;
}

bool Buffer::append(const int8* data, const uint32 len) {
	DUYE_TRACE("m_data >>> \n%s", m_data);
	if (m_capacity > 0 && m_size + len > m_capacity) {
		DUYE_ERROR("Buffer capacity(%d) too small", m_capacity);
		return false;
	}

	if (!m_data) {
		DUYE_ERROR("Buffer don't malloc, call resize()");
		return false;
	}

	memcpy(m_data + m_size, data, len);
	m_size += len;

	DUYE_TRACE("m_data >>> \n%s", m_data);

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

uint32 Buffer::capacity() {
	return m_capacity;
}

uint32 Buffer::capacity() const {
	return m_capacity;
}

bool Buffer::empty() {
	return m_size == 0;
}

bool Buffer::empty() const {
	return m_size == 0;
}

/*
int8* Buffer::copy(int8* buffer, const uint32 size) const {
	if (!buffer) {
		DUYE_ERROR("input parameter 'buffer' is NULL");
		return NULL;
	}
	
	if (size == 0) {
		DUYE_ERROR("input parameter 'size' is 0");
		return NULL;
	}

	if (!m_data) {
		DUYE_ERROR("member 'm_data' is NULL");
		return NULL;		
	}

	if (m_size == 0) {
		DUYE_ERROR("member 'm_size' is 0");
		return NULL;		
	}	
	
	memcpy(m_data, buffer, size > m_size ? m_size : size);
	
	return buffer;
}
*/

}
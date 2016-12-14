/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_library.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-06-20
* @note 
*
*  1. 2014-06-20 duye Created this file
* 
*/
#include <duye_library.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.system.library";

Library::Library() : m_libHandle(NULL)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

Library::~Library()
{
	if (m_libHandle) {
		dlclose(m_libHandle);
	}
}

bool Library::open(const int8* libPath, const int32 flags)
{
	if (!libPath) {
		ERROR_DUYE_LOG("input libPath is NULL");
		return NULL;
	}
	
    m_libHandle = dlopen(libPath, flags);
	int8* error = dlerror();
	if (!m_libHandle || error) {
		ERROR_DUYE_LOG("dlopen error:%s", error);
		return false;
	}

	return true;
}

void* Library::getSym(const int8* enter) {
	if (!enter) {
		ERROR_DUYE_LOG("input enter is NULL");
		return NULL;
	}

	if (!m_libHandle) {
		ERROR_DUYE_LOG("library not open");
		return NULL;
	}	
	
	void* address = dlsym(m_libHandle, enter);
	int8* error = dlerror();
	if (!address || error) {
		ERROR_DUYE_LOG("dlsym error:%s", error);
		return NULL;		
	}

	return address;
}

uint8* Library::error() {
	return m_error.error;
}

}

/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_library.h
* @version     
* @brief      
* @author   duye
* @date     2014-06-20
* @note 
*
*  1. 2014-06-20 duye Created this file
* 
*/
#pragma once

#include <dlfcn.h>
#include <duye_sys.h>
#include <duye_type.h>

namespace duye {

/** 
 * shared GLibrary wrapper
 */
class Library
{
public:
    Library();
    ~Library();

    /**
     * @brief load shared GLibrary
     * @param [in] libPath : library path
     * @param [in] flags : RTLD_LAZY|RTLD_NOW
     * @return true/false
     * @note 
     */		
    bool open(const int8* libPath, const int32 flags = RTLD_LAZY);

	void* getSym(const int8* enter);

	uint8* error();

private:
	Error m_error;
	std::string m_libPath;
	void* m_libHandle;
};
}

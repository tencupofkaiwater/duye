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
     * @return handle/NULL
     * @note 
     */		
    static void* open(const int8* libPath, const int32 flags = RTLD_LAZY);

    /**
     * @brief close shared library
     * @param [in] handle : library handle
     * @return true/false
     * @note 
     */		
    static bool close(void* handle);
};
}

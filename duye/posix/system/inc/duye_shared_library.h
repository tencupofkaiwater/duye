/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_shared_library.h
* @version     
* @brief      
* @author   duye
* @date     2014-03-19
* @note 
*
*  1. 2014-03-19 duye Created this file
* 
*/

#pragma once

#include <dlfcn.h>

#include <string>

#include <duye/posix/inc/duye_posix_def.h>

DUYE_POSIX_NS_BEG

// brief : shared library wrapper
class SharedLibrary
{
public:
    SharedLibrary();
    ~SharedLibrary();

 	// brief : load shared library
	// @para [in]libFilePath : library path
	// @para [in]flags : RTLD_LAZY|RTLD_NOW
	// @return library handle on success, or NULL on error
    static D_Void* OpenLib(const std::string& libFilePath, const D_Int32 flags = RTLD_LAZY);

 	// brief : close shared library
	// @para [in]handle : library handle
	// @return 0 on success, or -1 on error    
    static D_Bool CloseLib(D_Void* handle);
};

DUYE_POSIX_NS_END

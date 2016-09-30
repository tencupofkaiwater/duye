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

Library::Library()
{
}

Library::~Library()
{
}

void* Library::open(const int8* libPath, const int32 flags)
{
    return dlopen(libPath, flags);
}

bool Library::close(void* handle)
{
    return dlclose(handle) == 0 ? true : false;    
}
}

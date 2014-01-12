/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_bytemem.h
* @version     
* @brief      
* @author   duye
* @date     2013-12-1
* @note 
*
*  1. 2013-12-1 duye Created this file
* 
*/

#pragma once

#include <duye/stl/inc/duye_stl_def.h>

DUYE_STL_NS_BEG 

class Bytemem
{
public:
	Bytemem();
	~Bytemem();

	static D_UInt32 Strlen(const D_Int8* str); 
	static D_Int8* Strcpy(D_Int8* dstStr, const D_Int8* srcStr);
	static bool Strcmp(D_Int8* str1, D_Int8* str2); 
	static void Memset(D_Int8* str, const D_Int8 ch, D_UInt32 size); 
	static D_Int8* Memcpy(D_Int8* dstStr, const D_Int8* srcStr, const D_UInt32 size); 
	static bool Memcmp(D_Int8* str1, D_Int8* str2, D_UInt32 size); 
};

DUYE_STL_NS_END 

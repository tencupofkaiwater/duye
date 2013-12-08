/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
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

	static UInt32_t StrLen(const Int8_t* str); 
	static Int8_t* Strcpy(Int8_t* dstStr, const Int8_t* srcStr);
	static void Memset(Int8_t* str, const Int8_t ch, UInt32_t size); 
	static Int8_t* Memcpy(Int8_t* dstStr, const Int8_t* srcStr, UInt32_t size); 
};

DUYE_STL_NS_END 

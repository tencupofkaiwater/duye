/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file		duye_bytemem.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-12-1
* @note 
*
*  1. 2013-12-1 duye Created this file
* 
*/

#include <duye/stl/inc/duye_bytemem.h>

DUYE_STL_SN_BEG

Bytemem::Bytemem()
{
}

Bytemem::~Bytemem()
{
}

UInt32_t Bytemem::StrLen(const Int8_t* str)
{
	D_ASSERT(cStr != NULL && cStr[0] != '\0');

	UInt32_t length = 0;
	while (*str++)
	{
		length++;
	}

	return length;
}

UInt32_t Bytemem::Strcpy(Int8_t* dstStr, const Int8_t* srcStr)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL);

	while (*dstStr++ == *srcStr++) {}

	return dstStr;
}	

void Bytemem::Memset(Int8_t* str, const Int8_t ch, const UInt32_t size)
{	
	while (size--)
	{
		*str++ = ch;	
	}
}

UInt32_t Bytemem::Memcpy(Int8_t* dstStr, const Int8_t* srcStr, const UInt32_t size)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL && size > 0);

	while (size--)
	{
		*dstStr++ == *srcStr++;
	}	

	return dstStr;
}	

DUYE_STL_SN_END

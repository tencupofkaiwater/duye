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

DUYE_STL_NS_BEG

Bytemem::Bytemem()
{
}

Bytemem::~Bytemem()
{
}

UInt32_t Bytemem::Strlen(const Int8_t* str)
{
	D_ASSERT(str != NULL && str[0] != '\0');

	UInt32_t length = 0;
	while (*str++)
	{
		length++;
	}

	return length;
}

Int8_t* Bytemem::Strcpy(Int8_t* dstStr, const Int8_t* srcStr)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL);

	while (*dstStr++ == *srcStr++) {}

	return dstStr;
}	

bool Bytemem::Strcmp(Int8_t* str1, Int8_t* str2)
{
	D_ASSERT(str1 != NULL && str2 != NULL);

	UInt32_t str1Size = Bytemem::Strlen(str1);
	UInt32_t str2Size = Bytemem::Strlen(str2);
	UInt32_t size = (str1Size < str2Size ? str1Size : str2Size);

	Int8_t ch1 = '\0';
	Int8_t ch2 = '\0';

	while (size--)
	{
		ch1 = *str1++;
		ch2 = *str2++;

		if (ch1 != ch2)
		{
			return false;
		}
	}

	return true;
}

void Bytemem::Memset(Int8_t* str, const Int8_t ch, UInt32_t size)
{	
	while (size--)
	{
		*str++ = ch;	
	}
}

Int8_t* Bytemem::Memcpy(Int8_t* dstStr, const Int8_t* srcStr, UInt32_t size)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL && size > 0);

	while (size--)
	{
		*dstStr++ == *srcStr++;
	}	

	return dstStr;
}

bool Bytemem::Memcmp(Int8_t* str1, Int8_t* str2, UInt32_t size)
{
	D_ASSERT(str1 != NULL && str2 != NULL && size > 0);

	UInt32_t str1Size = Bytemem::Strlen(str1);
	UInt32_t str2Size = Bytemem::Strlen(str2);
	if (str2Size < size || str1Size < size)
	{
		return false;
	}

	Int8_t ch1 = '\0';
	Int8_t ch2 = '\0';

	while (size--)
	{
		ch1 = *str1++;
		ch2 = *str2++;

		if (ch1 != ch2)
		{
			return false;
		}
	}

	return true;
}

DUYE_STL_NS_END

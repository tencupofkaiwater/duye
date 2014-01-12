/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
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

D_UInt32 Bytemem::Strlen(const D_Int8* str)
{
	D_ASSERT(str != NULL && str[0] != '\0');

	D_UInt32 length = 0;
	while (*str++)
	{
		length++;
	}

	return length;
}

D_Int8* Bytemem::Strcpy(D_Int8* dstStr, const D_Int8* srcStr)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL);

	while (*dstStr++ == *srcStr++) {}

	return dstStr;
}	

bool Bytemem::Strcmp(D_Int8* str1, D_Int8* str2)
{
	D_ASSERT(str1 != NULL && str2 != NULL);

	D_UInt32 str1Size = Bytemem::Strlen(str1);
	D_UInt32 str2Size = Bytemem::Strlen(str2);
	D_UInt32 size = (str1Size < str2Size ? str1Size : str2Size);

	D_Int8 ch1 = '\0';
	D_Int8 ch2 = '\0';

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

void Bytemem::Memset(D_Int8* str, const D_Int8 ch, D_UInt32 size)
{	
	while (size--)
	{
		*str++ = ch;	
	}
}

D_Int8* Bytemem::Memcpy(D_Int8* dstStr, const D_Int8* srcStr, D_UInt32 size)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL && size > 0);

	while (size--)
	{
		*dstStr++ == *srcStr++;
	}	

	return dstStr;
}

bool Bytemem::Memcmp(D_Int8* str1, D_Int8* str2, D_UInt32 size)
{
	D_ASSERT(str1 != NULL && str2 != NULL && size > 0);

	D_UInt32 str1Size = Bytemem::Strlen(str1);
	D_UInt32 str2Size = Bytemem::Strlen(str2);
	if (str2Size < size || str1Size < size)
	{
		return false;
	}

	D_Int8 ch1 = '\0';
	D_Int8 ch2 = '\0';

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

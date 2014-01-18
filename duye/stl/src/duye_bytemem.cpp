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

D_UInt32 Bytemem::Strlen(const D_Int8* str)
{
	D_ASSERT(str != NULL);

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

D_Int32 Bytemem::Strcmp(D_Int8* str1, D_Int8* str2)
{
	D_ASSERT(str1 != NULL && str2 != NULL);

	D_UInt32 str1Size = Bytemem::Strlen(str1);
	D_UInt32 str2Size = Bytemem::Strlen(str2);
	if (str1Size < str2Size)
	{
	    return -1;
	}
	
	D_Int8 ch1 = '\0';
	D_Int8 ch2 = '\0';

	while (str2Size--)
	{
		ch1 = *str1++;
		ch2 = *str2++;

        if (ch1 > ch2)
        {
            return 1;
        }
		else if (ch1 < ch2)
		{
			return -1;
		}
	}

	return 0;
}

void Bytemem::Memset(D_Int8* str, const D_Int8 ch, D_UInt32 size)
{	
    D_ASSERT(str != NULL);
	while (size--)
	{
		*str++ = ch;	
	}
}

D_Int8* Bytemem::Memcpy(D_Int8* dstStr, const D_Int8* srcStr, D_UInt32 size)
{
	D_ASSERT(srcStr != NULL && dstStr != NULL);

	while (size--)
	{
		*dstStr++ == *srcStr++;
	}	

	return dstStr;
}

D_Int32 Bytemem::Memcmp(D_Int8* str1, D_Int8* str2, D_UInt32 compareLen)
{
	D_ASSERT(str1 != NULL && str2 != NULL);

	D_UInt32 str1Size = Bytemem::Strlen(str1);
	D_UInt32 str2Size = Bytemem::Strlen(str2);

	if (str1Size < str2Size)
	{
	    return -1;
	}

    D_ASSERT(compareLen <= str2Size);

	D_Int8 ch1 = '\0';
	D_Int8 ch2 = '\0';

	while (compareLen--)
	{
		ch1 = *str1++;
		ch2 = *str2++;

        if (ch1 > ch2)
        {
            return 1;
        }
		else if (ch1 < ch2)
		{
			return -1;
		}
	}

	return 0;
}

D_Int32 Bytemem::FindSubStr(D_Int8* dstStr, D_Int8* srcStr, const D_Bool reverse)
{ 
    return FindSubStr(dstStr, Bytemem::Strlen(dstStr), srcStr, Bytemem::Strlen(srcStr), reverse);
}

D_Int32 Bytemem::MemFindSubStr(D_Int8* dstStr, const D_UInt32 dstStrLen, 
    D_Int8* srcStr, const D_UInt32 srcStrLen, const D_Bool reverse)
{
    if (srcStrLen > dstStrLen)
    {
        return -1;
    }

    if (reverse)
    {
        for (D_UInt32 i = dstStrLen; i >= srcStrLen; i--)
        {
            for (D_UInt32 j = srcStrLen; j > 0; j--)
            {
                if (dstStr[i - j] != srcStr[srcStrLen - j])
                {
                    break;
                }
            }

            if (j == 0 && dstStr[i] == srcStr[srcStrLen - 1])
            {
                return i;
            }
        }
    }
    else
    {
        for (D_UInt32 i = 0; i < dstStrLen - srcStrLen; i++)
        {
            for (D_UInt32 j = 0; j < srcStrLen; j++)
            {
                if (dstStr[i + j] != srcStr[j])
                {
                    break;
                }
            }

            if (j == srcStrLen)
            {
                return i;
            }
        }        
    }

    return -1;
}

DUYE_STL_NS_END

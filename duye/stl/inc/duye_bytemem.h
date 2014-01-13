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

// brief : memory operation
//	
// usage :
class Bytemem
{
public:
	Bytemem();

	// brief : calculate string length
	// @para [in]str : input string
	// @return : the string length
	// note
	static D_UInt32 Strlen(const D_Int8* str); 

	// brief : copy string
	// @para [out]dstStr : destination string
	// @para [int]srcStr : source string
	// @return : the dstSrc end address pointer
	// note	
	static D_Int8* Strcpy(D_Int8* dstStr, const D_Int8* srcStr);

	// brief : compare equal
	// @para [in]str1 : string
	// @para [in]str2 : string
	// @return : return true when equal, else if return false
	// note
	static bool Strcmp(D_Int8* str1, D_Int8* str2); 

	// brief : set char value for a buffer
	// @para [in]str : operand string
	// @para [in]ch : be set char value
	// @para [in]size : buffer size
	// @return : void
	// note	
	static void Memset(D_Int8* str, const D_Int8 ch, D_UInt32 size); 

	// brief : copy string with a size
	// @para [in]dstStr : destination string
	// @para [in]srcStr : source string 
	// @para [in]size : the length of source string
	// @return : the end address pointer of dstStr
	// note:	
	static D_Int8* Memcpy(D_Int8* dstStr, const D_Int8* srcStr, const D_UInt32 size); 

	// brief : compare string whether equal with a size
	// @para [in]str1 : input string
	// @para [in]str2 : input string
	// @para [in]size : compare size
	// @return : return true when equal, else if return false
	// note
	static bool Memcmp(D_Int8* str1, D_Int8* str2, D_UInt32 size); 
};

DUYE_STL_NS_END 

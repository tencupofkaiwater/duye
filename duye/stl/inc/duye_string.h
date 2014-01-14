/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_string.h
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
#include <duye/stl/inc/duye_bytemem.h>

DUYE_STL_NS_BEG

// brief : string wrapper
//	
// usage :
class String
{
public:
	String();
	// brief : constructor
	// @para [in]str : init string
	explicit String(const D_Int8* str);
	
	// brief : constructor
	// @para [in]str : init string
	// @para [in]strLen : the length of string
	String(const D_Int8* str, const D_UInt32 strLen);
	
	// brief : copying constructor
	// @para [in]str : string
	String(const String& str);
	~String();

	// brief : reset capacity size
	// @para [in]size : size
	void Resize(const D_UInt32 size);
	
	// brief : assign a string
	// @para [in]str : assign string
	void Assign(const D_Int8* str);
	
	// brief : assign a string
	// @para [in]str : assign string
	// @para [in]strLen : the length of string
	void Assign(const D_Int8* str, const D_UInt32 strLen);
	
	// brief : get C string
	// return : C string pointer
	D_Int8* GetCStr() const;

private:
	// brief : predistribution allocation buffer for string
	void PreAllocation();
	
	// brief : reallocation buffer for string
	void ReAllocation(const D_UInt32 size);
	
	// brief : release buffer
	void Release();

private:
	// string buffer
	D_Int8*		m_data;
	// string length
	D_UInt32	m_length;
	// capacity size
	D_UInt32	m_capacity;
};

DUYE_STL_NS_END

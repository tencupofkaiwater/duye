/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file		duye_str.h
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

class String
{
public:
	String();
	explicit String(const Int8_t* str);
	String(const Int8_t* str, const UInt32_t size);
	String(const String& duyeStr);
	~String();

	void Resize(const UInt32_t size);
	void Assign(const Int8_t* str);
	void Assign(const Int8_t* str, const UInt32_t size);
	Int8_t* GetCStr() const;

private:
	void PreAllocation();
	void ReAllocation(const UInt32_t size);
	void Release();

private:
	Int8_t*		m_data;
	UInt32_t	m_length;
	UInt32_t	m_capacity;
};

DUYE_STL_NS_END

/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
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
	explicit String(const D_Int8* str);
	String(const D_Int8* str, const D_UInt32 size);
	String(const String& duyeStr);
	~String();

	void Resize(const D_UInt32 size);
	void Assign(const D_Int8* str);
	void Assign(const D_Int8* str, const D_UInt32 size);
	D_Int8* GetCStr() const;

private:
	void PreAllocation();
	void ReAllocation(const D_UInt32 size);
	void Release();

private:
	D_Int8*		m_data;
	D_UInt32	m_length;
	D_UInt32	m_capacity;
};

DUYE_STL_NS_END

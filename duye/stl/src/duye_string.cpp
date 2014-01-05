/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file		duye_string.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-12-1
* @note 
*
*  1. 2013-12-1 duye Created this file
* 
*/

#include <duye/stl/inc/duye_string.h>

DUYE_STL_NS_BEG

static const D_UInt32 BUF_PRE_ALLOCATION_SIZE = 50;

String::String() 
	: m_data(NULL)
	, m_length(0)
	, m_capacity(0)
{
	PreAllocation();
}

String::String(const D_Int8* str) 
	: m_data(NULL)
	, m_length(0)									   
	, m_capacity(0)
{
	Assign(str);
}

String::String(const D_Int8* str, const D_UInt32 size) 
	: m_data(NULL)
	, m_length(0)									   
	, m_capacity(0)
{
	Assign(str, size);
}

String::String(const String& duyeStr)
{
	Assign(duyeStr.GetCStr());
}

String::~String()
{
	Release();
}

void String::Resize(const D_UInt32 size)
{
	D_ASSERT(size > 0);
	
	if (m_capacity >= size)
	{
		return;
	}	
	
	ReAllocation(size);
}

void String::Assign(const D_Int8* str)
{
	D_ASSERT(str != NULL && str[0] != '\0');
	
	D_UInt32 length = Bytemem::Strlen(str);
	if (m_capacity < length)
	{
		ReAllocation(length);
	}

	m_length = length; 
	Bytemem::Memcpy(m_data, str, length);
}

void String::Assign(const D_Int8* str, const D_UInt32 size)
{
	D_ASSERT(str != NULL && str[0] != '\0');

	Release();

	m_length = Bytemem::Strlen(str); 
	m_data = new D_Int8[m_length + 1];	
}

D_Int8* String::GetCStr() const
{
	return m_data;
}

void String::PreAllocation()
{
	m_data = new D_Int8[BUF_PRE_ALLOCATION_SIZE];
	D_ASSERT(m_data != NULL);
	m_capacity = BUF_PRE_ALLOCATION_SIZE;
}

void String::ReAllocation(const D_UInt32 size)
{
	m_data = new D_Int8[size];
	D_ASSERT(m_data != NULL);
	m_capacity = size;
}

void String::Release()
{
	if (m_data != NULL)
	{
		delete[] m_data;
	    m_data = NULL;	
	}
}

DUYE_STL_NS_END

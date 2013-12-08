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

static const UInt32_t BUF_PRE_ALLOCATION_SIZE = 50;

String::String() 
	: m_data(NULL)
	, m_length(0)
	, m_capacity(0)
{
	PreAllocation();
}

String::String(const Int8_t* str) 
	: m_data(NULL)
	, m_length(0)									   
	, m_capacity(0)
{
	Assign(str);
}

String::String(const Int8_t* str, const UInt32_t size) 
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

void String::Resize(const UInt32_t size)
{
	D_ASSERT(size > 0);
	
	if (m_capacity >= size)
	{
		return;
	}	
	
	ReAllocation(size);
}

void String::Assign(const Int8_t* str)
{
	D_ASSERT(str != NULL && str[0] != '\0');
	
	UInt32_t length = Bytemem::StrLen(str);
	if (m_capacity < length)
	{
		ReAllocation(length);
	}

	m_length = length; 
	Bytemem::Memcpy(m_data, str, length);
}

void String::Assign(const Int8_t* str, const UInt32_t size)
{
	D_ASSERT(str != NULL && str[0] != '\0');

	Release();

	m_length = Bytemem::StrLen(str); 
	m_data = new Int8_t[m_length + 1];	
}

Int8_t* String::GetCStr() const
{
	return m_data;
}

void String::PreAllocation()
{
	m_data = new Int8_t[BUF_PRE_ALLOCATION_SIZE];
	D_ASSERT(m_data != NULL);
	m_capacity = BUF_PRE_ALLOCATION_SIZE;
}

void String::ReAllocation(const UInt32_t size)
{
	m_data = new Int8_t[size];
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

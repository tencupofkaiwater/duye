/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
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

D_UInt8 String::EmptyString = '\0';

String::String() : m_data(NULL), m_length(0), m_capacity(0)
{
}

String::String(const D_Int8* str) : m_data(NULL), m_length(0), m_capacity(0)
{
    if (str == NULL)
    {
        return;
    }

    m_data = Buffer::Create(str);
    if (m_data != NULL)
    {
        m_length = Bytemem::Strlen(m_data);
        m_capacity = m_length;
    }
}

String::String(const D_Int8* str, const D_UInt32 len) : m_data(NULL), m_length(0), m_capacity(0)
{
    if (str == NULL)
    {
        return;
    }

    m_data = Buffer::Create(str, len);
    if (m_data != NULL)
    {
        m_length = len;
        m_capacity = m_length;
    }
}

String::String(const String& str) : m_data(NULL), m_length(0), m_capacity(0)
{
    if (str.Length() == 0)
    {
        return;
    }

    m_data = Buffer::Create(str.GetChars(), str.Length());
    if (m_data != NULL)
    {
        m_length = str.Length();
        m_capacity = str.Capacity();
    }
}

String::~String()
{
    Release();    
}

D_UInt32 String::Length()
{
    return m_length;
}

D_UInt32 String::Capacity()
{
    return m_capacity;
}

D_Bool String::IsEmpty()
{
    return (m_length == 0 ? true : false);
}

void String::Resize(const D_UInt32 size)
{
    if (m_data != NULL)    
    {
        
    }
}

D_Int8* String::GetChars()
{
    return m_data;
}

String& String::Append(const String& str)
{
}

String& String::Append(const D_Int8* str)
{
}

String& String::Append(const D_Int8* str, const D_UInt32 len)
{
}

String& String::Append(const D_Int8 ch, const D_UInt32 repeat = 1)
{
}

void String::Assign(const D_Int8* str)
{
}

void String::Assign(const String& str)
{
}

void String::Assign(const D_Int8* str, const D_UInt32 len)
{
}

D_UInt32 String::Delete(const D_Int8 ch)
{
}

D_UInt32 String::Delete(const D_UInt32 start, const D_UInt32 end, const D_Bool reverse = false)
{
}

D_Bool String::EndWith(const D_Int8* str)
{
}

D_Bool String::EndWith(const String& str)
{
}

D_Bool String::BegWith(const D_Int8* str)
{
}

D_Bool String::BegWith(const String& str)
{
}

D_Int32 String::Compare(const D_Int8* str)
{
}

D_Int32 String::Compare(const String& str)
{
}

D_UInt32 String::Find(const D_Int8 ch, const D_Bool reverse = false)
{
}

D_UInt32 String::Find(const D_Int8 ch, const D_UInt32 start, const D_Bool reverse = false)
{
}

D_UInt32 String::Find(const D_Int8* str, const D_Bool reverse = false)
{
}

D_UInt32 String::Find(const String& str, const D_Bool reverse = false)
{
}

D_UInt32 String::Find(const D_Int8* str, const D_UInt32 start, const D_Bool reverse = false)
{
}

D_UInt32 String::Find(const String& str, const D_UInt32 start, const D_Bool reverse = false)
{
}

D_UInt32 String::Insert(const D_Int8 ch, const D_UInt32 start, const D_Bool reverse = false)
{
}

D_UInt32 String::Insert(const D_Int8* str, const D_UInt32 start, const D_Bool reverse = false)
{
}

D_UInt32 String::Insert(const String& str, const D_UInt32 start, const D_Bool reverse = false)
{
}
	
String& String::Replace(const D_Int8 dstCh, const D_Int8 srcCh, const D_UInt32 start = 0)
{
}

String& String::Replace(const D_Int8* dstStr, const D_Int8* srcStr, const D_UInt32 start = 0)
{
}

String& String::Replace(const String& dstStr, const D_Int8* srcStr, const D_UInt32 start = 0)
{
}

String& String::Replace(const D_Int8* dstStr, const String& srcStr, const D_UInt32 start = 0)
{
}

String& String::Replace(const String& dstStr, const String& srcStr, const D_UInt32 start = 0)
{
}

String String::SubString(const D_UInt32 start, const D_UInt32 len = String::End)
{
}

String String::LeftString(const D_UInt32 len)
{
}

String String::RightString(const D_UInt32 len)
{
}

String String::ToLowercase() const
{
}

String String::ToUppercase() const
{
}

void String::MakeLowercase()
{
}

void String::MakeUppercase()
{
}

D_Result String::ToInteger(D_Int16& value) const
{
}

D_Result String::ToInteger(D_Int32& value) const
{
}

D_Result String::ToInteger(D_Int64& value) const
{
}

D_Result String::ToInteger(D_UInt16& value) const
{
}

D_Result String::ToInteger(D_UInt32& value) const
{
}

D_Result String::ToInteger(D_UInt64& value) const
{
}

D_Result String::ToFloat(float& value) const
{
}

const String& String::Trim()
{
}

const String& String::TrimLeft()
{
}

const String& String::TrimRight()
{
}

String& String::operator=(const D_Int8* str)
{
}

String& String::operator=(const String& str)
{
}

String& String::operator=(const D_Int8 ch)
{
}

const String& String::operator+=(const D_Int8* str)
{
}

const String& String::operator+=(const String& str)
{
}

const String& String::operator+=(const D_Int8 ch)
{
}

D_Int8 String::operator[](const D_UInt32 index) const
{
}

D_Int8& String::operator[](const D_UInt32 index)
{
}

void String::PreAllocation()
{
}

void String::ReAllocation(const D_UInt32 size)
{
}

void String::Release()
{
    Buffer* buffer = GetBuffer();
    if (buffer != NULL)
    {
        buffer->Destroy();
    }
}

Buffer* String::GetBuffer()
{
    reinterpret_cast<Buffer*>(m_data) - 1;
}

String operator+(const String& str1, const String& str2)
{
}

String operator+(const String& str1, const D_Int8* str2)
{
}

String operator+(const D_Int8* str1, const String& str2)
{
}

String operator+(const String& str, D_Int8 ch)
{
}

String operator+(D_Int8 ch, const String& str)
{
}

DUYE_STL_NS_END

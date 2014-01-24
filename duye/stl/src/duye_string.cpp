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
    Assign(str);
}

String::String(const D_Int8* str, const D_UInt32 len) : m_data(NULL), m_length(0), m_capacity(0)
{
    Assign(str, len);
}

String::String(const String& str) : m_data(NULL), m_length(0), m_capacity(0)
{   
    Assign(str);   
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
    if (m_capacity > size)
    {
        return;    
    }
    
    Release();   
    m_data = Buffer::Create(size); 
    m_length = 0;
    m_capacity = size;
}

D_Int8* String::GetChars()
{
    return m_data;
}

String& String::Append(const D_Int8 ch, const D_UInt32 repeat = 1)
{
    D_Int8* tmpBuf = new D_Int8[repeat];
    Bytemem::Memset(tmpBuf, ch, repeat);
    String& str = Append(tmpBuf, repeat);  

    delete [] tmpBuf;
    tmpBuf = NULL;
    
    return str;
}

String& String::Append(const String& str)
{
    return Append(str.GetChars(), str.Length());           
}

String& String::Append(const D_Int8* str)
{
    return Append(str, Bytemem::Strlen(str));
}

String& String::Append(const D_Int8* str, const D_UInt32 len)
{
    D_UInt32 oldLen = m_length;
    D_UInt32 newLen = oldLen + len;
     
    if (m_capacity < newLen)
    {
        D_Int8* buffer = Buffer::Create(newLen);
        if (oldLen > 0)
        {
            Bytemem::Memcpy(buffer, m_data, oldLen);
        }
        
        Release();
        m_data = buffer;
    }

    Bytemem::Memcpy(m_data + oldLen, str, len);
    
    m_length = newLen;
    m_capacity = newLen;

    return *this;
}

void String::Assign(const D_Int8* str)
{
    Assign(str, Bytemem::Strlen(str));  
}

void String::Assign(const String& str)
{
    Assign(str.GetChars(), str.Length());    
}

void String::Assign(const D_Int8* str, const D_UInt32 len)
{
    Release();
    
    if (str == NULL || len == 0)
    {
        return;
    }

    m_data = Buffer::Create(str, len);
    D_ASSERT(m_data != NULL);
    
    if (m_data != NULL)
    {
        m_length = len;
        m_capacity = len;
    } 
}

String& String::Delete(const D_Int8 ch)
{
    D_Int8* tmpBuf = new D_Int8[m_length];
    D_UInt32 k = 0;
    
    for (D_UInt32 i = 0; i < m_length; i++)
    {
        if (m_data[i]) != ch)
        {
            tmpBuf[k++] = m_data[i];    
        }
    }

    tmpBuf[k] = '\0';

    if (k != m_length)
    {
        Bytemem::Memset(m_data, '\0', m_length);   
        Bytemem::Memcpy(m_data, tmpBuf, k);
        m_length = k;
    }

    delete [] tmpBuf;
    tmpBuf = NULL;

    return *this;
}

String& String::Delete(const D_UInt32 start, const D_UInt32 end)
{
    if (end == String::EndPos)
    {
        Bytemem::Memset(m_data + start, '\0', m_length - start);
        return *this;
    }

    if (start >= m_length || end >= m_length || start >= end)
    {
        return *this;    
    }

    Bytemem::Memcpy(m_data + start, m_data + end, m_length - end);
    D_UInt32 leaveLen = start + (m_length - end);
    Bytemem::Memset(m_data + leaveLen, '\0', m_length - leaveLen);
    m_length = leaveLen;

    return *this;
}

D_Bool String::BegWith(const D_Int8* str)
{
    return BegWith(str, Bytemem::Strlen(str));        
}

D_Bool String::BegWith(const D_Int8* str, const D_UInt32 len)
{
    D_ASSERT(Bytemem::Strlen(str) == len);
    
    if (len > m_length)
    {
        return false;
    }
    
    return Bytemem::Memcmp(m_data, str, len) == 0;
}

D_Bool String::BegWith(const String& str)
{
    return BegWith(str.GetChars());
}

D_Bool String::EndWith(const D_Int8* str)
{
    return EndWith(str, Bytemem::Strlen(str));
}

D_Bool String::EndWith(const D_Int8* str, const D_UInt32 len);
{
    D_ASSERT(Bytemem::Strlen(str) == len);
    
    if (len > m_length)
    {
        return false;
    }
    
    return Bytemem::Strcmp(m_data + (m_length - len), str, len) == 0;    
}

D_Bool String::EndWith(const String& str)
{
    return EndWith(str.GetChars());
}

D_Int32 String::Compare(const D_Int8* str)
{
    return Bytemem::Strcmp(m_data, str);
}

D_Int32 String::Compare(const String& str)
{
    return Bytemem::Memcmp(m_data, str, str.Length());
}

D_UInt32 String::Find(const D_Int8 ch, const D_Bool relaxed = false)
{
    return Find(ch, 0, reverse);
}

D_UInt32 String::Find(const D_Int8 ch, const D_UInt32 start, const D_Bool relaxed = false)
{
	if (start >= m_length)
	{
		return String::End;
	}
	
	D_Int32 pos = Bytemem::FindCh(m_data + start, ch, relaxed))
	if (pos != 0)
    {
    	return String::End;
    }

    return pos + start;
}

D_UInt32 String::Find(const D_Int8* str, const D_Bool reverse = false)
{
    return Bytemem::FindSubStr(m_data, str, reverse);
}

D_UInt32 String::Find(const String& str, const D_Bool reverse = false)
{
	return Bytemem::FindSubString(m_data, str.GetChars(), reverse)	
}

D_UInt32 String::Find(const D_Int8* str, const D_UInt32 start, const D_Bool reverse = false)
{
    if (start >= m_length)
    {
        return String::End;
    }
    
    return Bytemem::FindSubStr(m_data + start, str, reverse);    
}

D_UInt32 String::Find(const String& str, const D_UInt32 start, const D_Bool reverse = false)
{
    if (start >= m_length)
    {
        return String::End;
    }
    
    return Bytemem::FindSubStr(m_data + start, str.GetChars(), reverse);  	
}

D_UInt32 String::Insert(const D_Int8 ch, const D_UInt32 start, const D_Bool reverse = false)
{
	if (start > m_length)
	{
		return String::End;
	}
	
	if (m_length + 2 > m_capacity)
	{
		D_Int8* tmpBuf = new D_Int8[]
	}
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

String& String::Reverse() const
{
    return *this;
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
    if (m_data == NULL)
    {
        return;
    }
    
    Buffer* buffer = GetBuffer();
    if (buffer != NULL)
    {
        buffer->Destroy();
    }

    m_data = NULL;
    m_length = 0;
    m_capacity = 0;    
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

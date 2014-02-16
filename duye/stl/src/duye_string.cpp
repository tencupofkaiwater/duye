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

D_UInt32 String::Length() const
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
    Release();   
    m_data = Buffer::Create(size); 
    m_length = 0;
    m_capacity = size;
}

D_Int8* String::GetChars()
{
    return m_data;
}

D_Int8* String::GetChars() const
{
    return m_data;
}

D_UInt32 String::Append(const D_Int8 ch, const D_UInt32 repeat)
{
    if (repeat == 0)
    {
        return m_length;
    }
    
    D_Int8* tmpBuf = new D_Int8[repeat];
    Bytemem::Memset(tmpBuf, ch, repeat);
    Append(tmpBuf, repeat);  

    delete [] tmpBuf;
    tmpBuf = NULL;
    
    return m_length;
}

D_UInt32 String::Append(const String& str)
{
    return Append(str.GetChars(), str.Length());           
}

D_UInt32 String::Append(const D_Int8* str)
{
    return Append(str, Bytemem::Strlen(str));
}

D_UInt32 String::Append(const D_Int8* str, const D_UInt32 len)
{
    if (str == NULL || len == 0)
    {
        return m_length;
    }
    
    D_UInt32 oldLen = m_length;
    D_UInt32 newLen = oldLen + len;
     
    if (newLen >= m_capacity)
    {
        D_Int8* buffer = Buffer::Create(newLen + 1);
        if (oldLen > 0)
        {
            Bytemem::Memcpy(buffer, m_data, oldLen);
        }

        m_capacity = newLen + 1;
        
        Release();
        m_data = buffer;
    }

    Bytemem::Memcpy(m_data + oldLen, str, len);
    m_data[newLen] = '\0';
    
    m_length = newLen;

    return m_length;
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
    if (str == NULL || len == 0)
    {
        return;
    }

    if (len >= m_capacity)
    {
        m_capacity = len + 1;
        Resize(m_capacity);
    }
    
    Bytemem::Memcpy(m_data, str, len);
    m_data[len] = '\0';    
    m_length = len;
}

String& String::Delete(const D_Int8 ch)
{
    D_Int8* tmpBuf = new D_Int8[m_length];
    D_UInt32 k = 0;
    
    for (D_UInt32 i = 0; i < m_length; i++)
    {
        if (m_data[i] != ch)
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
    if (end == String::End)
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
    
    return (Bytemem::Memcmp(m_data, (D_Int8*)str, len) == 0);
}

D_Bool String::BegWith(const String& str)
{
    return BegWith(str.GetChars());
}

D_Bool String::EndWith(const D_Int8* str)
{
    return EndWith(str, Bytemem::Strlen(str));
}

D_Bool String::EndWith(const D_Int8* str, const D_UInt32 len)
{
    D_ASSERT(Bytemem::Strlen(str) == len);
    
    if (len > m_length)
    {
        return false;
    }
    
    return Bytemem::Memcmp(m_data + (m_length - len), (D_Int8*)str, len) == 0;    
}

D_Bool String::EndWith(const String& str)
{
    return EndWith(str.GetChars());
}

D_Int32 String::Compare(const D_Int8* str) const
{
    return Bytemem::Strcmp(m_data, (D_Int8*)str);
}

D_Int32 String::Compare(const String& str) const
{
    return Bytemem::Memcmp(m_data, str.GetChars(), str.Length());
}

D_UInt32 String::Find(const D_Int8 ch, const D_Bool relaxed)
{
    return Find(ch, 0, relaxed);
}

D_UInt32 String::Find(const D_Int8 ch, const D_UInt32 start, const D_Bool relaxed)
{
	if (start >= m_length)
	{
		return String::End;
	}
	
	D_Int32 pos = Bytemem::FindChar(m_data + start, ch, relaxed);
	if (pos != 0)
    {
    	return String::End;
    }

    return pos + start;
}

D_UInt32 String::Find(const D_Int8* str, const D_Bool reverse)
{
    return Bytemem::FindStr(m_data, (D_Int8*)str, reverse);
}

D_UInt32 String::Find(const String& str, const D_Bool reverse)
{
	return Bytemem::FindStr(m_data, str.GetChars(), reverse);	
}

D_UInt32 String::Find(const D_Int8* str, const D_UInt32 start, const D_Bool reverse)
{
    if (start >= m_length)
    {
        return String::End;
    }
    
    return Bytemem::FindStr(m_data + start, (D_Int8*)str, reverse);    
}

D_UInt32 String::Find(const String& str, const D_UInt32 start, const D_Bool reverse)
{
    if (start >= m_length)
    {
        return String::End;
    }
    
    return Bytemem::FindStr(m_data + start, str.GetChars(), reverse);  	
}

D_UInt32 String::Insert(const D_Int8 ch, const D_UInt32 start)
{
	if (start > m_length)
	{
		return String::End;
	}
	
	if (m_length + 2 > m_capacity)
	{
		//D_Int8* tmpBuf = new D_Int8[]
	}
}

D_UInt32 String::Insert(const D_Int8* str, const D_UInt32 start)
{
    return 0;
}

D_UInt32 String::Insert(const String& str, const D_UInt32 start)
{
    return 0;
}
	
String& String::Replace(const D_Int8 dstCh, const D_Int8 srcCh, const D_UInt32 start)
{
    return *this;
}

String& String::Replace(const D_Int8* dstStr, const D_Int8* srcStr, const D_UInt32 start)
{
    return *this;
}

String& String::Replace(const String& dstStr, const D_Int8* srcStr, const D_UInt32 start)
{
    return *this;
}

String& String::Replace(const D_Int8* dstStr, const String& srcStr, const D_UInt32 start)
{
    return *this;
}

String& String::Replace(const String& dstStr, const String& srcStr, const D_UInt32 start)
{
    return *this;
}

String String::SubString(const D_UInt32 start, const D_UInt32 len)
{
    return String("");
}

String String::LeftString(const D_UInt32 len)
{
    return String("");
}

String String::RightString(const D_UInt32 len)
{
    return String("");
}

String String::ToLowercase() const
{
    return String("");
}

String String::ToUppercase() const
{   
    return String("");
}

void String::MakeLowercase()
{
}

void String::MakeUppercase()
{
}

String& String::Reverse()
{
    return *this;
}

D_Bool String::ToInteger(D_Int16& value) const
{
    return true; 
}

D_Bool String::ToInteger(D_Int32& value) const
{
    return true; 
}

D_Bool String::ToInteger(D_Int64& value) const
{
    return true; 
}

D_Bool String::ToInteger(D_UInt16& value) const
{
    return true; 
}

D_Bool String::ToInteger(D_UInt32& value) const
{
    return true; 
}

D_Bool String::ToInteger(D_UInt64& value) const
{
    return true; 
}

D_Bool String::ToFloat(float& value) const
{
    return true; 
}

const String& String::Trim()
{
    return *this;
}

const String& String::TrimLeft()
{
    return *this;
}

const String& String::TrimRight()
{
    return *this;
}

String& String::operator=(const D_Int8* str)
{
    return *this;    
}

String& String::operator=(const String& str)
{
    return *this;
}

String& String::operator=(const D_Int8 ch)
{
    return *this;
}

const String& String::operator+=(const D_Int8* str)
{
    return *this;
}

const String& String::operator+=(const String& str)
{
    return *this;
}

const String& String::operator+=(const D_Int8 ch)
{
    return *this;
}

D_Int8 String::operator[](const D_UInt32 index) const
{
    return '0';
}

D_Int8& String::operator[](const D_UInt32 index)
{
    return m_data[index];
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
   return reinterpret_cast<Buffer*>(m_data) - 1;
}

String operator+(const String& str1, const String& str2)
{
    return String("");
}

String operator+(const String& str1, const D_Int8* str2)
{
    return String("");
}

String operator+(const D_Int8* str1, const String& str2)
{
    return String("");
}

String operator+(const String& str, D_Int8 ch)
{
    return String("");
}

String operator+(D_Int8 ch, const String& str)
{
    return String("");
}

DUYE_STL_NS_END

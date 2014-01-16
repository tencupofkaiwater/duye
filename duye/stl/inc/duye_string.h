/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_string.h
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
    // empty string
    static D_UInt8 EmptyString;
    // string end position
    static const D_UInt32 EndPos = 0xFFFFFFFF;
    
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

	// brief : get length
	// return : length
	D_UInt32 Length(); 	

    // brief : whether is empty string
    // return : true/false, if empty return true, else if return false
    D_Bool IsEmpty();

	// brief : reset capacity size
	// @para [in]size : size
	void Resize(const D_UInt32 size);    
    
    // brief : get C string
    // reutrn : C pointer
    D_Int8* GetChars();  

	// brief : append string
	// @para [in]str : string
	// return : new string
	String& Append(const String& str);

	// brief : append string
	// @para [in]str : C pointer
	// return : new string 
    String& Append(const D_Int8* str);

	// brief : append string
	// @para [in]str : C pointer
	// @para [in]len : the length of parameter 'str'
	// return : new string     
    String& Append(const D_Int8* str, const D_UInt32 len);

	// brief : append string
	// @para [in]ch : append character
	// @para [in]repeat : repeat times
	// return : new string     
    String& Append(const D_Int8 ch, const D_UInt32 repeat = 1);

	// brief : assign a string
	// @para [in]str : assign string
	void Assign(const D_Int8* str);
	void Assign(const String& str);
	
	// brief : assign a string
	// @para [in]str : assign string
	// @para [in]strLen : the length of string
	void Assign(const D_Int8* str, const D_UInt32 len);    

    // brief : delete all character equal to parameter 'ch'
    // @para [in]ch : be deleted character
    // return : the index of the first be deleted character, if don't find the character, 
    // return String::End
    D_UInt32 Delete(const D_Int8 ch);

    // brief : delete string
    // @para [in]index : the begin index
    // @para [in]len : delete string length
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first be deleted character, if don't find the character, 
    // return String::End    
    D_UInt32 Delete(const D_UInt32 start, const D_UInt32 end, const D_Bool reverse = false);

    // brief : end with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false
    D_Bool EndWith(const D_Int8* str);
    D_Bool EndWith(const String& str);

    // brief : begin with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false
    D_Bool BegWith(const D_Int8* str);
    D_Bool BegWith(const String& str);   

    // brief : compare string
    // @para [in]str : be compared string
    // return : 
    //  < 0 , when < str
    //  = 0 , when == str
    //  > 0 , when > str
    D_Int32 Compare(const D_Int8* str);
    D_Int32 Compare(const String& str);
    
    // brief : find character
    // @para [in]ch : need find character
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_Int8 ch, const D_Bool reverse = false);     

    // brief : find character
    // @para [in]ch : need find character
    // @para [in]start : start index
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_Int8 ch, const D_UInt32 start, const D_Bool reverse = false);   
    
    // brief : find sub string
    // @para [in]str : the sub string
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End 
    D_UInt32 Find(const D_Int8* str, const D_Bool reverse = false);
    D_UInt32 Find(const String& str, const D_Bool reverse = false);

    // brief : find sub string
    // @para [in]str : the sub string
    // @para [in]start : start index
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End    
    D_UInt32 Find(const D_Int8* str, const D_UInt32 start, const D_Bool reverse = false);
    D_UInt32 Find(const String& str, const D_UInt32 start, const D_Bool reverse = false);
    
    // brief : insert character
    // @para [in]ch : insert character
    // @para [in]start : insert index
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Insert(const D_Int8 ch, const D_UInt32 start, const D_Bool reverse = false);    
    
    // brief : insert string
    // @para [in]str : insert string
    // @para [in]start : insert index
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End    
    D_UInt32 Insert(const D_Int8* str, const D_UInt32 start, const D_Bool reverse = false);
    D_UInt32 Insert(const String& str, const D_UInt32 start, const D_Bool reverse = false);
 	
	// brief : replace character
	// @para [in]dstCh : be replaced character
	// @para [in]srcCh : replaced character
	// return : return new string
    String& Replace(const D_Int8 dstCh, const D_Int8 srcCh, const D_UInt32 start = 0);
    
	// brief : replace string
	// @para [in]dstStr : be replaced string
	// @para [in]srcStr : replaced string
	// return : return new string    
    String& Replace(const D_Int8* dstStr, const D_Int8* srcStr, const D_UInt32 start = 0);
    String& Replace(const String& dstStr, const D_Int8* srcStr, const D_UInt32 start = 0);
    String& Replace(const D_Int8* dstStr, const String& srcStr, const D_UInt32 start = 0);
    String& Replace(const String& dstStr, const String& srcStr, const D_UInt32 start = 0);

	// brief : get sub string
	// @para [in]start : begin index
	// @para [in]len : sub string length, default is the end of string
	// return : new sub string
	String SubString(const D_UInt32 start, const D_UInt32 len = String::End);

	// brief : get left string
	// @para [in]len : sub string length, default is the end of string
	// return : new sub string
	String LeftString(const D_UInt32 len);

	// brief : get right string
	// @para [in]len : sub string length, default is the end of string
	// return : new sub string	
	String RightString(const D_UInt32 len);

	// brief : converte to lowercase
	// return : new sub string	
	String ToLowercase() const;

	// brief : converte to uppercase
	// return : new sub string		
	String ToUppercase() const;

	// brief : make string to lowercase
    void MakeLowercase();

    // brief : make string to uppercase
    void MakeUppercase();	

	// brief : converte to integer
	// return : true/false
	D_Result ToInteger(D_Int16& value) const;
	D_Result ToInteger(D_Int32& value) const;
	D_Result ToInteger(D_Int64& value) const;
	
	D_Result ToInteger(D_UInt16& value) const;
	D_Result ToInteger(D_UInt32& value) const;
	D_Result ToInteger(D_UInt64& value) const;

	// brief : converte to float
	// return : true/false
	D_Result ToFloat(float& value) const;

    // brief : make string to uppercase
    const String& Trim();
    const String& TrimLeft();
    const String& TrimRight();
    
	String& operator=(const D_Int8* str);
	String& operator=(const String& str);
	String& operator=(const D_Int8 ch);
	
	const String& operator+=(const D_Int8* str);
	const String& operator+=(const String& str);
	const String& operator+=(const D_Int8 ch);
	
	D_Int8 operator[](const D_UInt32 index) const;
	D_Int8& operator[](const D_UInt32 index);

    // friend operators
    friend String operator+(const String& str1, const String& str2);
    friend String operator+(const String& str1, const D_Int8* str2);
    friend String operator+(const D_Int8* str1, const String& str2);
    friend String operator+(const String& str, D_Int8 ch);
    friend String operator+(D_Int8 ch, const String& str);	
	
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

// brief : memory malloc
//	
// usage :
class Buffer 
{
public:
    static Buffer* Allocate(D_UInt32 allocated, D_UInt32 len) 
    {
        void* mem = ::operator new(sizeof(Buffer)+allocated+1);
        return new(mem) Buffer(allocated, length);
    }
    
    static char* Create(NPT_Size allocated, NPT_Size length=0) 
    {
        Buffer* shared = Allocate(allocated, length);
        return shared->GetChars();
    }
    
    static char* Create(const char* copy) 
    {
        NPT_Size length = StringLength(copy);
        Buffer* shared = Allocate(length, length);
        CopyString(shared->GetChars(), copy);
        return shared->GetChars();
    }
    
    static char* Create(const char* copy, NPT_Size length) 
    {
        Buffer* shared = Allocate(length, length);
        CopyBuffer(shared->GetChars(), copy, length);
        shared->GetChars()[length] = '\0';
        return shared->GetChars();
    }
    static char* Create(char c, NPT_Cardinal repeat) {
        Buffer* shared = Allocate(repeat, repeat);
        char* s = shared->GetChars();
        while (repeat--) {
            *s++ = c;
        }
        *s = '\0';
        return shared->GetChars();
    }
    // methods
    char* GetChars() { 
        // return a pointer to the first char
        return reinterpret_cast<char*>(this+1); 
    }
    NPT_Size GetLength() const      { return m_Length; }
    void SetLength(NPT_Size length) { m_Length = length; }
    NPT_Size GetAllocated() const   { return m_Allocated; }
    void Destroy() { ::operator delete((void*)this); }
    
private:
    // methods
    Buffer(NPT_Size allocated, NPT_Size length = 0) : 
        m_Length(length),
        m_Allocated(allocated) {}
    
    // members
    NPT_Cardinal m_Length;
    NPT_Cardinal m_Allocated;
    // the actual string data follows

};

inline bool operator==(const String& str1, const String& str2) 
{ 
    return str1.Compare(str2) == 0; 
}

inline bool operator==(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) == 0; 
}

inline bool operator==(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) == 0; 
}

inline bool operator!=(const String& str1, const String& str2) 
{
    return str1.Compare(str2) != 0; 
}

inline bool operator!=(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) != 0; 
}

inline bool operator!=(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) != 0; 
}

inline bool operator<(const String& str1, const String& str2) 
{
    return str1.Compare(str2) < 0; 
}

inline bool operator<(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) < 0; 
}

inline bool operator<(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) > 0; 
}

inline bool operator>(const String& str1, const String& str2) 
{
    return str1.Compare(str2) > 0; 
}

inline bool operator>(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) > 0; 
}

inline bool operator>(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) < 0; 
}

inline bool operator<=(const String& str1, const String& str2) 
{
    return str1.Compare(str2) <= 0; 
}

inline bool operator<=(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) <= 0; 
}

inline bool operator<=(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) >= 0; 
}

inline bool operator>=(const String& str1, const String& str2) 
{
    return str1.Compare(str2) >= 0; 
}

inline bool operator>=(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) >= 0; 
}

inline bool operator>=(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) <= 0; 
}

DUYE_STL_NS_END

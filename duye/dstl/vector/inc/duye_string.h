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
#include <duye/stl/inc/duye_buffer.h>

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
    static const D_UInt32 End = 0xFFFFFFFF;
    
public:
	String();
	// brief : constructor
	// @para [in]str : init string
	explicit String(const D_Int8* str);
	
	// brief : constructor
	// @para [in]str : init string
	// @para [in]len : the length of string
	String(const D_Int8* str, const D_UInt32 len);
	
	// brief : copying constructor
	// @para [in]str : string
	String(const String& str);
	~String();

	// brief : get length
	// return : length
	D_UInt32 Length(); 	
	D_UInt32 Length() const; 	

	// brief : get capacity
	// return : capacity
	D_UInt32 Capacity();

    // brief : whether is empty string
    // return : true/false, if empty return true, else if return false
    D_Bool IsEmpty();

	// brief : reset capacity size
	// @para [in]size : size
	void Resize(const D_UInt32 size);    
    
    // brief : get C string
    // reutrn : C pointer
    D_Int8* GetChars();  
    D_Int8* GetChars() const;  

	// brief : append string
	// @para [in]ch : append character
	// @para [in]repeat : repeat times
	// return : string length
    D_UInt32 Append(const D_Int8 ch, const D_UInt32 repeat = 1);
    
	// brief : append string
	// @para [in]str : string
	// return : string length
	D_UInt32 Append(const String& str);

	// brief : append string
	// @para [in]str : C pointer
	// return : string length 
    D_UInt32 Append(const D_Int8* str);

	// brief : append string
	// @para [in]str : C pointer
	// @para [in]len : the length of parameter 'str'
	// return : string length     
    D_UInt32 Append(const D_Int8* str, const D_UInt32 len);

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
    String& Delete(const D_Int8 ch);

    // brief : delete string
    // @para [in]index : the begin index
    // @para [in]len : delete string length
    // return String::End    
    String& Delete(const D_UInt32 start, const D_UInt32 end = String::End);

    // brief : begin with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false
    D_Bool BegWith(const D_Int8* str);

    // brief : begin with specific string
    // @para [in]str : compare string
    // @para [in]len : string length
    // return : true/false, found return true, else if return false
    D_Bool BegWith(const D_Int8* str, const D_UInt32 len);
    
    // brief : begin with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false    
    D_Bool BegWith(const String& str); 
    
    // brief : end with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false
    D_Bool EndWith(const D_Int8* str);

    // brief : end with specific string
    // @para [in]str : compare string
    // @para [in]len : string length
    // return : true/false, found return true, else if return false    
    D_Bool EndWith(const D_Int8* str, const D_UInt32 len);

    // brief : end with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false    
    D_Bool EndWith(const String& str);  

    // brief : compare string
    // @para [in]str : be compared string
    // return : 
    //  < 0 , when < str
    //  = 0 , when == str
    //  > 0 , when > str
    D_Int32 Compare(const D_Int8* str) const;
    D_Int32 Compare(const String& str) const;
    
    // brief : find character
    // @para [in]ch : need find character
    // @para [in]relaxed : whether discriminate capital, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_Int8 ch, const D_Bool relaxed = false);     

    // brief : find character
    // @para [in]ch : need find character
    // @para [in]start : start index
    // @para [in]relaxed : whether discriminate capital, default is true
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_Int8 ch, const D_UInt32 start, const D_Bool relaxed = true);   
    
    // brief : find sub string
    // @para [in]str : the sub string
    // @para [in]relaxed : whether discriminate capital, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End 
    D_UInt32 Find(const D_Int8* str, const D_Bool relaxed = false);
    D_UInt32 Find(const String& str, const D_Bool relaxed = false);

    // brief : find sub string
    // @para [in]str : the sub string
    // @para [in]start : start index
    // @para [in]relaxed : whether discriminate capital, default is true
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End    
    D_UInt32 Find(const D_Int8* str, const D_UInt32 start, const D_Bool relaxed = true);
    D_UInt32 Find(const String& str, const D_UInt32 start, const D_Bool relaxed = true);
    
    // brief : insert character
    // @para [in]ch : insert character
    // @para [in]start : insert index, default is 0
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Insert(const D_Int8 ch, const D_UInt32 start = 0);    
    
    // brief : insert string
    // @para [in]str : insert string
    // @para [in]start : insert index, default is 0
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End    
    D_UInt32 Insert(const D_Int8* str, const D_UInt32 start = 0);
    D_UInt32 Insert(const String& str, const D_UInt32 start = 0);
 	
	// brief : replace character
	// @para [in]dstCh : be replaced character
	// @para [in]srcCh : replaced character
	// @para [in]start : insert index, default is 0
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

	// brief : reverse string
	// return : 
	String& Reverse();    

	// brief : converte to integer
	// return : true/false
	D_Bool ToInteger(D_Int16& value) const;
	D_Bool ToInteger(D_Int32& value) const;
	D_Bool ToInteger(D_Int64& value) const;
	
	D_Bool ToInteger(D_UInt16& value) const;
	D_Bool ToInteger(D_UInt32& value) const;
	D_Bool ToInteger(D_UInt64& value) const;

	// brief : converte to float
	// return : true/false
	D_Bool ToFloat(float& value) const;

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

	// bref : convert to buffer object
	Buffer* GetBuffer();

private: 
	D_Int8*		m_data;
	D_UInt32    m_length;
	D_UInt32    m_capacity;
};

inline D_Bool operator==(const String& str1, const String& str2) 
{ 
    return str1.Compare(str2) == 0; 
}

inline D_Bool operator==(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) == 0; 
}

inline D_Bool operator==(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) == 0; 
}

inline D_Bool operator!=(const String& str1, const String& str2) 
{
    return str1.Compare(str2) != 0; 
}

inline D_Bool operator!=(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) != 0; 
}

inline D_Bool operator!=(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) != 0; 
}

inline D_Bool operator<(const String& str1, const String& str2) 
{
    return str1.Compare(str2) < 0; 
}

inline D_Bool operator<(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) < 0; 
}

inline D_Bool operator<(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) > 0; 
}

inline D_Bool operator>(const String& str1, const String& str2) 
{
    return str1.Compare(str2) > 0; 
}

inline D_Bool operator>(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) > 0; 
}

inline D_Bool operator>(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) < 0; 
}

inline D_Bool operator<=(const String& str1, const String& str2) 
{
    return str1.Compare(str2) <= 0; 
}

inline D_Bool operator<=(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) <= 0; 
}

inline D_Bool operator<=(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) >= 0; 
}

inline D_Bool operator>=(const String& str1, const String& str2) 
{
    return str1.Compare(str2) >= 0; 
}

inline D_Bool operator>=(const String& str1, const D_Int8* str2) 
{
    return str1.Compare(str2) >= 0; 
}

inline D_Bool operator>=(const D_Int8* str1, const String& str2) 
{
    return str2.Compare(str1) <= 0; 
}

DUYE_STL_NS_END
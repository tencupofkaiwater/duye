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
    static const U_DInt32 End = 0xFFFFFFFF;
    
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

	// brief : append string
	// @para [in]str : string
	// return : new string
	String& Append(const String& str);

	// brief : append string
	// @para [in]str : C pointer
	// return : new string 
    String& Append(const D_Int8* str);

	// brief : append string
	// @para [in]str : string
	// @para [in]index : the index of input string
	// @para [in]len : the length of append string
	// return : new string     
    String& Append(const String& str, const D_UInt32 index, const D_UInt32 len);

	// brief : append string
	// @para [in]str : C pointer
	// @para [in]len : the length of parameter 'str'
	// return : new string     
    String& Append(const D_Int8* str, const D_UInt32 len);

	// brief : append string
	// @para [in]num : the number of the second parameter
	// @para [in]ch : append character
	// return : new string     
    String& Append(const D_UInt32 num, const D_Int8 ch);

	// brief : assign a string
	// @para [in]str : assign string
	void Assign(const D_Int8* str);
	
	// brief : assign a string
	// @para [in]str : assign string
	// @para [in]strLen : the length of string
	void Assign(const D_Int8* str, const D_UInt32 strLen);    

    // brief : get character by index
    // @para [in]index : index
    // return : character
    D_Int8 GetChar(const D_UInt32 index);

    // brief : get C string
    // @para
    // reutrn : C pointer
    D_Int8* GetPtr();

    // brief : begin with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false
    D_Bool BegWith(const String& str);
    D_Bool BegWith(const D_Int8* str);

    // brief : end with specific string
    // @para [in]str : compare string
    // return : true/false, found return true, else if return false
    D_Bool EndWith(const String& str);
    D_Bool EndWith(const D_Int8* str);

    // brief : compare string from a specific index
    // @para [in]index : start index
    // @para [in]str : compare string
    // @para [in]reverse : whether is reverse find, default is false
    // return : true/false, found return true, else if return false   
    D_Bool MidWith(const D_UInt32 index, const String& str, const D_Bool reverse = false);
    D_Bool MidWith(const D_UInt32 index, const D_Int8* str, const D_Bool reverse = false);

    // brief : whether is empty string
    // return : true/false, if empty return true, else if return false
    D_Bool IsEmpty();

    // brief : delete all character equal to parameter 'ch'
    // @para [in]ch : be deleted character
    // return : the index of the first be deleted character, if don't find the character, 
    // return String::End
    D_UInt32 Delete(const D_Int8 ch);

    // brief : delete all character equal to parameter 'ch', begin index
    // @para [in]index : the begin index
    // @para [in]ch : be deleted character
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first be deleted character, if don't find the character, 
    // return String::End    
    D_UInt32 Delete(const D_UInt32 index, const D_Int8 ch, const D_Bool reverse = false);

    // brief : delete from index to index + len
    // @para [in]index : the begin index
    // @para [in]size : delete size
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first be deleted character, if don't find the character, 
    // return String::End    
    D_UInt32 Delete(const D_UInt32 index, const D_UInt32 size, const D_Bool reverse = false);

    // brief : delete a sub string
    // @para [in]str : the sub string
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first be deleted character, if don't find the character, 
    // return String::End    
    D_UInt32 Delete(const String& str, const D_Bool reverse = false);  
    D_UInt32 Delete(const D_Int8* str, const D_Bool reverse = false);

    // brief : find sub string
    // @para [in]str : the sub string
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const String& str, const D_Bool reverse = false);
    D_UInt32 Find(const D_Int8* str, const D_Bool reverse = false);

    // brief : find sub string
    // @para [in]index : start index
    // @para [in]str : the sub string
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_UInt32 index, const String& str, const D_Bool reverse = false);
    D_UInt32 Find(const D_UInt32 index, const D_Int8* str, const D_Bool reverse = false);

    // brief : find character
    // @para [in]ch : need find character
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_Int8 ch, const D_Bool reverse = false);     

    // brief : find character
    // @para [in]index : start index
    // @para [in]ch : need find character
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Find(const D_UInt32 index, const D_Int8 ch, const D_Bool reverse = false);   

    // brief : insert character
    // @para [in]index : start index
    // @para [in]ch : need find character
    // @para [in]reverse : whether is reverse find, default is false
    // return : the index of the first character of the found sub string, 
    // if don't find the character, return String::End      
    D_UInt32 Insert(const D_UInt32 index, const D_Int8 ch, const D_Bool reverse = false);    

	// brief : get length
	// return : length
	D_UInt32 Length();    

    String& Replace();

	// brief : reset capacity size
	// @para [in]size : size
	void Resize(const D_UInt32 size);

	String SubString();
	
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

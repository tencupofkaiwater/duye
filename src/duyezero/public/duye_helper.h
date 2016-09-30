/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_helper.h
* @version     
* @brief      
* @author   duye
* @date	    2014-03-09
* @note 
*
*  1. 2014-03-09 duye created this file
* 
*/
#pragma once

#include <string>
#include <vector>
#include <duye_type.h>

namespace duye {

/**
 * @brief string extend function
 * @note
 */
class StrHelper
{
public:
	/**
	 * @brief convert char to uppercase
	 * @para [in] instr : in string
	 * @note : no copy, modify original data
	 */	
	static void strupr(int8* instr);
	/**
	 * @brief convert chars to uppercase
	 * @para [in] instr : in string
	 * @para [in] outstr : out string	
	 * @para [in] outsize : outstr buffer size	 
	 * @return : true/false
	 */	    
	static bool strnupr(const int8* instr, int8* outstr, const uint32 outsize);	
	/**
	 * @brief convert char to lowercase
	 * @para [in] instr : in string
	 * @note : no copy, modify original data
	 */	    
	static void strlwr(int8* instr);
	/**
	 * @brief convert chars to lowercase
	 * @para [in] instr : in string
	 * @para [in] outstr : out string	
	 * @para [in] outsize : outstr buffer size	 
	 * @return : true/false
	 */	        
	static bool strlwr(const int8* instr, int8* outstr, const uint32 outsize);

	/**
	 * @brief convert numerical value to string
	 * @para [in] flag/integer : in numerical 
	 * @return : string
	 */	 
	static std::string toStr(const bool flag);
	static std::string toStr(const int16 integer);
	static std::string toStr(const uint16 integer);
	static std::string toStr(const int32 integer);
	static std::string toStr(const uint32 integer);
	static std::string toStr(const int64 integer);
	static std::string toStr(const uint64 integer);
	static std::string toStr(const float fpn);
	static std::string toStr(const double fpn);

	/**
	 * @brief convert string to bool
	 * @para [in] inStr : in string 
	 * @return : true/false
	 */	
	static bool toBool(const uint8* inStr);
	static bool toBool(const std::string& inStr);

	/**
	 * @brief convert string to integer
	 * @para [in] inStr : in string 
	 * @return : true/false
	 */	
	static int64 toInt(const uint8* inStr);
	static int64 toInt(const std::string& inStr);

	/**
	 * @brief to detemine char whether is integer.
	 * @para [in] ch : in char
	 * @return : true/false
	 */	
    static bool isNum(const int8 ch);
	/**
	 * @brief to detemine chars whether is integer.
	 * @para [in] chars : in chars
	 * @return : true/false
	 */	    
    static bool isNums(const int8* chars);
    static bool isNums(const std::string& str);

	/**
	 * @brief to detemine whether is ip address.
	 * @para [in] ipAddr : in ip address
	 * @return : true/false
	 */	   
    static bool isIpAddr(const std::string& ipAddr);
	/**
	 * @brief to detemine whether is port.
	 * @para [in] port : port
	 * @return : true/false
	 */	       
    static bool isPort(const uint32 port);

	/**
	 * @brief compare string
	 * @para [in] firstStr : first string.
	 * @para [in] secondStr : second string.
	 * @para [in] ignore : whether is ignore capital and lowercase, default case sensitive.
	 * @return : on full match, return true. else if return false.
	 */
	static bool compare(const int8* firstStr, const int8* secondStr, const bool ignore = false);
	/**
	 * @brief compare string
	 * @para [in] firstStr : first string.
	 * @para [in] secondStr : second string.
	 * @para [in] comLen : should compare length.
	 * @para [in] ignore : ignore capital and lowercase.
	 * @return : on full match, return true. else if return false.
	 */    
	static bool compare(const int8* firstStr, const int8* secondStr, const uint32 comLen, const bool ignore = false);
	/**
	 * @brief compare string
	 * @para [in] str : full string.
	 * @para [in] subStr : sub string.
	 * @para [in] ignore : ignore capital and lowercase.
	 * @return : on found sub string, return true. else if return false.
	 */        
	static bool begWith(const int8* str, const int8* subStr, const bool ignore = false);
	static bool endWith(const int8* str, const int8* subStr, const bool ignore = false);	

	/**
	 * @brief compare string
	 * @para [in] inStr : full string.
	 * @para [in] separator : cut off symbol
	 * @para [in] outArray : output string array
	 */   
	static void split(const std::string& inStr, const uint8 separator, std::vector<std::string>& outArray);

	/**
	 * @brief get file path basename
	 * @para [in] inFilePath : file full path.
	 * @return : basename
	 * @note /etc/test/tt.txt, basename is 'tt.txt'
	 */      
    static std::string basename(const std::string& inFilePath);
    static std::string basename(const int8* inFilePath);

	/**
	 * @brief get file directory
	 * @para [in] inFilePath : file full path.
	 * @return : file directory
	 * @note /etc/test/tt.txt, file directory is '/etc/test'
	 */    
    static std::string filedir(const std::string& inFilePath);
    static std::string filedir(const int8* inFilePath);	 
};

/**
 * @brief string extend function
 * @note
 */
class ByteHelper
{
public:
	/**
	 * @brief find sub byte array
	 * @param [in] data : input data
	 * @param [in] dataLen : input data length
	 * @param [in] sub : sub byte array
	 * @param [in] subLen : sub byte array size
	 * @return start position, NULL indicate don't found
	 * @note 
	 */
	static uint8* findSubBytes(const uint8* data, const uint32 dataLen, const uint8* sub, const uint32 subLen);

	/**
	 * @brief find byte
	 * @param [in] data : input data
	 * @param [in] dataLen : input data length
	 * @param [in] sub : sub byte array
	 * @param [in] subLen : sub byte array size
	 * @return start position, NULL indicate don't found
	 * @note 
	 */
	static uint8* findByte(const uint8* data, const uint32 dataLen, const uint8 byte);

	/**
	 * @brief reverse find byte
	 * @param [in] data : input data
	 * @param [in] dataLen : input data length
	 * @param [in] sub : sub byte array
	 * @param [in] subLen : sub byte array size
	 * @return start position, NULL indicate don't found
	 * @note 
	 */
	static uint8* findByteR(const uint8* data, const uint32 dataLen, const uint8 byte);
	
	/**
	 * @brief convert byte array to hex format string
	 * @param [in] data : input data
	 * @param [in] dataLen : input data length
	 * @return hex string
	 * @note 
	 */
	static std::string toHexStr(const uint8* data, const uint32 dataLen);
};

/**
 * @brief time extend function
 * @note
 */
class TimeHelper
{
public:
	struct TimeValue
	{
		uint16  year;
		uint8   month;
		uint8   day;
		uint8   hour;
		uint8   minute;
		uint8   sec;
		uint16  msec;
		uint16  usec;
	};

public:
	/**
	 * @brief format time
	 * @param [in] usec : microsecond
	 * @param [out] timeValue : time value
	 * @return void
	 * @note 
	 */
	static void format(const uint64 usec, TimeHelper::TimeValue& timeValue);

	/**
	 * @brief format time
	 * @param [in] usec : microsecond
	 * @return time string
	 * @note example 'YYYY-MM-DD HH:MM:SS:MS:US'
	 */
	static std::string format(const uint64 usec);
};

/**
 * @brief time extend function
 * @note
 */
class NetHelper
{
public:
	/**
	 * @brief format time
	 * @param [in] strIP : string ip
	 * @return: On error, returned 0
	 */    
    static uint32 ipToInt(const std::string& strIP);

	/**
	 * @brief format time
	 * @param [in] intIP : int ip
	 * @return : string ip
	 */    
    static std::string ipToStr(const uint32 intIP);
};

/**
 * @brief algorithm extend function
 * @note
 */
class AlgHelper
{
public:
	/**
	 * @brief calculation bytes md5
	 * @param [in] bytes : in bytes
	 * @param [in] len : in bytes len
	 * @return: md5 hex string
	 */    
    static std::string md5Bytes(const int8* bytes, const uint32 len);
	/**
	 * @brief calculation file md5
	 * @param [in] filePath : file full path
	 * @return: md5 hex string
	 */      
    static std::string md5File(const int8* filePath); 
};

}

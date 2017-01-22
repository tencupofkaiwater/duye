/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_base64.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-18
* @note 
*
*  1. 2016-04-18 duye created this file
* 
*/
#pragma once

#include <string>
#include <duye_system.h>

namespace duye {

class Base64
{
public:    
	std::string base64Encode(const int8*, uint32 len);
	std::string base64Encode(const std::string& str);
	std::string base64Decode(const int8*, uint32 len);
	std::string base64Decode(const std::string& str);
	std::string base64Decode(const std::string& decodeStr, uint32& outLen);
	std::string base64Decode(const int8* encodedStr, uint32 inLen, uint32& outLen);

private:    
	bool isBase64(uint8 c);
};
}

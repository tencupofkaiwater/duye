/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_base64.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-18
* @note 
*
*  1. 2016-04-18 duye created this file
* 
*/
#include <iostream>
#include <ctype.h>
#include <duye_base64.h>

namespace duye {

static const std::string base64Chars = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string Base64::base64Encode(const std::string& str)
{
	return base64Encode(str.c_str(), str.length());
}

std::string Base64::base64Encode(const int8* bytesToEncode, uint32 inLen)
{
	std::string ret;
	int i = 0;
	int j = 0;
	uint8 charArray4[4] = {0};
    uint8 charArray3[3] = {0};
	
	while (inLen--)
	{
		charArray3[i++] = *(bytesToEncode++);
		if (i == 3)
		{
			charArray4[0] = (charArray3[0] & 0xfc) >> 2;
			charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
			charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
			charArray4[3] = charArray3[2] & 0x3f;
			
			for(i = 0; (i <4) ; i++)
				ret += base64Chars[charArray4[i]];
			i = 0;
		}
	}
	
	if (i)
	{
		for(j = i; j < 3; j++)
			charArray3[j] = '\0';
		
		charArray4[0] = (charArray3[0] & 0xfc) >> 2;
		charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
		charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
		charArray4[3] = charArray3[2] & 0x3f;
		
		for (j = 0; (j < i + 1); j++)
			ret += base64Chars[charArray4[j]];
		
		while((i++ < 3))
			ret += '=';
	}
	
	return ret;
}

std::string Base64::base64Decode(const int8* encodedStr, uint32 inLen)
{
	int i = 0;
	int j = 0;
	int in_ = 0;
	uint8 charArray4[4] = {0};
    uint8 charArray3[3] = {0};
	std::string ret;
	
	while (inLen-- && (encodedStr[in_] != '=') && isBase64(encodedStr[in_]))
	{
		charArray4[i++] = encodedStr[in_]; in_++;
		if (i ==4) 
		{
			for (i = 0; i <4; i++)
				charArray4[i] = base64Chars.find(charArray4[i]);
			
			charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
			charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
			charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];
			
			for (i = 0; (i < 3); i++)
				ret += charArray3[i];
			i = 0;
		}
	}
	
	if (i) 
	{
		for (j = i; j <4; j++)
			charArray4[j] = 0;
		
		for (j = 0; j <4; j++)
			charArray4[j] = base64Chars.find(charArray4[j]);
		
		charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
		charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
		charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];
		
		for (j = 0; (j < i - 1); j++) ret += charArray3[j];
	}
	
	return ret;
}

std::string Base64::base64Decode(const int8* encodedStr, uint32 inLen, uint32& outLen)
{
	int i = 0;
	int j = 0;
	int in_ = 0;
	outLen = 0;
	uint8 charArray4[4] = {0};
    uint8 charArray3[3] = {0};
	std::string ret;
	
	while (inLen-- && (encodedStr[in_] != '=') && isBase64(encodedStr[in_])) 
	{
		charArray4[i++] = encodedStr[in_]; in_++;
		if (i ==4) 
		{
			for (i = 0; i <4; i++)
				charArray4[i] = base64Chars.find(charArray4[i]);
			
			charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
			charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
			charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];
			
			for (i = 0; (i < 3); i++)
			{
			   	ret += charArray3[i];
				outLen++;
			}
			
			i = 0;
		}
	}
	
	if (i) 
	{
		for (j = i; j <4; j++)
			charArray4[j] = 0;
		
		for (j = 0; j <4; j++)
			charArray4[j] = base64Chars.find(charArray4[j]);
		
		charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
		charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
		charArray3[2] = ((charArray4[2] & 0x3) << 6) + charArray4[3];
		
		for (j = 0; (j < i - 1); j++)
		{
		    ret += charArray3[j];
            outLen++;
		}
	}
	
	return ret;
}

std::string Base64::base64Decode(const std::string& decodeStr)
{
	return base64Decode(decodeStr.c_str(), decodeStr.size());
}

std::string Base64::base64Decode(const std::string& decodeStr, uint32& outLen)
{
	return base64Decode(decodeStr.c_str(), decodeStr.size(), outLen);
}

bool Base64::isBase64(uint8 c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}  
}

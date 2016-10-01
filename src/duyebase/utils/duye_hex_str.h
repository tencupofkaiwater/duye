/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_hex_str.h
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

#include <duye_system.h>

namespace duye {

class HexStr
{
public:
	HexStr();
	~HexStr();


    /**
     * 将unsigned  char*字符串转换成16进制字符串
     * @param[in] charStr 原始值
     * @param[in] size 原始字符串长度
     * @param[out] hexStr 转换后的值
     */   
    static void charStr2HexStr(const int8* charStr, uint32 size, int8* hexStr);
    /**
     * 将16进制字符串转换成unsigned  char*字符串
     * @param[in] pszHexStr 原始值
     * @param[in] nSize 原始字符串长度
     * @param[out] pucCharStr 转换后的值
     */
    static void hexStr2CharStr(const int8* hexStr, uint32 nSize, int8* charStr);
    /**
     * 将unsigned char转换成2字节的16进制字符串
     * @param[in] ch 原始值
     * @param[out] hex 16进制字符串值
     */    
	static void char2Hex(int8 ch, int8* hex);
    /**
     * 将2字节的16进制字符串转换成unsigned  char
     * @param[in] hex 原始值
     * @param[out] ch 转换后的值
     */        
	static void hex2Char(const int8* hex, int8& ch);
};
}

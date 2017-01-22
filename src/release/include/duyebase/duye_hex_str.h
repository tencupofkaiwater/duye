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
     * ��unsigned  char*�ַ���ת����16�����ַ���
     * @param[in] charStr ԭʼֵ
     * @param[in] size ԭʼ�ַ�������
     * @param[out] hexStr ת�����ֵ
     */   
    static void charStr2HexStr(const int8* charStr, uint32 size, int8* hexStr);
    /**
     * ��16�����ַ���ת����unsigned  char*�ַ���
     * @param[in] pszHexStr ԭʼֵ
     * @param[in] nSize ԭʼ�ַ�������
     * @param[out] pucCharStr ת�����ֵ
     */
    static void hexStr2CharStr(const int8* hexStr, uint32 nSize, int8* charStr);
    /**
     * ��unsigned charת����2�ֽڵ�16�����ַ���
     * @param[in] ch ԭʼֵ
     * @param[out] hex 16�����ַ���ֵ
     */    
	static void char2Hex(int8 ch, int8* hex);
    /**
     * ��2�ֽڵ�16�����ַ���ת����unsigned  char
     * @param[in] hex ԭʼֵ
     * @param[out] ch ת�����ֵ
     */        
	static void hex2Char(const int8* hex, int8& ch);
};
}

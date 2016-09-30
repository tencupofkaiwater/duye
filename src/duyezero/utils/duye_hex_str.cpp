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
#include <string.h>
#include <duye_hex_str.h>

namespace duye {

HexStr::HexStr()
{
}

HexStr::~HexStr()
{
}

void HexStr::char2Hex(int8 ch, int8* hex)
{
	unsigned char byte[2] = {0};
	byte[0] = ch/16;
	byte[1] = ch%16;
	for(int i=0; i<2; i++)
	{
		if(byte[i] >= 0 && byte[i] <= 9)
			hex[i] = '0' + byte[i];
		else
			hex[i] = 'A' + byte[i] - 10;
	}
	hex[2] = 0;
}

void HexStr::hex2Char(const int8* hex, int8& ch)
{
	ch = 0;
	for(int i=0; i<2; i++)
	{
		if(*(hex + i) >='0' && *(hex + i) <= '9')
			ch = (ch << 4) + (*(hex + i) - '0');
		else if(*(hex + i) >='A' && *(hex + i) <= 'F')
			ch = (ch << 4) + (*(hex + i) - 'A' + 10);
		else
			break;
	}
}    

void HexStr::charStr2HexStr(const int8* charStr, uint32 size, int8* hexStr)
{
	uint32 i = 0;
	int8 hex[3] = {0};
    
	hexStr[0] = 0;    
	for (i = 0; i < size; i++)
	{
		char2Hex(charStr[i], hex);
		strcat(hexStr, hex);
	}
}

void HexStr::hexStr2CharStr(const int8* hexStr, uint32 size, int8* charStr)
{
	uint32 i = 0;
	int8 ch = 0;
    
	for (i = 0; i < size; i++)
	{
		hex2Char(hexStr + 2 * i, ch);
		charStr[i] = ch;
	}
}
}
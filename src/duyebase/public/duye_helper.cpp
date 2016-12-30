/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_helper.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-03-09
* @note 
*
*  1. 2014-03-09 duye created this file
* 
*/
#include <time.h>
#include <string.h>
#include <duye_sys.h>
#include <duye_md5.h>
#include <duye_helper.h>

namespace duye {

static const int32 UPR_DIF_LWR = 'a' - 'A';

void StrHelper::strupr(int8* instr)
{
	if (instr == NULL)
	{
		return;
	}

	int8* p = instr;
	for (; *p != 0; p++)
	{
		if (*p >= 'a' && *p <= 'z')
		{
			*p -= UPR_DIF_LWR; 
		}
	}
}

bool StrHelper::strnupr(const int8* instr, int8* outstr, const uint32 outsize)
{
	if (instr == NULL || 
		outstr == NULL || 
		strlen(instr) >= outsize)
	{
		return false;
	}

	for (; *instr != 0; instr++, outstr++)
	{
		if (*instr >= 'a' && *instr <= 'z')
		{
			*outstr = *instr - UPR_DIF_LWR; 
		}

		*outstr = *instr;
	}

    *outstr = 0;

	return true;	
}

void StrHelper::strlwr(int8* instr)
{
	if (instr == NULL)
	{
		return;
	}

	int8* p = instr;
	for (; *p != 0; p++)
	{
		if (*p >= 'A' && *p <= 'Z')
		{
			*p += UPR_DIF_LWR; 
		}
	}
}

bool StrHelper::strlwr(const int8* instr, int8* outstr, const uint32 outsize)
{
	if (instr == NULL || 
		outstr == NULL || 
		strlen(instr) >= outsize)
	{
		return false;
	}

	for (; *instr != 0; instr++, outstr++)
	{
		if (*instr >= 'A' && *instr <= 'Z')
		{
			*outstr = *instr + UPR_DIF_LWR; 
		}

		*outstr = *instr;
	}
    
    *outstr = 0;

	return true;	
}

std::string StrHelper::toStr(const bool flag)
{
	return flag ? "true" : "false";
}

std::string StrHelper::toStr(const int16 integer)
{
	return toStr((int64)integer);
}

std::string StrHelper::toStr(const uint16 integer)
{
	return toStr((uint64)integer);
}

std::string StrHelper::toStr(const int32 integer)
{
	return toStr((int64)integer);
}

std::string StrHelper::toStr(const uint32 integer)
{
	return toStr((uint64)integer);
}

std::string StrHelper::toStr(const int64 integer)
{
	int8 outStr[128] = {0};
	snprintf(outStr, 128, "%lld", integer);
	return std::string(outStr);
}

std::string StrHelper::toStr(const uint64 integer)
{
	int8 outStr[128] = {0};
	snprintf(outStr, 128, "%llu", integer);
	return std::string(outStr);
}

std::string StrHelper::toStr(const float fpn)
{
	int8 outStr[1024] = {0};
	snprintf(outStr, 1024, "%f", fpn);
	return std::string(outStr);
}

std::string StrHelper::toStr(const double fpn)
{
	int8 outStr[1024] = {0};
	snprintf(outStr, 1024, "%lf", fpn);
	return std::string(outStr);
}

bool StrHelper::toBool(const uint8* inStr)
{
	if (inStr == NULL)
		return false;
	
	if (memcmp(inStr, "true", sizeof("true") - 1) == 0)
		return true;

	return false;		
}

bool StrHelper::toBool(const std::string& inStr)
{
	return toBool(inStr.c_str());
}
	
int64 StrHelper::toInt(const uint8* inStr)
{
	if (inStr == NULL)
	{
		return 0;
	}
    
    bool isNegative = false;
	uint32 len = strlen((const char*)inStr);
	int64 sum = 0;
	for (uint32 i = 0; i < len; i++)
	{
		if (inStr[i] < '0' || inStr[i] > '9')
		{
            if (inStr[i] == '-')
            {
                isNegative = true;
                continue;
            }

		    return 0;
		}

		sum *= 10;
		sum += (inStr[i] - '0');
	}

    if (isNegative)
        return -sum;
    
	return sum;
}

int64 StrHelper::toInt(const std::string& inStr)
{
	if (inStr.empty())
		return 0;
	
	return toInt((const uint8*)(inStr.c_str()));
}

bool StrHelper::isNum(const int8 ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}

bool StrHelper::isNums(const int8* chars)
{
    if (chars == NULL || *chars == 0)
        return false;
    
    uint32 len = strlen(chars);
    for (uint32 i = 0; i < len; i++)
    {
        if (!isNum(chars[i]))
            return false;
    }

    return true;
}

bool StrHelper::isNums(const std::string& str)
{
    return isNums(str.c_str());
}

bool StrHelper::isIpAddr(const std::string& ipAddr)
{
    std::vector<std::string> outArray;
    split(ipAddr, '.', outArray);
    if (outArray.size() != 4)
        return true;

    for (uint32 i = 0; i < 4; i++)
    {
        int32 ipVal = (int32)toInt(outArray[i]);
        if (ipVal < 0 || ipVal > 255)
            return false;
    }

    return true;
}
     
bool StrHelper::isPort(const uint32 port)
{
    if (port <= 0 || port > 0xFFFF)
        return false;
    return true;
}

bool StrHelper::compare(const int8* firstStr, const int8* secondStr, const bool ignore)
{
	if (firstStr == NULL || secondStr == NULL)
	{
		return false;
	}
	
	if (ignore)
	{
		for (; *firstStr != 0 && *secondStr != 0; firstStr++, secondStr++)
		{
			if (*firstStr == *secondStr || 
				(*firstStr + UPR_DIF_LWR) == *secondStr ||
				*firstStr - UPR_DIF_LWR == *secondStr)
			{
				continue;
			}

			return false;
		}

		if (*firstStr == 0 && *secondStr == 0)
		{
			return true;
		}
	}
	else
	{
		for (; *firstStr != 0 && *secondStr != 0; firstStr++, secondStr++)
		{
			if (*firstStr == *secondStr)
			{
				continue;
			}

			return false;
		}

		if (*firstStr == 0 && *secondStr == 0)
		{
			return true;
		}	
	
	}

	return false;
}

bool StrHelper::compare(const int8* firstStr, const int8* secondStr, const uint32 comLen, const bool ignore)
{
	if (firstStr == NULL || 
		secondStr == NULL || 
		comLen <= 0)
	{
		return false;
	}

	uint32 len1 = strlen(firstStr);
	uint32 len2 = strlen(firstStr);	
	if (comLen > (len1 < len2 ? len1 : len2))
	{
		return false;
	}
	
	if (ignore)
	{
		for (uint32 i = 0; i < comLen; firstStr++, secondStr++, i++)
		{
			if (*firstStr == *secondStr || 
				(*firstStr + UPR_DIF_LWR) == *secondStr ||
				*firstStr - UPR_DIF_LWR == *secondStr)
			{
				continue;
			}

			return false;
		}
	}
	else
	{
		for (uint32 i = 0; i < comLen; firstStr++, secondStr++, i++)
		{
			if (*firstStr == *secondStr)
			{
				continue;
			}

			return false;
		}
	
	}

	return true;
}

bool StrHelper::begWith(const int8* str, const int8* subStr, const bool ignore)
{
	uint32 strLen = strlen(str);
	uint32 subStrLen = strlen(subStr);

	if (strLen < subStrLen)
	{
		return false;
	}
	
	return compare(str, subStr, subStrLen, ignore);
}

bool StrHelper::endWith(const int8* str, const int8* subStr, const bool ignore)
{
	uint32 strLen = strlen(str);
	uint32 subStrLen = strlen(subStr);
	
	if (strLen < subStrLen)
	{
		return false;
	}

	return compare(str + (strLen - subStrLen), subStr, subStrLen, ignore);
}

void StrHelper::trim(std::string& inStr) {
	std::string temp_str;
	for (uint32 i = 0; i < inStr.length(); i++) {
		if (inStr[i] == ' ')
			continue;
		temp_str = inStr.substr(i);
		break;
	}

	for (uint32 i = temp_str.length() - 1; i >= 0; i--) {
		if (temp_str[i] == ' ')
			continue;
		temp_str = temp_str.substr(0, i + 1);
		break;
	}

	inStr = temp_str;
}

void StrHelper::trimEnter(std::string& inStr) {
	if (StrHelper::endWith(inStr.c_str(), "\n")) {
		inStr = inStr.substr(0, inStr.length() - (sizeof("\n") - 1));
	} else if (StrHelper::endWith(inStr.c_str(), "\r\n")) {
		inStr = inStr.substr(0, inStr.length() - (sizeof("\r\n") - 1));
	}
}

void StrHelper::split(const std::string& inStr, const int8 separator, std::vector<std::string>& outArray)
{
	outArray.clear();
	uint32 begPos = 0;

	for (uint32 i = 0; i < inStr.length(); i++)
	{
		if (inStr[i] == separator)
		{
			outArray.push_back(inStr.substr(begPos, i - begPos));
			begPos = i + 1;
		}
	}

	if (begPos < inStr.length())
	{
		outArray.push_back(inStr.substr(begPos));
	}

	// if (outArray.empty()) 
	// {
	// 	outArray.push_back(inStr);
	// }
}

void StrHelper::split(const std::string& inStr, const std::string& separator, std::vector<std::string>& outArray)
{
	if (inStr.empty() || separator.empty()) return;
	
	outArray.clear();
	size_t start_pos = 0;
	size_t end_pos = 0;
	
	for (;;)
	{
		end_pos = inStr.find(separator, start_pos);
		if (end_pos == std::string::npos) break;
		if (start_pos != end_pos) {
			outArray.push_back(inStr.substr(start_pos, end_pos - start_pos));
		}

		start_pos = end_pos + separator.length();
	}

	// if (outArray.empty()) 
	// {
	// 	outArray.push_back(inStr);
	// }	
}

void StrHelper::split(const std::string& inStr, const int8 separator, std::list<std::string>& outArray) {
	std::vector<std::string> temp_array;
	split(inStr, separator, temp_array);
	outArray.assign(temp_array.begin(), temp_array.end());
}

void StrHelper::split(const std::string& inStr, const std::string& separator, std::list<std::string>& outArray) {
	std::vector<std::string> temp_array;
	split(inStr, separator, temp_array);
	outArray.assign(temp_array.begin(), temp_array.end());
}

void StrHelper::split(const std::string& inStr, const int8 separator, std::set<std::string>& outArray) {
	std::vector<std::string> temp_array;
	split(inStr, separator, temp_array);
	outArray.insert(temp_array.begin(), temp_array.end());
}

void StrHelper::split(const std::string& inStr, const std::string& separator, std::set<std::string>& outArray) {
	std::vector<std::string> temp_array;
	split(inStr, separator, temp_array);
	outArray.insert(temp_array.begin(), temp_array.end());
}

bool StrHelper::getLine(const std::string& inStr, const int8* sepStr, std::list<std::string>& lineList) {
	if (inStr.empty() || sepStr == NULL) {
		return false;
	}
	
	int32 i = 0;
	size_t beg_pos = 0;
	size_t end_pos = 0;
	
	while (inStr[i] != 0) {
		end_pos = inStr.find(sepStr, beg_pos);
		if (end_pos != std::string::npos) {
			lineList.push_back(inStr.substr(beg_pos, end_pos - beg_pos));
			beg_pos = end_pos + 1;
			end_pos = beg_pos;
			i = end_pos;
			continue;
		}

		i++;
	}

	return true;
}

bool StrHelper::getLine(const std::string& inStr, const int8* sepStr, std::set<std::string>& lineSet) {
	if (inStr.empty() || sepStr == NULL) {
		return false;
	}
	
	int32 i = 0;
	size_t beg_pos = 0;
	size_t end_pos = 0;
	
	while (inStr[i] != 0) {
		end_pos = inStr.find(sepStr, beg_pos);
		if (end_pos != std::string::npos) {
			lineSet.insert(inStr.substr(beg_pos, end_pos - beg_pos));
			beg_pos = end_pos + 1;
			end_pos = beg_pos;
			i = end_pos;
			continue;
		}

		i++;
	}

	return true;
}

std::string StrHelper::basename(const std::string& inFilePath)
{
    std::string::size_type pos = inFilePath.find_last_of('/');
    if (pos == std::string::npos)
        return inFilePath;

    return inFilePath.substr(pos + 1, inFilePath.length() - pos -1);
}

std::string StrHelper::basename(const int8* inFilePath)
{
    return basename(std::string(inFilePath));
}

std::string StrHelper::filedir(const std::string& inFilePath)
{
    std::string::size_type pos = inFilePath.find_last_of('/');
    if (pos == std::string::npos)
        return inFilePath;

    return inFilePath.substr(0, pos - 1);
}

std::string StrHelper::filedir(const int8* inFilePath)
{
    return filedir(std::string(inFilePath));
}

int8* ByteHelper::findSubBytes(const int8* data, const uint32 dataLen, const int8* sub, const uint32 subLen)
{
	if (subLen > dataLen)
		return NULL;

	for (uint32 i = 0; i <= (dataLen - subLen); i++)
	{
		uint32 j = 0;
		for (; j < subLen; j++)
		{
			if (sub[j] != data[i + j])
				break;
		}

		if (j == subLen)
		{
			return (int8*)(data + i);
		}
	}

	return NULL;
}

int8* ByteHelper::findByte(const int8* data, const uint32 dataLen, const int8 byte)
{
	for (uint32 i = 0; i < dataLen; i++)
	{
		if (data[i] == byte)
		{
			return (int8*)(data + i);
		}
	}

	return NULL;
}

int8* ByteHelper::findByteR(const int8* data, const uint32 dataLen, const int8 byte)
{
	for (uint32 i = dataLen; i > 0; i--)
	{
		if (data[i] == byte)
		{
			return (int8*)(data + i);
		}
	}

	return NULL;
}

std::string ByteHelper::toHexStr(const int8* data, const uint32 dataLen)
{
	std::string hexStr;
	uint8 temp[4] = {0};

	for (uint32 i = 0; i < dataLen; i++)
	{
		snprintf((char*)temp, 4, "%02x ", data[i]);
		hexStr.append((const char*)temp);
	}

	StrHelper::strupr((int8*)hexStr.c_str());

	return hexStr;
}

void TimeHelper::format(const uint64 usec, TimeHelper::TimeValue& timeValue)
{
	memset(&timeValue, 0, sizeof(TimeValue));

	uint64 second = usec / 1000000LL;
	struct tm* timeStruct = NULL;
	timeStruct = localtime((time_t*)&second);

	uint8 timeBuf[64] = {0};
	strftime((char*)timeBuf, sizeof(timeBuf), "%Y", timeStruct);
	timeValue.year = (uint16)StrHelper::toInt((const uint8*)timeBuf);
	strftime((char*)timeBuf, sizeof(timeBuf), "%m", timeStruct);
	timeValue.month = (uint8)StrHelper::toInt((const uint8*)timeBuf);
	strftime((char*)timeBuf, sizeof(timeBuf), "%d", timeStruct);
	timeValue.day = (uint8)StrHelper::toInt((const uint8*)timeBuf);
	strftime((char*)timeBuf, sizeof(timeBuf), "%H", timeStruct);
	timeValue.hour = (uint8)StrHelper::toInt((const uint8*)timeBuf);
	strftime((char*)timeBuf, sizeof(timeBuf), "%M", timeStruct);
	timeValue.minute = (uint8)StrHelper::toInt((const uint8*)timeBuf);
	strftime((char*)timeBuf, sizeof(timeBuf), "%S", timeStruct);
	timeValue.sec = (uint8)StrHelper::toInt((const uint8*)timeBuf);
	timeValue.msec = (uint16)(usec % 1000000LL / 1000LL);
	timeValue.usec = (uint16)(usec % 1000LL);
}

std::string TimeHelper::format(const uint64 usec)
{
	TimeValue timeValue;
	format(usec, timeValue);

	uint32 tempBufSize = 64;
	uint8 tempBuf[64] = {0};

	snprintf((char*)tempBuf, (size_t)tempBufSize, "%04d-%02d-%02d %02d:%02d:%02d:%03d:%03d", 
		timeValue.year, timeValue.month, timeValue.day, 
		timeValue.hour, timeValue.minute, 
		timeValue.sec, timeValue.msec, timeValue.usec);

	return std::string((const char*)tempBuf);
}

uint32 NetHelper::ipToInt(const std::string& strIP)
{
    std::vector<std::string> ipStrArray;
    StrHelper::split(strIP, '.', ipStrArray);

    if (ipStrArray.size() != 4)
        return 0;
     
    return (StrHelper::toInt(ipStrArray[0]) << 24) 
        + (StrHelper::toInt(ipStrArray[1]) << 16)  
        + (StrHelper::toInt(ipStrArray[2]) << 8) 
        + StrHelper::toInt(ipStrArray[3]);      
}

std::string NetHelper::ipToStr(const uint32 intIP)
{
    return (StrHelper::toStr((intIP >> 24) & 0xFF)) + "." 
        + (StrHelper::toStr((intIP >> 16) & 0xFF)) + "."  
        + (StrHelper::toStr((intIP >> 8) & 0xFF)) + "." 
        + (StrHelper::toStr(intIP & 0xFF));
}

/*
std::string AlgHelper::md5Str(const std::string& inStr)
{
    #if 0
    std::string md5;
    std::string cmd = "openssl md5 " + filePath;

    int8 outBuf[33] = {0};
    if (System::shell(cmd.c_str(), outBuf, 33))
        md5.assign(outBuf);
    
    return md5;
    #endif

    std::string md5Str;
    
    Md5 md5;
    uint8 md5Val[33] = {0};
    md5.md5Str((int8*)inStr.c_str(), md5Val);
    md5Str.assign(md5Val);
    
    return md5Str;
}
*/

std::string AlgHelper::md5Bytes(const int8* bytes, const uint32 len)
{
    if (bytes == NULL || len == 0)
        return "";
    
    std::string md5Val;
    Md5 md5;
    int8 md5Buf[33] = {0};
    md5.md5Bytes((int8*)bytes, len, md5Buf);
    md5Val.assign(md5Val);
    return md5Val;
}

std::string AlgHelper::md5File(const int8* filePath)
{
    if (filePath == NULL)
        return "";

    std::string md5Val;
    Md5 md5;
    int8 md5Buf[33] = {0};
    md5.md5File((int8*)filePath, md5Buf);
    md5Val.assign(md5Val);
    return md5Val;
}
}

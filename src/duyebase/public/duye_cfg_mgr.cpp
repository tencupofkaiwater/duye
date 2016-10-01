/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_cfg_mgr.cpp
* @version     
* @brief      
* @author   duye
* @date     2014-09-28
* @note 
*
*  1. 2014-09-28 duye Created this file
*/

#include <string>
#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_cfg_mgr.h>

static const int8* DUYE_LOG_PREFIX = "duye.public.cfgmgr";

namespace duye {

CfgMgr::CfgMgr() {}
CfgMgr::CfgMgr(const std::string& filePath) : m_cfgFilePath(filePath) {}
CfgMgr::~CfgMgr() {}

bool CfgMgr::load()
{
    if (m_cfgFilePath.empty())
    {
        DUYE_ERROR("configuration file path is empty");
        return false;
    }
    
    return load(m_cfgFilePath);
}

bool CfgMgr::load(const std::string& filePath)
{
	m_cfgFilePath = filePath;
    if (!m_cfgDoc.loadFile(m_cfgFilePath))
    {
        DUYE_ERROR("load configuration file %s failed:%s, line:%d", 
			m_cfgFilePath.c_str(), m_cfgDoc.errorDesc(), m_cfgDoc.errorRow());
        return false;        
    }    
    
    return true;
}

bool CfgMgr::loadData(const int8* cfgData)
{
    if (cfgData == NULL)
    {
        DUYE_ERROR("cfg_data == NULL");
        return false;                
    }
    
    return true;
}

bool CfgMgr::loadData(const std::string cfgData)
{
    return loadData(cfgData.c_str());
}

bool CfgMgr::setValue(const std::string& path, const bool value)
{
    return setText(path, StrHelper::toStr(value));
}

bool CfgMgr::setValue(const std::string& path, const int32 value)
{
    return setText(path, StrHelper::toStr(value));
}

bool CfgMgr::setValue(const std::string& path, const int64 value)
{
    return setText(path, StrHelper::toStr(value));
}

bool CfgMgr::setValue(const std::string& path, const uint32 value)
{
    return setText(path, StrHelper::toStr(value));
}

bool CfgMgr::setValue(const std::string& path, const uint64 value)
{
    return setText(path, StrHelper::toStr(value));
}

bool CfgMgr::setValue(const std::string& path, const int8* value)
{
    return setText(path, StrHelper::toStr(value));
}

bool CfgMgr::setValue(const std::string& path, const std::string& value)
{
    return setText(path, value);
}

bool CfgMgr::getValue(const std::string& path, bool& value)
{
    std::string text = getText(path);
	if (text.empty())
		return false;

	value = StrHelper::toBool(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int16& value)
{
    std::string text = getText(path);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int32& value)
{
    std::string text = getText(path);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int64& value)
{
    std::string text = getText(path);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint16& value)
{
    std::string text = getText(path);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint32& value)
{
    std::string text = getText(path);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint64& value)
{
    std::string text = getText(path);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, std::string& value)
{
    std::string text = getText(path);
	if (text.empty())
		return false;

	value = text;

	return true;
}

bool CfgMgr::getValue(const std::string& path, int8* buffer, const uint64 size)
{
    std::string text = getText(path);
	if (text.empty())
		return false;

	uint32 copyLen = text.size() > size ? size : text.size();
	memcpy(buffer, text.c_str(), copyLen);

	return true;
}

std::string CfgMgr::getValue(const std::string& path)
{
	return getText(path);
}

bool CfgMgr::save()
{
    return true;
}

void CfgMgr::print()
{
	m_cfgDoc.print();
}

std::string CfgMgr::getText(const std::string& path)
{
	std::string outText;
	std::vector<std::string> pathArray;
	StrHelper::split(path, '.', pathArray);
	if (pathArray.size() <= 1 || pathArray.size() > 3)
	{
		DUYE_ERROR("pathArray.size() <= 1 || pathArray.size() > 3");
		return "";
	}
	
	XmlElement* rootElement = m_cfgDoc.rootElement();
	if (rootElement == NULL)
	{
		DUYE_ERROR("rootElement == NULL");
	    return "";		
	}
	
	if (rootElement->valueStr() != pathArray[0])
	{
		DUYE_ERROR("rootElement->valueStr() != pathArray[0], %s = %s", rootElement->value(), pathArray[0].c_str());
	    return "";		
	}

	const int8* tempText = NULL;
	XmlElement* childElement = rootElement->firstChildElement();
	for (; childElement != NULL; childElement = childElement->nextSiblingElement())
	{
		if (childElement->valueStr() == pathArray[1])
		{
			if (pathArray.size() == 2)
			{
				tempText = childElement->getText();
				if (tempText == NULL)
					return "";

				outText.assign(tempText);
			}
			
			XmlElement* childElement2 = childElement->firstChildElement();
			for (; childElement2 != NULL; childElement2 = childElement2->nextSiblingElement())
			{
				if (childElement->valueStr() == pathArray[2])
				tempText = childElement->getText();
				if (tempText == NULL)
					return "";

				outText.assign(tempText);
			}
		}        
	}
	
	return outText;
}

bool CfgMgr::setText(const std::string& path, const std::string& val)
{
	return true;
}

}

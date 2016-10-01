/***********************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_ini_section.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-03-15
* @note 
*
*  2. 2014-06-26 duye removal to gohoop project
*
*  1. 2014-03-15 duye Created this file
* 
*/
#include <duye_ini_section.h>

namespace duye {

IniSection::IniSection() {}
IniSection::IniSection(const std::string& sectionName)
{
    m_sectionName = sectionName;
}

IniSection::~IniSection() {}

bool IniSection::getPara(const std::string& para, std::string& value)
{
    AutoLock autoLock(m_mapMutex);

    KeyValueMap::iterator iter = m_keyValueMap.find(para);
    if (iter == m_keyValueMap.end())
    {
    	return false;
    }

    value.assign(iter->second);
    return true;    
}

bool IniSection::setPara(const std::string& para, const std::string& value)
{
    AutoLock autoLock(m_mapMutex);

    KeyValueMap::iterator iter = m_keyValueMap.find(para);
    if (iter == m_keyValueMap.end())
    {
    	return false;
    }

    iter->second = value;
    return true;   
}

bool IniSection::addPara(const std::string& para, const std::string& value)
{
    AutoLock autoLock(m_mapMutex);

    KeyValueMap::iterator iter = m_keyValueMap.find(para);
    if (iter != m_keyValueMap.end())
    {
    	return false;
    }

    m_keyValueMap.insert(std::make_pair(para, value)); 
    return true;
}

bool IniSection::delPara(const std::string& para)
{
    AutoLock autoLock(m_mapMutex);

    KeyValueMap::iterator iter = m_keyValueMap.find(para);
    if (iter == m_keyValueMap.end())
    {
    	return false;
    }

    m_keyValueMap.erase(iter);
    return true;
}

const IniSection::KeyValueMap& IniSection::getkeyValueMap() const
{
    return m_keyValueMap; 
}
}

/***********************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_ini_section.h
* @version     
* @brief      
* @author   duye
* @date	    2014-03-15
* @note 
*
*  2. 2014-06-26 duye removal to gohoop project
*  1. 2014-03-15 duye Created this file
* 
*/

#pragma once

#include <map>
#include <string>
#include <duye_system.h>

namespace duye {

/** 
 * @brief ini file section
 */
class IniSection
{
public:
    /** 
     * @brief key-value map
     */
    typedef std::map<std::string, std::string> KeyValueMap;

public:
    IniSection();

    /**
     * @brief constructor
     * @param [in] sectionName : section name
     * @return KeyValueMap const reference
     * @note 
     */    
    explicit IniSection(const std::string& sectionName);
    ~IniSection();

    /**
     * @brief get value
     * @param [in] para : parameter
     * @param [in] value : value
     * @return true/false
     * @note 
     */
    bool getPara(const std::string& para, std::string& value); 

    /**
     * @brief set value
     * @param [in] para : parameter
     * @param [in] value : value
     * @return true/false
     * @note 
     */
    bool setPara(const std::string& para, const std::string& value);    

    /**
     * @brief add parameter ane value
     * @param [in] para : parameter
     * @param [in] value : value
     * @return true/false
     * @note 
     */
    bool addPara(const std::string& para, const std::string& value);

    /**
     * @brief delete parameter
     * @param [in] para : parameter
     * @return true/false
     * @note 
     */
    bool delPara(const std::string& para);

    /**
     * @brief get keyValueMap
     * @return m_keyValueMap 
     * @note 
     */
    const KeyValueMap& getkeyValueMap() const;   
    
private:
    std::string   		m_sectionName;
    KeyValueMap	m_keyValueMap;
    Mutex			m_mapMutex;
};
}

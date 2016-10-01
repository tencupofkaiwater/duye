/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_ini.h
* @version     
* @brief      
* @author   duye
* @date	    2013-11-15
* @note 
*
*  1. 2013-11-15 duye created this file
* 
*/
#pragma once

#include <map>
#include <string>
#include <duye_system.h>

namespace duye {

class IniSection;

/** 
* @brief ini file section map
* <section_name, ini_section>
*/
typedef std::map<std::string, IniSection*> IniSectionMap;

/** 
 * @brief POSIX condition wrapper
 */
class IniFile
{
public:
    IniFile();

    /**
     * @brief constructor
     * @param [in] filePath : file path
     * @note 
     */ 
    IniFile(const std::string& filePath);

    ~IniFile();

    /**
     * @brief load file
     * @param [in] filePath : file path
     * @return true/false
     * @note 
     */
    bool loadFile(const std::string& filePath);

    /**
     * @brief import data from buffer
     * @param [in] data : file data
     * @return true/false
     * @note 
     */     
    bool importData(const std::string& data);

    /**
     * @brief import data from buffer
     * @param [in] data : file data
     * @param [in] length : data length
     * @return true/false
     * @note 
     */     
    bool importData(const int8* data, const uint64 length);    

    /**
     * @brief get value
     * @param [in] section : section name
     * @param [in] paraName : parameter name
     * @param [out] value : return value
     * @return true/false
     * @note 
     */ 
    bool getParaVal(const std::string& section, 
        const std::string& paraName, 
        std::string& value);

    /**
     * @brief set value
     * @param [in] section : section name
     * @param [in] paraName : parameter name
     * @param [in] value : set value
     * @return true/false
     * @note 
     */ 
    bool setParaVal(const std::string& section, 
        const std::string& paraName, 
        const std::string& value);    
	    
    /**
     * @brief del section
     * @param [in] section : section name
     * @param [in] paraName : parameter name
     * @param [in] value : set value
     * @return true/false
     * @note 
     */ 
    bool delSection(const std::string& section);

    /**
     * @brief del parameter
     * @param [in] section : section name
     * @param [in] paraName : parameter name
     * @param [in] value : set value
     * @return true/false
     * @note 
     */
    bool delPara(const std::string& section, const std::string& paraName); 

    /**
     * @brief save configuration to file
     * @return true/false
     * @note 
     */
    bool saveFile();  

    /**
     * @brief save configuration to file
     * @return true/false
     * @note 
     */ 
    bool saveFile(const std::string& filePath);    

    /**
     * @brief get error string
     * @return error string
     * @note 
     */
    int8* error();     

private:
    void cleanSectionMap();
    bool parserSection(const int8* data, const uint64 length, uint64& offset);
    bool getOneLine(const int8* data, const uint64 length, std::string& lineStr); 

private:
    std::string	    m_filePath;
    IniSectionMap   m_iniSectionMap;
    Mutex	    	m_mapMutex;
    Error*    		m_error;
};
}

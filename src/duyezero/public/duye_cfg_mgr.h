/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_cfg_mgr.h
* @version     
* @brief      
* @author   duye
* @date     2014-09-28
* @note 
*
*  1. 2014-09-28 duye Created this file
* 
*/
#pragma once

#include <string>
#include <duye_type.h>
#include <duye_system.h>
#include <duye_xml.h>

namespace duye {

/**
 * @brief configuration manager class
 */
class CfgMgr
{
public:
    CfgMgr();
    explicit CfgMgr(const std::string& filePath);
    ~CfgMgr();
    
    /**
     * @breif load configuration
     * @return true/false
     */
    bool load();
    bool load(const std::string& filePath);
    bool loadData(const int8* cfgData);
    bool loadData(const std::string cfgData);
    
    /**
     * @brief set configuration value
     * @param [in] path : parameter path, like : dfscfg.server.port
     * @param [in] value : set value
     * @return true/false
     */
    bool setValue(const std::string& path, const bool value);
    bool setValue(const std::string& path, const int32 value);
    bool setValue(const std::string& path, const int64 value);
    bool setValue(const std::string& path, const uint32 value);
    bool setValue(const std::string& path, const uint64 value);
    bool setValue(const std::string& path, const int8* value);
    bool setValue(const std::string& path, const std::string& value);
    
    /**
     * @brief get configuration value
     * @param [in] path : parameter path, like : dfscfg.server.port
     * @param [out] value : get value
     * @return true/false
     */
    bool getValue(const std::string& path, bool& value);
    bool getValue(const std::string& path, int16& value);
    bool getValue(const std::string& path, int32& value);
    bool getValue(const std::string& path, int64& value);
    bool getValue(const std::string& path, uint16& value);
    bool getValue(const std::string& path, uint32& value);
    bool getValue(const std::string& path, uint64& value);
    bool getValue(const std::string& path, std::string& value);
	std::string getValue(const std::string& path);
    
    /**
     * @brief get configuration data
     * @param [in] path : parameter path, like : dfscfg.server.port
     * @param [out] buffer : data buffer
     * @param [in] size : data buffer size
     * @return true/false
     */    
    bool getValue(const std::string& path, int8* buffer, const uint64 size);
    
    /**
     * @brief save configuration 
     * @return true/false
     */
    bool save();

    /**
     * @brief printf config
     * @return 
     */
    void print();	

private:
	std::string getText(const std::string& path);
	bool setText(const std::string& path, const std::string& val);
    
private:
    std::string     m_cfgFilePath;
    XmlDocument 	m_cfgDoc;
};
}

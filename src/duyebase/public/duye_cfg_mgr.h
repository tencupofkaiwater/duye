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

// conf example
/*
	<mangjing>
		<node name="global">
	   		<!--mangjing root directory-->
	   		<param name="mangjing_root" value="/etc/mangjing/">
	    		<!--cpu limit, value is %x-->
	   		<param name="cpu_precent" value="30">
		</node>
		<node name="module">
	   		<!--status on/off-->
	   		<param name="sys_info" status="on"/>
		</node>
	</mangjing>
*/

class NodeAndNamePair {
public:
	NodeAndNamePair(const std::string& innode, const std::string& inname) : node(innode), name(inname) {}
	std::string node;
	std::string name;
};

/**
 * @brief configuration manager class
 */
class CfgMgr
{
public:
	typedef std::list<std::list<std::pair<std::string/*attr_name*/, std::string/*attr_value*/> > > NodeList;

public:
    CfgMgr();
    explicit CfgMgr(const std::string& filePath);
    ~CfgMgr();

	static CfgMgr& ins();
    
    /**
     * @breif load configuration
     * @return true/false
     */
    bool load();
    bool load(const std::string& filePath);
    bool loadData(const int8* cfgData);
    bool loadData(const std::string cfgData);
    
    /**
     * @brief get configuration value
     * @param [in] path : parameter path, like : dfscfg.server.port
     * @param [out] value : get value
     * @return true/false
     * @note: ex : setValue("node:global.param:cpu_precent", value);
     *	<mangjing>
     * 		<node name="global">
     *     		<!--mangjing root directory-->
     *     		<param name="mangjing_root" value="/etc/mangjing/">
     *      		<!--cpu limit, value is %x-->
     *     		<param name="cpu_precent" value="30">
     * 		</node>
     * 		<node name="module">
     *     		<!--status on/off-->
     *     		<param name="sys_info" status="on"/>
     * 		</node>
  	 *	</mangjing>
     */
    bool setValue(const std::string& path, const bool value, int8* attName = NULL);
    bool setValue(const std::string& path, const int32 value, int8* attName = NULL);
    bool setValue(const std::string& path, const int64 value, int8* attName = NULL);
    bool setValue(const std::string& path, const uint32 value, int8* attName = NULL);
    bool setValue(const std::string& path, const uint64 value, int8* attName = NULL);
    bool setValue(const std::string& path, const int8* value, int8* attName = NULL);
    bool setValue(const std::string& path, const std::string& value, int8* attName = NULL);
    
    /**
     * @brief get configuration value
     * @param [in] path : parameter path, like : dfscfg.server.port
     * @param [out] value : get value
     * @return true/false
     * @note: ex : getValue("node:global.param:cpu_precent", value);
     * getValue("node_name:name_value.node_name:name_value", value);
     *	<mangjing>
     * 		<node name="global">
     *     		<!--mangjing root directory-->
     *     		<param name="mangjing_root" value="/etc/mangjing/">
     *      		<!--cpu limit, value is %x-->
     *     		<param name="cpu_precent" value="30">
     * 		</node>
     * 		<node name="module">
     *     		<!--status on/off-->
     *     		<param name="sys_info" status="on"/>
     * 		</node>
  	 *	</mangjing>
     */
    bool getValue(const std::string& path, bool& value, int8* attName = NULL);
    bool getValue(const std::string& path, int16& value, int8* attName = NULL);
    bool getValue(const std::string& path, int32& value, int8* attName = NULL);
    bool getValue(const std::string& path, int64& value, int8* attName = NULL);
    bool getValue(const std::string& path, uint16& value, int8* attName = NULL);
    bool getValue(const std::string& path, uint32& value, int8* attName = NULL);
    bool getValue(const std::string& path, uint64& value, int8* attName = NULL);
    bool getValue(const std::string& path, std::string& value, int8* attName = NULL);
	std::string getValue(const std::string& path, int8* attName = NULL);

	bool getNodes(const std::string& path, const std::list<std::string>& attrList, NodeList& nodeList);
    
    /**
     * @brief save configuration 
     * @return true/false
     */
    bool save();

    /**
     * @brief printf config
     * @return 
     */
    void toString(std::string& outString);

    /**
     * @brief get last error string
     * @return error
     * @note 
     */		
    uint8* error();	

private:
	std::string getText(const std::string& path, int8* attName);
	bool setText(const std::string& path, const std::string& val, int8* attName);
	bool parsePath(const std::string& path, std::list<duye::NodeAndNamePair>& nodeAndNameList);
	XmlElement* getNode(const std::list<duye::NodeAndNamePair>& nodeAndNameList);
	bool getNodeList(const std::list<duye::NodeAndNamePair>& nodeAndNameList, const std::list<std::string>& attrList, NodeList& nodeList);
	XmlElement* recursion(XmlElement* node, const std::string& node_name, const std::string& name_attr, bool judge_name = true);
    
private:
	Error			m_error;
    std::string     m_cfgFilePath;
    XmlDocument 	m_cfgDoc;
};
	
}

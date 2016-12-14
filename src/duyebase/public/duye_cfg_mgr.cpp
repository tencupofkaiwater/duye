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
#include <list>
#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_cfg_mgr.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.public.cfgmgr";

CfgMgr::CfgMgr() {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

CfgMgr::CfgMgr(const std::string& filePath) : m_cfgFilePath(filePath) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

CfgMgr::~CfgMgr() {}

CfgMgr& CfgMgr::ins() {
	static CfgMgr ins;
	return ins;
}

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

bool CfgMgr::setValue(const std::string& path, const bool value, const std::string& attName)
{
    return setText(path, StrHelper::toStr(value), attName);
}

bool CfgMgr::setValue(const std::string& path, const bool value)
{
    return setText(path, StrHelper::toStr(value), "");
}

bool CfgMgr::setValue(const std::string& path, const int32 value, const std::string& attName)
{
    return setText(path, StrHelper::toStr(value), attName);
}

bool CfgMgr::setValue(const std::string& path, const int32 value)
{
    return setText(path, StrHelper::toStr(value), "");
}

bool CfgMgr::setValue(const std::string& path, const int64 value, const std::string& attName)
{
    return setText(path, StrHelper::toStr(value), attName);
}

bool CfgMgr::setValue(const std::string& path, const int64 value)
{
    return setText(path, StrHelper::toStr(value), "");
}

bool CfgMgr::setValue(const std::string& path, const uint32 value, const std::string& attName)
{
    return setText(path, StrHelper::toStr(value), attName);
}

bool CfgMgr::setValue(const std::string& path, const uint32 value)
{
    return setText(path, StrHelper::toStr(value), "");
}

bool CfgMgr::setValue(const std::string& path, const uint64 value, const std::string& attName)
{
    return setText(path, StrHelper::toStr(value), attName);
}

bool CfgMgr::setValue(const std::string& path, const uint64 value)
{
    return setText(path, StrHelper::toStr(value), "");
}

bool CfgMgr::setValue(const std::string& path, const int8* value, const std::string& attName)
{
    return setText(path, StrHelper::toStr(value), attName);
}

bool CfgMgr::setValue(const std::string& path, const int8* value)
{
    return setText(path, StrHelper::toStr(value), "");
}

bool CfgMgr::setValue(const std::string& path, const std::string& value, const std::string& attName)
{
    return setText(path, value, attName);
}

bool CfgMgr::setValue(const std::string& path, const std::string& value)
{
    return setText(path, value, "");
}

bool CfgMgr::getValue(const std::string& path, bool& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty())
		return false;

	value = StrHelper::toBool(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, bool& value)
{ 
    std::string text = getText(path, "");
	if (text.empty())
		return false;

	value = StrHelper::toBool(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int16& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int16& value)
{
    std::string text = getText(path, "");
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int32& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int32& value)
{
    std::string text = getText(path, "");
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int64& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int64& value)
{
    std::string text = getText(path, "");
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (int64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint16& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint16& value)
{
    std::string text = getText(path, "");
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint32& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint32& value)
{
    std::string text = getText(path, "");
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint64& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint64& value)
{
    std::string text = getText(path, "");
	if (text.empty() || !StrHelper::isNums(text))
		return false;

	value = (uint64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, std::string& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty())
		return false;

	value = text;

	return true;
}

bool CfgMgr::getValue(const std::string& path, std::string& value)
{
    std::string text = getText(path, "");
	if (text.empty())
		return false;

	value = text;

	return true;
}

std::string CfgMgr::getValue(const std::string& path, const std::string& attName) {
	if (attName.empty()) return "";
	return getText(path, attName);	
}

std::string CfgMgr::getValue(const int8* path, const int8* attName) {
	if (!attName || strlen(attName) == 0) return "";
	return getText(path, attName);
}

std::string CfgMgr::getValue(const std::string& path) {
	return getText(path, "");		
}

std::string CfgMgr::getValue(const int8* path) {
	if (!path) return "";
	return getText(path, "");
}

bool CfgMgr::getNodes(const std::string& path, const std::list<std::string>& attrList, ParamNodeList& nodeList) {
	std::list<duye::NodeAndNamePair> node_and_name_list;
	if (!parsePath(path, node_and_name_list)) return "";

	std::list<NodeAndNamePair>::const_iterator iter = node_and_name_list.begin();
	for (; iter != node_and_name_list.end(); ++iter) {
		if (iter->node == node_and_name_list.back().node) {
			if (iter->node.empty() || !iter->name.empty()) {
				ERROR_DUYE_LOG("path(%s) error:last node not need name value", path.c_str());
			}
		} else if (iter->node.empty() || iter->name.empty()) {
			ERROR_DUYE_LOG("path(%s) error:node or name is empty", path.c_str());
			return "";
		}
	}

	return getNodeList(node_and_name_list, attrList, nodeList);
}

bool CfgMgr::save()
{
    return true;
}

void CfgMgr::toString(std::string& outString)
{
	//m_cfgDoc.print();
}

uint8* CfgMgr::error() {
	return m_error.error;
}

std::string CfgMgr::getText(const std::string& path, const std::string& attName)
{	
	std::list<duye::NodeAndNamePair> node_and_name_list;
	if (!parsePath(path, node_and_name_list)) return "";

	std::list<NodeAndNamePair>::const_iterator iter = node_and_name_list.begin();
	for (; iter != node_and_name_list.end(); ++iter) {
		if (iter->node.empty() || iter->name.empty()) {
			ERROR_DUYE_LOG("path(%s) error:node or name is empty", path.c_str());
			return "";
		}
	}	

	XmlElement* node = getNode(node_and_name_list);
	if (!node) return "";

	if (attName.empty()) {
		return node->getText();
	} else {
		return *(node->attribute(attName));
	}	

	return "";
}

bool CfgMgr::setText(const std::string& path, const std::string& val, const std::string& attName)
{	
	std::list<duye::NodeAndNamePair> node_and_name_list;
	if (!parsePath(path, node_and_name_list)) return false;

	std::list<NodeAndNamePair>::const_iterator iter = node_and_name_list.begin();
	for (; iter != node_and_name_list.end(); ++iter) {
		if (iter->node.empty() || iter->name.empty()) {
			ERROR_DUYE_LOG("path(%s) error:node or name is empty", path.c_str());
			return "";
		}
	}	

	XmlElement* node = getNode(node_and_name_list);
	if (!node) return false;

	if (attName.empty()) {
		node->setText(val.c_str());
	} else {
		node->setAttribute(attName, val);
	}	
	
	m_cfgDoc.saveFile(m_cfgFilePath);
	
	return true;
}

bool CfgMgr::parsePath(const std::string& path, std::list<duye::NodeAndNamePair>& nodeAndNameList) {
	std::list<std::string> node_list;
	StrHelper::split(path, '.', node_list);
	if (node_list.empty()) {
		ERROR_DUYE_LOG("parse path error");
		return false;
	}
	
	std::list<std::string>::iterator iter = node_list.begin();
	for (; iter != node_list.end(); ++iter) {
		std::vector<std::string> node_name_vec;
		StrHelper::split(path, ':', node_name_vec);
		if (node_name_vec.size() == 1) {
			nodeAndNameList.push_back(NodeAndNamePair(node_name_vec[0], ""));
		} else if (node_name_vec.size() == 2) {
			nodeAndNameList.push_back(NodeAndNamePair(node_name_vec[0], node_name_vec[1]));
		} else {
			ERROR_DUYE_LOG("parse node and name error");
			return false;			
		}
	}

	return true;
}

XmlElement* CfgMgr::getNode(const std::list<duye::NodeAndNamePair>& nodeAndNameList) {
	XmlElement* root = m_cfgDoc.rootElement();
	if (root == NULL) {
		ERROR_DUYE_LOG("root == NULL");
		return NULL;
	}

	XmlElement* node = root->firstChildElement();
	if (node == NULL) {
		ERROR_DUYE_LOG("FirstChildElement == NULL");
		return NULL;
	}

	XmlElement* found_node = node;
	std::list<NodeAndNamePair>::const_iterator pair_iter = nodeAndNameList.begin();
	for (; pair_iter != nodeAndNameList.end(); ++pair_iter) {
		found_node = recursion(found_node, pair_iter->node, pair_iter->name);
		if (!found_node) {
			break;
		} else {
			found_node = found_node->firstChildElement();
		}
	}

	return found_node;
}

bool CfgMgr::getNodeList(const std::list<duye::NodeAndNamePair>& nodeAndNameList, const std::list<std::string>& attrList, ParamNodeList& nodeList) {
	XmlElement* root = m_cfgDoc.rootElement();
	if (root == NULL) {
		ERROR_DUYE_LOG("root == NULL");
		return false;
	}

	XmlElement* node = root->firstChildElement();
	if (node == NULL) {
		ERROR_DUYE_LOG("FirstChildElement == NULL");
		return false;
	}

	XmlElement* found_node = node;
	bool judge_name = true;
	std::list<NodeAndNamePair>::const_iterator iter = nodeAndNameList.begin();
	for (; iter != nodeAndNameList.end(); ++iter) {
		if (iter->name.empty()) {
			judge_name = false;
		}
		
		found_node = recursion(found_node, iter->node, iter->name, judge_name);
		if (!found_node) {
			break;
		} else {
			found_node = found_node->firstChildElement();
		}
	}

	if (found_node) {
		while (found_node) {
			ParamNode param_node;
			std::list<std::string>::const_iterator attr_iter = attrList.begin();
			for (; attr_iter != attrList.end(); ++attr_iter) {
				const int8* value = found_node->attribute(attr_iter->c_str());
				if (value) {
					param_node.addPair(*attr_iter, value);
				}
			}
			
			nodeList.push_back(param_node);			
			found_node = found_node->nextSiblingElement();
		}
	} else {
		return false;
	}

	return true;
}

XmlElement* CfgMgr::recursion(XmlElement* node, const std::string& node_name, const std::string& name_attr, bool judge_name) {
	if (!node) {
		return NULL;
	}

	if (judge_name && name_attr.empty()) return NULL;

	if (node->value() != node_name) {
		return recursion(node->nextSiblingElement(), node_name, name_attr, judge_name);
	} else if (judge_name) {
		const int8* value = node->attribute("name");
		if (value == NULL || value != name_attr) {
			return recursion(node->nextSiblingElement(), node_name, name_attr, judge_name);
		}
	}
	
	return node;
}

}

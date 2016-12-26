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

CfgMgr::CfgMgr() {}

CfgMgr::~CfgMgr() {}

CfgMgr& CfgMgr::ins() {
	static CfgMgr ins;
	return ins;
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
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	value = StrHelper::toBool(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, bool& value)
{ 
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	value = StrHelper::toBool(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int16& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int16& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int32& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int32& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (int32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int64& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (int64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, int64& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (int64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint16& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint16& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint32& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint32& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (uint32)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint64& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (uint64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, uint64& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	if (!StrHelper::isNums(text)) {
		DUYE_ERROR("content isn't number");
		return false;
	}

	value = (uint64)StrHelper::toInt(text);

	return true;
}

bool CfgMgr::getValue(const std::string& path, std::string& value, const std::string& attName)
{
	if (attName.empty()) return false;
	
    std::string text = getText(path, attName);
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	value = text;

	return true;
}

bool CfgMgr::getValue(const std::string& path, std::string& value)
{
    std::string text = getText(path, "");
	if (text.empty()) {
		DUYE_ERROR("content is empty");
		return false;
	}

	value = text;

	return true;
}

std::string CfgMgr::getValue(const std::string& path, const std::string& attName) {
	if (attName.empty()) {
		DUYE_ERROR("input 'attName' is empty");
		return "";
	}
	
	return getText(path, attName);	
}

std::string CfgMgr::getValue(const int8* path, const int8* attName) {
	if (!attName || strlen(attName) == 0) {
		DUYE_ERROR("input attName == null or is empty");
		return "";
	}
	
	return getText(path, attName);
}

std::string CfgMgr::getValue(const std::string& path) {
	return getText(path, "");		
}

std::string CfgMgr::getValue(const int8* path) {
	if (!path) {
		DUYE_ERROR("input path == null");
		return "";
	}
	return getText(path, "");
}

bool CfgMgr::getNodes(const std::string& path, const std::list<std::string>& attrList, ParamNodeList& nodeList) {
	DUYE_DEBUG("path : %s", path.c_str());
	
	std::list<duye::NodeAndNamePair> node_and_name_list;
	if (!parsePath(path, node_and_name_list)) return false;

	std::list<NodeAndNamePair>::const_iterator iter = node_and_name_list.begin();
	for (; iter != node_and_name_list.end(); ++iter) {
		DUYE_DEBUG("node:%s, name:%s", iter->node.c_str(), iter->name.c_str());
		if (iter->node == node_and_name_list.back().node) {
			DUYE_DEBUG("last node:%s", iter->node.c_str());
			if (iter->node.empty() || !iter->name.empty()) {
				DUYE_ERROR("path(%s) error:last node not need name value", path.c_str());
			}
		} else if (iter->node.empty() || iter->name.empty()) {
			DUYE_ERROR("path(%s) error:node or name is empty", path.c_str());
			return false;
		}
	}

	if (node_and_name_list.empty()) {
		DUYE_DEBUG("node_and_name_list is empty");
		return false;
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

const std::string& CfgMgr::getConfPath() const {
	return m_cfgFilePath;
}

std::string CfgMgr::getText(const std::string& path, const std::string& attName)
{	
	std::list<duye::NodeAndNamePair> node_and_name_list;
	if (!parsePath(path, node_and_name_list)) return "";

	std::list<NodeAndNamePair>::const_iterator iter = node_and_name_list.begin();
	for (; iter != node_and_name_list.end(); ++iter) {
		if (iter->node.empty() || iter->name.empty()) {
			DUYE_ERROR("path(%s) error:node or name is empty", path.c_str());
			return "";
		}
	}	

	XmlElement* node = getNode(node_and_name_list);
	if (!node) {
		DUYE_ERROR("getNode() == null, by path:'%s'", path.c_str());
		return "";
	}

	if (attName.empty()) {
		DUYE_INFO("getText");
		const int8* text = node->getText();
		if (text) {
			return text;
		} else {
			return "";
		}
	} else {
		DUYE_INFO("getAttribute");
		const std::string* value = node->attribute(attName);
		if (value) {
			return *value;
		} else {
			return "";
		}
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
			DUYE_ERROR("path(%s) error:node or name is empty", path.c_str());
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
		DUYE_ERROR("parse path by '.' error");
		return false;
	}
	
	std::list<std::string>::iterator iter = node_list.begin();
	for (; iter != node_list.end(); ++iter) {
		std::vector<std::string> node_name_vec;
		StrHelper::split(*iter, ':', node_name_vec);
		if (node_name_vec.size() == 1) {
			nodeAndNameList.push_back(NodeAndNamePair(node_name_vec[0], ""));
		} else if (node_name_vec.size() == 2) {
			nodeAndNameList.push_back(NodeAndNamePair(node_name_vec[0], node_name_vec[1]));
		} else {
			DUYE_ERROR("parse path:'%s' by ':' to get node and name error", path.c_str());
			return false;			
		}
	}

	return true;
}

XmlElement* CfgMgr::getNode(const std::list<duye::NodeAndNamePair>& nodeAndNameList) {
	XmlElement* root = m_cfgDoc.rootElement();
	if (root == NULL) {
		DUYE_ERROR("root == NULL");
		return NULL;
	}

	XmlElement* node = root->firstChildElement();
	if (node == NULL) {
		DUYE_ERROR("FirstChildElement == NULL");
		return NULL;
	}

	XmlElement* found_node = node;
	uint32 depth = nodeAndNameList.size();
	uint32 curr_depth = 0;
	std::list<NodeAndNamePair>::const_iterator pair_iter = nodeAndNameList.begin();
	for (; pair_iter != nodeAndNameList.end(); ++pair_iter) {
		curr_depth++;
		if (pair_iter->node.empty() || pair_iter->name.empty()) {
			DUYE_ERROR("node or name is empty");
			break;
		}
		
		DUYE_DEBUG("node:%s, name:%s", pair_iter->node.c_str(), pair_iter->name.c_str());
		found_node = recursion(found_node, pair_iter->node, pair_iter->name);
		if (!found_node) {
			DUYE_ERROR("found_node == null");
			break;
		} else if (curr_depth != depth) {
			found_node = found_node->firstChildElement();
		}
	}

	return found_node;
}

bool CfgMgr::getNodeList(const std::list<duye::NodeAndNamePair>& nodeAndNameList, const std::list<std::string>& attrList, ParamNodeList& nodeList) {
	DUYE_DEBUG("in %s", __FUNCTION__);
	
	XmlElement* root = m_cfgDoc.rootElement();
	if (root == NULL) {
		DUYE_ERROR("root == NULL");
		return false;
	}

	XmlElement* node = root->firstChildElement();
	if (node == NULL) {
		DUYE_ERROR("FirstChildElement == NULL");
		return false;
	}

	XmlElement* found_node = node;
	bool judge_name = true;
	uint32 depth = nodeAndNameList.size();
	uint32 curr_depth = 0;
	std::list<NodeAndNamePair>::const_iterator iter = nodeAndNameList.begin();
	for (; iter != nodeAndNameList.end(); ++iter) {
		curr_depth++;
		if (iter->name.empty()) {
			judge_name = false;
		}

		DUYE_DEBUG("node:%s, name:%s", iter->node.c_str(), iter->name.c_str());
		found_node = recursion(found_node, iter->node, iter->name, judge_name);
		if (!found_node) {
			break;
		} else if (curr_depth != depth) {
			found_node = found_node->firstChildElement();
		}
	}

	if (found_node) {
		uint32 cnt = 1;
		std::string last_node_name = nodeAndNameList.back().node;		
		while (found_node) {
			if (found_node->value() != last_node_name) {
				found_node = found_node->nextSiblingElement();
				continue;
			}

			DUYE_DEBUG("%d. get attr in node:%s", cnt++, last_node_name.c_str());
			
			ParamNode param_node;
			std::list<std::string>::const_iterator attr_iter = attrList.begin();
			for (; attr_iter != attrList.end(); ++attr_iter) {
				const int8* value = found_node->attribute(attr_iter->c_str());
				if (value) {
					param_node.addPair(*attr_iter, value);
					DUYE_DEBUG("add pair(%s, %s)", attr_iter->c_str(), value);
				}
			}
			
			nodeList.push_back(param_node);
			found_node = found_node->nextSiblingElement();
		}
	} else {
		DUYE_ERROR("found_node == null");
		return false;
	}

	return true;
}

XmlElement* CfgMgr::recursion(XmlElement* node, const std::string& node_name, const std::string& name_attr, bool judge_name) {
	if (!node) {
		DUYE_ERROR("node == null");
		return NULL;
	}

	if (judge_name && name_attr.empty()) {
		DUYE_ERROR("judge_name == true, but name_attr is empty");
		return NULL;
	}

	if (node->value() != node_name) {
		return recursion(node->nextSiblingElement(), node_name, name_attr, judge_name);
	} else if (judge_name) {
		const int8* value = node->attribute("name");
		if (value == NULL) {
			DUYE_ERROR("node->attribute('name') = null");
			return NULL;
		}

		DUYE_DEBUG("node->attribute('name') = %s, name_attr=%s", value, name_attr.c_str());
		if (value != name_attr) {
			DUYE_DEBUG("node->attribute('name') = %s, input:%s, unmatch", value, name_attr.c_str());
			return recursion(node->nextSiblingElement(), node_name, name_attr, judge_name);
		}
	}

	DUYE_DEBUG("find node = %s", node_name.c_str());
	
	return node;
}

}

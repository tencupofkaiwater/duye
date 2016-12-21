/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_url.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-19
* @note 
*
* 1. 2016-12-19 duye Created this file
*/
#include <duye_http_url.h>

namespace duye {

HttpUrl::HttpUrl() {
}

HttpUrl::HttpUrl(const std::string& path) : m_path(path) {}

HttpUrl::~HttpUrl() {
}

void HttpUrl::setPath(const std::string& path) {
	m_path = path;
}

void HttpUrl::addQueryParm(const std::string& name, const std::string& value) {
	m_query_map.insert(std::make_pair(name, value));
}

const std::string& HttpUrl::getPath() const {
	return m_path;
}

std::string HttpUrl::getUrl() {
	std::string url = m_path + "?";
	QueryMap::iterator iter = m_query_map.begin();
	for (; iter != m_query_map.end(); ++iter) {
		if (iter != m_query_map.begin()) {
			url += "&";
		}

		url += iter->first + "=" + iter->second;
	}

	return url;
}

std::string HttpUrl::getUrl() const {
	std::string url = m_path + "?";
	QueryMap::const_iterator iter = m_query_map.begin();
	for (; iter != m_query_map.end(); ++iter) {
		if (iter != m_query_map.begin()) {
			url += "&";
		}

		url += iter->first + "=" + iter->second;
	}

	return url;
}

}
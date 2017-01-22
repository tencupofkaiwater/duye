/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_url.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-19
* @note 
*
* 1. 2016-12-19 duye Created this file
*/

#pragma once

#include <map>
#include <string>
#include <duye_type.h>

namespace duye {

class HttpUrl {
public:
	// <name, value>
	typedef std::map<std::string, std::string> QueryMap;

public:
	HttpUrl();
	explicit HttpUrl(const std::string& path);
	~HttpUrl();

	void setPath(const std::string& path);
	void addQueryParm(const std::string& name, const std::string& value);
	const std::string& getPath() const;
	std::string getUrl();
	std::string getUrl() const;

private:
	std::string m_path;
	QueryMap m_query_map;
};

}
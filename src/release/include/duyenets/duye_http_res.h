/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_res.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/

#pragma once

#include <string>
#include <map>
#include <duye_type.h>
#include <duye_buffer.h>
#include <duye_http_type.h>
#include <duye_http_header.h>

namespace duye {

class HttpRes {
public:
	HttpRes();
	HttpRes(const Buffer& html);
	~HttpRes();

	bool parseResHtml(const Buffer& html);
	const HttpResHeader& getHeader() const;
	const Buffer& getBody() const;
	bool getJsonParaValue(const std::string& name, std::string& value);
	std::string getJsonParaValue(const std::string& name);
	const ParamPairs& getJsonParaMap() const;
	void setStatusCode(const HttpResCode& code);
	HttpResCode getStatusCode();

private:
	bool parseRes(const Buffer& html);
	bool parseBody();
	std::string getHeaderHtml(const Buffer& html);

private:
	Buffer 		m_org_body;
	HttpResHeader m_header;
	ParamPairs 	m_jsons;
};
}
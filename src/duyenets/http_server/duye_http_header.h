/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_header.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-18
* @note 
*
* 1. 2016-12-18 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_helper.h>
#include <duye_http_type.h>

namespace duye {

// <name, value>
typedef std::map<std::string, std::string> ParamPairs;

/* 
 * @biref response status code description define
 */
class HttpResStatusCode {
public:
	// <code, description>
	typedef std::map<HttpResCode, const std::string> StatusCodeDescMap;

public:
	HttpResStatusCode();
	static HttpResStatusCode& ins();
	std::string getDesc(const HttpResCode& code);

private:
	StatusCodeDescMap m_status_code_sesc_map;
};

class HttpMethod {
public:
	typedef std::map<HttpMethodType, const std::string>	MethodNames;
	
public:
	HttpMethod();
	static HttpMethod& ins();	
	std::string getName(const HttpMethodType& type);

private:
	MethodNames m_method_names;
};

class HttpHeaderData {
public:	
	// <HttpHeaderType, name>
	typedef std::map<HttpHeaderType, const std::string> HeaderNames;	
	// <name, HttpHeaderType>
	typedef std::map<const std::string, HttpHeaderType> NameHeaders;		
	// <HttpHeaderType, name>
	typedef std::map<HttpHeaderType, const std::string> DefaultValues;	
	
public:
	HttpHeaderData();
	static HttpHeaderData& ins();
	std::string getName(const HttpHeaderType& type);
	std::string getDefValue(const HttpHeaderType& type);
	HttpHeaderType getHeaderType(const std::string& name);

private:
	HeaderNames m_header_names;
	NameHeaders m_name_headers;
	DefaultValues m_default_values;
};

class HttpReqHeader {
public:
	HttpReqHeader();
	explicit HttpReqHeader(const HttpMethodType& type, const std::string& url);	
	bool setMethod(const HttpMethodType& type);	
	bool setValue(const HttpHeaderType& type, const std::string& value);
	void addQueryPara(const std::string& name, const std::string& value);	
	std::string getValue(const HttpHeaderType& type);
	std::string getHeaderString();

private:
	void init();

private:
	ParamPairs m_querys;
	HttpMethodType m_method;
	std::string m_protocol;
	std::string m_url;
	std::string m_host;
	std::string m_connection;
	std::string m_user_agent;
	std::string m_accept;
	std::string m_referer;
	std::string m_accept_encoding;
	std::string m_language;
};

class HttpResHeader {
public:	
	// <HttpHeaderType, value>
	typedef std::map<HttpHeaderType, const std::string> HeaderMap;
	
public:
	HttpResHeader();	
	HttpResHeader(const std::string& header_html);
	bool parse(const std::string& header_html);
	bool empty();
	bool setHeaderValue(const HttpHeaderType& header_type, const std::string& value);	
	std::string getHeaderValue(const HttpHeaderType& header_type);
	
private:
	bool getPair(const std::string& in_str, std::string& name, std::string& value);
	bool setPair(const std::string& name, const std::string& value);
	
private:
	HeaderMap m_header_map;
};

}
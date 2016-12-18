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
	HttpReqHeader() : m_method(HTTP_GET)
	{
		init();
	}

	explicit HttpReqHeader(const HttpMethodType& type, const std::string& url)
	{
		init();
		setMethod(type);
		setValue(HTTP_REQ_URL, url);
	}	
	
	void setMethod(const HttpMethodType& type) {
		if (type < HTTP_GET || type > HTTP_POST) {
			error = "type error";
			return;
		}

		m_method = type;
	}
	
	void setValue(const HttpHeaderType& type, std::string& value, std::string& error) {
		error.clear();
		
		switch (type) {
			case HTTP_METHOD : {
				error = "HTTP_METHOD setting use setMethod";
				break;
			}
			case HTTP_PROTOCOL : {
				error = "HTTP_PROTOCOL don't need setting";
				break;
			}
			case HTTP_REQ_URL : m_url = value; break;
			case HTTP_REQ_HOST : m_host = value; break;
			case HTTP_CONNECTION : m_connection = value; break;
			case HTTP_REQ_USER_AGENT : m_user_agent = value; break;
			case HTTP_REQ_ACCEPT : m_accept = value; break;
			case HTTP_REQ_REFERER : m_referer = value; break;
			case HTTP_REQ_ACCEPT_ENCODING : m_accept_encoding = value; break;
			case HTTP_REQ_LANGUAGE : m_language = value; break;
			default : error = "type error"; break;
		}		
	}

	void addQueryPara(const std::string& name, const std::string& value) {
		m_querys[name] = value;
	}
	
	std::string getValue(const HttpHeaderType& type, std::string& error) {
		error.clear();
		
		switch (type) {
			case HTTP_METHOD : return HttpMethod::ins().getName(m_method, error);
			case HTTP_PROTOCOL : return m_protocol;
			case HTTP_REQ_URL : return m_url;
			case HTTP_REQ_HOST : return m_host;
			case HTTP_CONNECTION : return m_connection;
			case HTTP_REQ_USER_AGENT : return m_user_agent;
			case HTTP_REQ_ACCEPT : return m_accept;
			case HTTP_REQ_REFERER : return m_referer;
			case HTTP_REQ_ACCEPT_ENCODING : return m_accept_encoding;
			case HTTP_REQ_LANGUAGE : return m_language;
			default : error = "type error"; break;
		}

		return "";
	}

	std::string getHeaderString(std::string& error) {
		error.clear();
		std::string header_string;
		
		if (m_method == HTTP_METHOD_MAX) {
			error = "HTTP_METHOD is empty";
			return header_string;
		}

		if (m_url.empty()) {
			error = "HTTP_URL is empty";
			return header_string;
		}

		header_string.append(HttpMethod::ins().getName(m_method, error));
		if (error.empty()) return "";		
		header_string.append(" " + m_url);
		if (!m_querys.empty()) {
			header_string.append("?");
			ParamPairs::iterator iter = m_querys.begin();
			for (; iter != m_querys.end(); ++iter) {
				if (iter != m_querys.begin()) {
					header_string.append("&");
				}
				
				header_string.append(iter->first + "=" + iter->second);				
			}
		}
		header_string.append(" " + m_protocol + "\n");
		if (!m_host.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_HOST, error) + ": " + m_host + "\n");
		if (!m_connection.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_CONNECTION, error) + ": " + m_connection + "\n");	
		if (!m_user_agent.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_USER_AGENT, error) + ": " + m_user_agent + "\n");		
		if (!m_accept.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_ACCEPT, error) + ": " + m_accept + "\n");	
		if (!m_referer.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_REFERER, error) + ": " + m_referer + "\n");	
		if (!m_accept_encoding.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_ACCEPT_ENCODING, error) + ": " + m_accept_encoding + "\n");	
		if (!m_language.empty())
			header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_LANGUAGE, error) + ": " + m_language + "\n");

		return header_string;
	}

private:
	void init() 
	{
		std::string error;
		m_protocol = HttpHeaderData::ins().getDefValue(HTTP_PROTOCOL, error);
		m_connection = HttpHeaderData::ins().getDefValue(HTTP_CONNECTION, error);
		m_accept = HttpHeaderData::ins().getDefValue(HTTP_REQ_ACCEPT, error);
		m_language = HttpHeaderData::ins().getDefValue(HTTP_REQ_LANGUAGE, error);		
	}

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
	// <HttpHeaderType, value>
	typedef std::map<HttpHeaderType, const std::string> HeaderMap;
	
public:
	HttpResHeader() {}	
	
	HttpResHeader(const std::string& header_html) {
		parse(header_html);
	}
	
	bool parse(const std::string& header_html) {
		std::list<std::string> lineList;
		StrHelper::getLine(header_html, "\r\n", lineList);
		if (lineList.empty()) {
			//ERROR_DUYE_LOG("http response header error");
			return false;
		}

		bool get_protocol = false;
		std::list<std::string>::iterator iter = lineList.begin();
		for (; iter != lineList.end(); ++iter) {
			if (!get_protocol) {
				if (StrHelper::begWith(iter->c_str(), "HTTP/")) {
					std::vector<std::string> split_array;
					StrHelper::split(*iter, ' ', split_array);
					if (split_array.size() != 3) {
						//ERROR_DUYE_LOG("get http protocol error");
						return false;
					} else {
						m_header_map.insert(std::make_pair(HTTP_PROTOCOL, split_array[0]));
						m_header_map.insert(std::make_pair(HTTP_RES_CODE, split_array[1]));
						m_header_map.insert(std::make_pair(HTTP_RES_CODE_DESC, split_array[2]));
					}					
				}

				if (!m_header_map[HTTP_PROTOCOL].empty()) {
					get_protocol = true;
				}
			} else {
				std::string name;
				std::string value;
				if (getPair(*iter, name, value)) {
					//ERROR_DUYE_LOG("get pair from '%s' error", iter->c_str());
					return false;
				} else {
					if (setPair(name, value)) {
						//ERROR_DUYE_LOG("set pair name:'%s', value:'%s' error", name.c_str(), value.c_str());
						return false;
					}
				}
			}
		}		
		
		return true;
	}

	bool empty() {
		return m_header_map[HTTP_PROTOCOL].empty();
	}

	bool setHeaderValue(const HttpHeaderType& header_type, const std::string& value) {
		if (header_type < HTTP_METHOD || header_type >= HTTP_HEADER_MAX) {
			//ERROR_DUYE_LOG("input parameter header_type error");
			return false;
		}

		m_header_map.insert(std::make_pair(header_type, value));
		return true;
	}
	
	std::string getHeaderValue(const HttpHeaderType& header_type);
	
private:
	bool getPair(const std::string& in_str, std::string& name, std::string& value);
	bool setPair(const std::string& name, const std::string& value);
	
private:
	HeaderMap m_header_map;
};

}
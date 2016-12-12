/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_type.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_helper.h>

namespace duye {

enum HttpMethodType {
	HTTP_GET,
	HTTP_HEAD,
	HTTP_PUT,
	HTTP_DELETE,
	HTTP_POST,
	HTTP_METHOD_MAX
};

enum HttpParaType {
	HTTP_QUERY,
	HTTP_JSON,
	HTTP_PARA_MAX
};

enum HttpHeaderType {
	// common type
	HTTP_METHOD,
	HTTP_PROTOCOL,
	HTTP_CONNECTION,

	// request type
	HTTP_REQ_URL,
	HTTP_REQ_HOST,
	HTTP_REQ_USER_AGENT,
	HTTP_REQ_ACCEPT,
	HTTP_REQ_REFERER,
	HTTP_REQ_ACCEPT_ENCODING,	
	HTTP_REQ_LANGUAGE,	
	
	// response type
	HTTP_RES_CODE,
	HTTP_RES_CODE_DESC,
	HTTP_RES_DATE,
	HTTP_RES_SERVER,
	HTTP_RES_LAST_MODIFIED,
	HTTP_RES_ETAG,
	HTTP_RES_ACCEPT_RANGES,
	HTTP_RES_CONTENT_LENGTH,
	HTTP_RES_KEEP_ALIVE,
	HTTP_RES_CONTENT_TYPE,
	
	HTTP_HEADER_MAX
};

// <name, value>
typedef std::map<std::string, std::string> ParamPairs;

class HttpMethod {
	typedef std::map<HttpMethodType, const std::string>	MethodNames;
	
public:
	HttpMethod()
	{
		m_method_names.insert(std::make_pair(HTTP_GET, "get"));
		m_method_names.insert(std::make_pair(HTTP_HEAD, "head"));
		m_method_names.insert(std::make_pair(HTTP_PUT, "put"));
		m_method_names.insert(std::make_pair(HTTP_DELETE, "delete"));
		m_method_names.insert(std::make_pair(HTTP_POST, "post"));
	}

	static HttpMethod& ins() {
		static HttpMethod ins;
		return ins;
	}
	
	std::string getName(const HttpMethodType& type, std::string& error) {
		error.clear();
		
		if (type < HTTP_GET || type > HTTP_POST) {
			error = "type error";
			return "";
		}
		
		return m_method_names[type];
	}

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
	HttpHeaderData()
	{
		// common 
		m_header_names.insert(std::make_pair(HTTP_CONNECTION, "Connection"));

		// request
		m_header_names.insert(std::make_pair(HTTP_REQ_HOST, "Host"));
		m_header_names.insert(std::make_pair(HTTP_REQ_USER_AGENT, "User-Agent"));
		m_header_names.insert(std::make_pair(HTTP_REQ_ACCEPT, "Accept"));
		m_header_names.insert(std::make_pair(HTTP_REQ_REFERER, "Referer"));
		m_header_names.insert(std::make_pair(HTTP_REQ_ACCEPT_ENCODING, "Accept-Encoding"));
		m_header_names.insert(std::make_pair(HTTP_REQ_LANGUAGE, "Accept-Language"));

		// reponse
		m_header_names.insert(std::make_pair(HTTP_RES_DATE, "Date"));
		m_header_names.insert(std::make_pair(HTTP_RES_SERVER, "Server"));
		m_header_names.insert(std::make_pair(HTTP_RES_LAST_MODIFIED, "Last-Modified"));
		m_header_names.insert(std::make_pair(HTTP_RES_ETAG, "ETag"));
		m_header_names.insert(std::make_pair(HTTP_RES_ACCEPT_RANGES, "Accept-Ranges"));
		m_header_names.insert(std::make_pair(HTTP_RES_CONTENT_LENGTH, "Content-Length"));
		m_header_names.insert(std::make_pair(HTTP_RES_KEEP_ALIVE, "Keep-Alive"));
		m_header_names.insert(std::make_pair(HTTP_RES_CONTENT_TYPE, "Content-Type"));

		// common
		m_header_names.insert(std::make_pair(HTTP_PROTOCOL, "HTTP/1.1"));
		m_header_names.insert(std::make_pair(HTTP_CONNECTION, "keep-alive"));
		// request
		m_header_names.insert(std::make_pair(HTTP_REQ_ACCEPT, "text/css,*/*;q=0.1"));
		m_header_names.insert(std::make_pair(HTTP_REQ_LANGUAGE, "zh-CN,zh;q=0.8"));
		// response
		m_header_names.insert(std::make_pair(HTTP_RES_CODE, "200"));
		m_header_names.insert(std::make_pair(HTTP_RES_ACCEPT_RANGES, "bytes"));

		HeaderNames::iterator iter = m_header_names.begin();
		for (; iter != m_header_names.end(); ++iter) {
			m_name_headers[iter->second] = iter->first;
		}
	}

	static HttpHeaderData& ins() {
		static HttpHeaderData ins;
		return ins;
	}
	
	std::string getName(const HttpHeaderType& type, std::string& error) {
		error.clear();

		if (type == HTTP_METHOD || type == HTTP_PROTOCOL || type == HTTP_REQ_URL || type == HTTP_RES_CODE) {
			error = "HTTP_METHOD, HTTP_PROTOCOL, HTTP_REQ_URL, and HTTP_RES_CODE hasn't name";
			return "";
		}			
		
		if (type < HTTP_METHOD || type > HTTP_HEADER_MAX) {
			error = "type error";
			return "";
		}	
		
		return m_header_names[type];
	}

	std::string getDefValue(const HttpHeaderType& type, std::string& error) {
		error.clear();
		DefaultValues::iterator iter = m_default_values.find(type);
		if (iter == m_default_values.end()) {
			error = "hasn't default value";
			return "";
		}

		return iter->second;
	}

	HttpHeaderType getHeaderType(const std::string& name) {
		NameHeaders::iterator iter = m_name_headers.find(name);
		if (iter == m_name_headers.end()) {
			return HTTP_HEADER_MAX;
		}

		return iter->second;
	}

private:
	HeaderNames m_header_names;
	NameHeaders m_name_headers;
	DefaultValues m_default_values;
};

class HttpReqHeader {
public:
	HttpReqHeader()
	{
		std::string error;
		m_protocol = HttpHeaderData::ins().getDefValue(HTTP_PROTOCOL, error);
		m_connection = HttpHeaderData::ins().getDefValue(HTTP_CONNECTION, error);
		m_accept = HttpHeaderData::ins().getDefValue(HTTP_REQ_ACCEPT, error);
		m_language = HttpHeaderData::ins().getDefValue(HTTP_REQ_LANGUAGE, error);
	}
	
	void setMethod(const HttpMethodType& type, std::string& error) {
		error.clear();
		
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

	std::string getHeaderValue(const HttpHeaderType& header_type) {
		if (header_type < HTTP_METHOD || header_type >= HTTP_HEADER_MAX) {
			//ERROR_DUYE_LOG("input parameter header_type error");
			return "";
		}
		
		return m_header_map[header_type];
	}

	/*
	uint8* error() {
		return m_error.error;
	}
	*/

private:
	bool getPair(const std::string& in_str, std::string& name, std::string& value) {
		std::vector<std::string> split_array;
		StrHelper::split(in_str, ": ", split_array);
		if (split_array.size() != 2) {
			return false;
		}

		name = split_array[0];
		value = split_array[1];

		return true;
	}

	bool setPair(const std::string& name, const std::string& value) {
		HttpHeaderType header_type = HttpHeaderData::ins().getHeaderType(name);
		if (header_type == HTTP_HEADER_MAX) {
			return false;
		}

		m_header_map.insert(std::make_pair(header_type, value));
		return true;
	}

private:
	//Error m_error;
	HeaderMap m_header_map;
};

}
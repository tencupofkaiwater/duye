/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_header.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-18
* @note 
*
* 1. 2016-12-18 duye Created this file
*/
#include <duye_logger.h>
#include <duye_http_header.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.header";

HttpResStatusCode::HttpResStatusCode() {
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_200, "response ok"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_404, "don't found page"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_408, "request timeout"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_413, "response too large"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_503, "service unabled"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_506, "page error, can't parse"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_507, "send request failed"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_508, "request ternination"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_509, "http client don't connect"));
	m_status_code_sesc_map.insert(std::make_pair(HTTP_CODE_510, "http client don't connect"));
}

HttpResStatusCode& HttpResStatusCode::ins() {
	static HttpResStatusCode ins;
	return ins;
}

std::string HttpResStatusCode::getDesc(const HttpResCode& code) {
	if (code < HTTP_CODE_200 || code >= HTTP_CODE_MAX) {
		DUYE_ERROR("HttpResCode error");
		return "";
	}

	return m_status_code_sesc_map[code];
}

HttpMethod::HttpMethod() {
	m_method_names.insert(std::make_pair(HTTP_GET, "get"));
	m_method_names.insert(std::make_pair(HTTP_HEAD, "head"));
	m_method_names.insert(std::make_pair(HTTP_PUT, "put"));
	m_method_names.insert(std::make_pair(HTTP_DELETE, "delete"));
	m_method_names.insert(std::make_pair(HTTP_POST, "post"));
}

HttpMethod& HttpMethod::ins() {
	static HttpMethod ins;
	return ins;
}

std::string HttpMethod::getName(const HttpMethodType& type) {
	if (type < HTTP_GET || type > HTTP_POST) {
		DUYE_ERROR("HttpMethodType error");
		return "";
	}
	
	return m_method_names[type];
}

HttpHeaderData::HttpHeaderData()
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

HttpHeaderData& HttpHeaderData::ins() {
	static HttpHeaderData ins;
	return ins;
}

std::string HttpHeaderData::getName(const HttpHeaderType& type) {
	if (type == HTTP_METHOD || type == HTTP_PROTOCOL || type == HTTP_REQ_URL || type == HTTP_RES_CODE) {
		DUYE_ERROR("HTTP_METHOD, HTTP_PROTOCOL, HTTP_REQ_URL, and HTTP_RES_CODE hasn't name");
		return "";
	}			
	
	if (type < HTTP_METHOD || type > HTTP_HEADER_MAX) {
		DUYE_ERROR("HttpHeaderType error");
		return "";
	}	
	
	return m_header_names[type];
}

std::string HttpHeaderData::getDefValue(const HttpHeaderType& type) {
	DefaultValues::iterator iter = m_default_values.find(type);
	if (iter == m_default_values.end()) {
		DUYE_ERROR("hasn't default value");
		return "";
	}

	return iter->second;
}

HttpHeaderType HttpHeaderData::getHeaderType(const std::string& name) {
	NameHeaders::iterator iter = m_name_headers.find(name);
	if (iter == m_name_headers.end()) {
		return HTTP_HEADER_MAX;
	}

	return iter->second;
}

HttpReqHeader::HttpReqHeader() : m_method(HTTP_GET) {
	init();
}

HttpReqHeader::HttpReqHeader(const HttpMethodType& type, const std::string& url) {
	init();
	setMethod(type);
	setValue(HTTP_REQ_URL, url);
}	

bool HttpReqHeader::setMethod(const HttpMethodType& type) {
	if (type < HTTP_GET || type > HTTP_POST) {
		DUYE_ERROR("type error");
		return false;
	}

	m_method = type;
	return true;
}

bool HttpReqHeader::setValue(const HttpHeaderType& type, const std::string& value) {
	switch (type) {
		case HTTP_METHOD : {
			DUYE_ERROR("HTTP_METHOD setting use setMethod");
			return false;
			break;
		}
		case HTTP_PROTOCOL : {
			DUYE_ERROR("HTTP_PROTOCOL don't need setting");
			return false;
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
		default : DUYE_ERROR("type error"); return false; break;
	}

	return true;
}

void HttpReqHeader::addQueryPara(const std::string& name, const std::string& value) {
	m_querys[name] = value;
}

std::string HttpReqHeader::getValue(const HttpHeaderType& type) {
	switch (type) {
		case HTTP_METHOD : return HttpMethod::ins().getName(m_method);
		case HTTP_PROTOCOL : return m_protocol;
		case HTTP_REQ_URL : return m_url;
		case HTTP_REQ_HOST : return m_host;
		case HTTP_CONNECTION : return m_connection;
		case HTTP_REQ_USER_AGENT : return m_user_agent;
		case HTTP_REQ_ACCEPT : return m_accept;
		case HTTP_REQ_REFERER : return m_referer;
		case HTTP_REQ_ACCEPT_ENCODING : return m_accept_encoding;
		case HTTP_REQ_LANGUAGE : return m_language;
		default : DUYE_ERROR("type error"); break;
	}

	return "";
}

std::string HttpReqHeader::getHeaderString() {
	std::string header_string;	
	if (m_method == HTTP_METHOD_MAX) {
		DUYE_ERROR("HTTP_METHOD is empty");
		return header_string;
	}

	if (m_url.empty()) {
		DUYE_ERROR("HTTP_URL is empty");
		return header_string;
	}

	header_string.append(HttpMethod::ins().getName(m_method));
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
		header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_HOST) + ": " + m_host + "\n");
	if (!m_connection.empty())
		header_string.append(HttpHeaderData::ins().getName(HTTP_CONNECTION) + ": " + m_connection + "\n");	
	if (!m_user_agent.empty())
		header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_USER_AGENT) + ": " + m_user_agent + "\n");		
	if (!m_accept.empty())
		header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_ACCEPT) + ": " + m_accept + "\n");	
	if (!m_referer.empty())
		header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_REFERER) + ": " + m_referer + "\n");	
	if (!m_accept_encoding.empty())
		header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_ACCEPT_ENCODING) + ": " + m_accept_encoding + "\n");	
	if (!m_language.empty())
		header_string.append(HttpHeaderData::ins().getName(HTTP_REQ_LANGUAGE) + ": " + m_language + "\n");

	return header_string;
}

void HttpReqHeader::init() {
	m_protocol = HttpHeaderData::ins().getDefValue(HTTP_PROTOCOL);
	m_connection = HttpHeaderData::ins().getDefValue(HTTP_CONNECTION);
	m_accept = HttpHeaderData::ins().getDefValue(HTTP_REQ_ACCEPT);
	m_language = HttpHeaderData::ins().getDefValue(HTTP_REQ_LANGUAGE);	
}

HttpResHeader::HttpResHeader() {}	
	
HttpResHeader::HttpResHeader(const std::string& header_html) {
	parse(header_html);
}

bool HttpResHeader::parse(const std::string& header_html) {
	std::list<std::string> lineList;
	StrHelper::getLine(header_html, "\r\n", lineList);
	if (lineList.empty()) {
		DUYE_ERROR("http response header error");
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
					DUYE_ERROR("get http protocol error");
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
				DUYE_ERROR("get pair from '%s' error", iter->c_str());
				return false;
			} else {
				if (setPair(name, value)) {
					DUYE_ERROR("set pair name:'%s', value:'%s' error", name.c_str(), value.c_str());
					return false;
				}
			}
		}
	}		
	
	return true;
}

bool HttpResHeader::empty() {
	return m_header_map[HTTP_PROTOCOL].empty();
}

bool HttpResHeader::setHeaderValue(const HttpHeaderType& header_type, const std::string& value) {
	if (header_type < HTTP_METHOD || header_type >= HTTP_HEADER_MAX) {
		DUYE_ERROR("HttpHeaderType error");
		return false;
	}

	m_header_map.insert(std::make_pair(header_type, value));
	return true;
}

std::string HttpResHeader::getHeaderValue(const HttpHeaderType& header_type) {
	if (header_type < HTTP_METHOD || header_type >= HTTP_HEADER_MAX) {
		DUYE_ERROR("HttpHeaderType error");
		return "";
	}
	
	return m_header_map[header_type];
}

bool HttpResHeader::getPair(const std::string& in_str, std::string& name, std::string& value) {
	std::vector<std::string> split_array;
	StrHelper::split(in_str, ": ", split_array);
	if (split_array.size() != 2) {
		DUYE_ERROR("input in_str(%s) error", in_str.c_str());
		return false;
	}

	name = split_array[0];
	value = split_array[1];

	return true;
}

bool HttpResHeader::setPair(const std::string& name, const std::string& value) {
	HttpHeaderType header_type = HttpHeaderData::ins().getHeaderType(name);
	if (header_type == HTTP_HEADER_MAX) {
		DUYE_ERROR("input name(%s) error", name.c_str());
		return false;
	}

	m_header_map.insert(std::make_pair(header_type, value));
	return true;
}

}
/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_req.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/
#include <duye_logger.h>
#include <duye_http_req.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.req";

HttpReq::HttpReq() {
}

HttpReq::HttpReq(const HttpReqHeader& http_header) : m_header(http_header) {
}

HttpReq::~HttpReq() {
}

void HttpReq::setHeader(const HttpReqHeader& http_header) {
	m_header = http_header;
}

bool HttpReq::addJsonPara(const std::string& name, const std::string& value) {
	m_jsons[name] = value;
	return true;
}

/*
Host: www.scala-lang.org

Connection: keep-alive

User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36

Accept: image/webp,image;q=0.8

Referer: http://www.scala-lang.org/download/

Accept-Encoding: gzip, deflate, sdch

Accept-Language: zh-CN,zh;q=0.8
*/
std::string HttpReq::getReqString() {
	std::string req_str = m_header.getHeaderString();
	if (req_str.empty()) {
		DUYE_ERROR("request html header is empty");
		return "";
	}

	if (!m_jsons.empty()) {
		std::string json_data = "{ ";
		ParamPairs::iterator iter = m_jsons.begin();
		for (; iter != m_jsons.end(); ++iter) {
			if (iter != m_jsons.begin()) {
				json_data.append(", ");
			}

			json_data.append("'" + iter->first + "': '" + iter->second + "'");
		}
		json_data.append(" }");
		req_str.append(json_data);
	}
	
	return req_str;
}
}
/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_res.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/
#include <string>
#include <list>
#include <duye_helper.h>
#include <duye_http_res.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.res";

HttpRes::HttpRes() {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

HttpRes::HttpRes(const Buffer& html) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
	parseResHtml(html);
}

HttpRes::~HttpRes() {}

bool HttpRes::parseResHtml(const Buffer& html) {
	return parseRes(html);
}

const HttpResHeader& HttpRes::getHeader() const {
	return m_header;
}

const Buffer& HttpRes::getBody() const {
	return m_org_body;
}

bool HttpRes::getJsonParaValue(const std::string& name, std::string& value) {
	ParamPairs::iterator iter = m_jsons.find(name);
	if (iter == m_jsons.end()) {
		return false;
	}

	value = iter->second;
	return true;
}

const ParamPairs& HttpRes::getJsonParaMap() const {
	return m_jsons;
}

uint8* HttpRes::getError() {
	return m_error.error;
}

/*
HTTP/1.1 200 OK

Date: Fri, 09 Dec 2016 02:37:21 GMT

Server: Apache

Last-Modified: Mon, 25 Jul 2016 09:12:36 GMT

ETag: "6a4-538722f630900"

Accept-Ranges: bytes

Content-Length: 1700

Keep-Alive: timeout=5, max=86

Connection: Keep-Alive

Content-Type: image/png
*/
bool HttpRes::parseRes(const Buffer& html) {
	if (html.empty()) {
		ERROR_DUYE_LOG("http response is empty");
		return false;		
	}
	
	std::string header_html = getHeaderHtml(html);
	if (header_html.empty()) {
		ERROR_DUYE_LOG("http response header is empty");
		return false;		
	}
	
	if (m_header.parse(header_html)) {
		return false;
	}

	if (parseBody()) {
		return false;
	}
	
	return true;
}

bool HttpRes::parseBody() {
	if (m_org_body.empty()) {
		ERROR_DUYE_LOG("http response body is empty");
		return false;
	}	
	
	return true;
}
	
std::string HttpRes::getHeaderHtml(const Buffer& html) {
	int8* end_pos = ByteHelper::findSubBytes(html.data(), html.size(), "\r\n\r\n", sizeof("\r\n\r\n") - 1);
	if (!end_pos) {
		return "";
	}

	uint32 header_len = end_pos - html.data();
	uint32 body_len = html.size() - header_len;

	m_org_body.init(body_len);
	html.copy(m_org_body.data(), m_org_body.size());

	return std::string(html.data(), header_len);
}

}
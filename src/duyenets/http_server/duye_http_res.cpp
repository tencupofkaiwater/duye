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
#include <duye_logger.h>
#include <duye_helper.h>
#include <duye_http_res.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.nets.http.res";

HttpRes::HttpRes() {
}

HttpRes::HttpRes(const Buffer& html) {
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

std::string HttpRes::getJsonParaValue(const std::string& name) {
	ParamPairs::iterator iter = m_jsons.find(name);
	if (iter == m_jsons.end()) {
		return "";
	}

	return iter->second;
}

const ParamPairs& HttpRes::getJsonParaMap() const {
	return m_jsons;
}

void HttpRes::setStatusCode(const HttpResCode& code) {
	switch (code) {
	case HTTP_CODE_200:
		m_header.setHeaderValue(HTTP_RES_CODE, "200");
		break;
	case HTTP_CODE_404:
		m_header.setHeaderValue(HTTP_RES_CODE, "404");
		break;
	case HTTP_CODE_503:
		m_header.setHeaderValue(HTTP_RES_CODE, "503");
		break;
	case HTTP_CODE_506:
		m_header.setHeaderValue(HTTP_RES_CODE, "506");
		break;		
	default:
		break;
	}
}

HttpResCode HttpRes::getStatusCode() {
	std::string code = m_header.getHeaderValue(HTTP_RES_CODE);

	if (code == "200") {
		return HTTP_CODE_200;
	} else if (code == "404") {
		return HTTP_CODE_404;
	} else if (code == "503") {
		return HTTP_CODE_503;
	} else if (code == "506") {
		return HTTP_CODE_506;
	} else {
		return HTTP_CODE_MAX;
	}

	return HTTP_CODE_MAX;
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
		DUYE_ERROR("http response is empty");
		return false;		
	}
	
	std::string header_html = getHeaderHtml(html);
	if (header_html.empty()) {
		DUYE_ERROR("http response header is empty");
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
		DUYE_ERROR("http response body is empty");
		return false;
	}	
	
	return true;
}
	
std::string HttpRes::getHeaderHtml(const Buffer& html) {
	int8* end_pos = ByteHelper::findSubBytes(html.data(), html.size(), "\r\n\r\n", sizeof("\r\n\r\n") - 1);
	if (!end_pos) {
		return "";
	}

	end_pos += (sizeof("\r\n\r\n") - 1);

	uint32 header_len = end_pos - html.data();
	uint32 body_len = html.size() - header_len;

	m_org_body.resize(body_len);
	m_org_body.append(end_pos, body_len);

	return std::string(html.data(), header_len);
}

}
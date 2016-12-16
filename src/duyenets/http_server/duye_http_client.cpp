/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_tcp_client.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/

#include <string>
#include <duye_logger.h>
#include <duye_tcp_client.h>
#include <duye_http_client.h>

#define HTTP_RESPONSE_TEMP_SIZE 10*1024
#define HTTP_RESPONSE_SIZE 1024*1024

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.client";

HttpClient::HttpClient() : m_server_port(0), m_is_connected(false), m_on_msger(NULL) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

HttpClient::HttpClient(const std::string& server_ip, const uint16 server_port) 
	: m_server_ip(server_ip), m_server_port(server_port), m_is_connected(false), m_on_msger(NULL) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

HttpClient::~HttpClient() {}

bool HttpClient::connect()
{
	if (m_server_ip.empty()) {
		DUYE_ERROR("server ip don't setting");
		return false;
	}

	return connect(m_server_ip, m_server_port);
}

bool HttpClient::connect(const std::string& serverIP, const uint16 serverPort)
{   
	m_server_ip = serverIP;
	m_server_port = serverPort;
	
    // millisecond
    const uint32 timeout = 3000;
    if (!m_tcp_client.connect(m_server_ip, m_server_port, timeout))
    {
        DUYE_ERROR("m_tcpClient.connect() failed");
        return false;
    }

    return true;
}

bool HttpClient::disconnect() {
	return m_tcp_client.disconnect();
}

bool HttpClient::request(const HttpReq& req, HttpRes& res) {
	if (!m_is_connected) {
		DUYE_ERROR("HttpClient don't connect");
		res.setStatusCode(HTTP_CODE_507);
	}

	std::string req_content = req.getReqString();
	int64 send_size = m_tcp_client.send(req_content.c_str(), req_content.length());
	if (send_size != req_content.length()) {
		DUYE_ERROR("send data failed");
		res.setStatusCode(HTTP_CODE_408);
	}

	Buffer response(HTTP_RESPONSE_SIZE);
	while (1) {
		int8 temp[HTTP_RESPONSE_TEMP_SIZE] = {0};
		int64 recv_size = m_tcp_client.recv(temp, HTTP_RESPONSE_TEMP_SIZE);
		if (recv_size < 0) {
			break;
		}

		if (response.append(temp, recv_size)) {
			DUYE_ERROR("Buffer::append() failed:%s", response.error());
			res.setStatusCode(HTTP_CODE_413);
			break;
		}
	}

	if (response.size() > 0) {
		if (!res.parseResHtml(response)) {
			DUYE_ERROR("http response format is error");
			res.setStatusCode(HTTP_CODE_506);
		}
	} else {
		DUYE_ERROR("received response is empty");
		res.setStatusCode(HTTP_CODE_404);
	}
	
	return true;
}

bool HttpClient::request(const HttpReq& req, const HttpClientIf* onMsger) {
	HttpRes res;
	if (request(req, res)) {
		if (onMsger) {
			return onMsger->onMsg(res);
		}
	}
	
	return false;
}

const std::string& HttpClient::getServerIP() {
	return m_server_ip;
}

uint16 HttpClient::getServerPort() {
	return m_server_port;
}

void HttpClient::regist(const HttpClientIf* onMsger) {
	m_on_msger = onMsger;
}

}

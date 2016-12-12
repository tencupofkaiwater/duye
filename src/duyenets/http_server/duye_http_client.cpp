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

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.client";

HttpClient::HttpClient() : m_server_port(0), m_is_connected(false) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

HttpClient::HttpClient(const std::string& server_ip, const uint16 server_port) 
	: m_server_ip(server_ip), m_server_port(server_port), m_is_connected(false) {
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

HttpClient::~HttpClient() {}

bool HttpClient::connect()
{
	if (m_server_ip.empty()) {
		ERROR_DUYE_LOG("server ip don't setting");
		return false;
	}

	return connect(m_server_ip, m_server_port);
}

bool HttpClient::connect(const std::string& serverIP, const uint16 serverPort)
{   
	m_server_ip = serverIP;
	m_server_port = serverPort;
	
    // millisecond
    const uint32 timeout = 10000;
    if (!m_tcp_client.connect(m_server_ip, m_server_port, timeout))
    {
        ERROR_DUYE_LOG("m_tcpClient.connect() failed");
        return false;
    }

    return true;
}

bool HttpClient::request(const HttpReq& req, HttpRes& res, const bool is_block) {
	if (!m_is_connected) {
		if (!connect(m_server_ip, m_server_port)) {
			return false;
		}
	}

	m_is_connected = true;

	return true;
}

uint8* HttpClient::getError() {
	return m_error.error;
}

}

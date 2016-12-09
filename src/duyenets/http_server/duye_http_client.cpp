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

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.client";

HttpClient::HttpClient() : m_server_port(0), m_is_connected(false) {}
HttpClient::HttpClient(const std::string& server_ip, const uint16 server_port) 
	: m_server_ip(server_ip), m_server_port(server_port), m_is_connected(false) {}
HttpClient::~HttpClient() {}

void HttpClient::setServer(const std::string& server_ip, const uint16 server_port) {
	m_server_ip = server_ip;
	m_server_port = server_port;
}

bool HttpClient::request(const HttpReq& req, HttpRes& res, const bool is_block) {
    // millisecond
    const uint32 timeout = 10000;
	if (!m_is_connected) {
	    if (!m_tcp_client.connect(server_ip, server_port, timeout))
	    {
	        ERROR_DUYE_LOG("m_tcpClient.connect() failed");
	        return false;
	    }
	}

	m_is_connected = true;

	return true;
}

bool HttpClient::connect(const std::string& serverIP, const uint16 serverPort)
{   
    // millisecond
    const uint32 timeout = 10000;
    if (!m_tcpClient.connect(serverIP, serverPort, timeout))
    {
        ERROR_DUYE_LOG("m_tcpClient.connect() failed");
        return false;
    }

    return true;
}

uint8* HttpClient::getError() {
	return m_error.error;
}

}

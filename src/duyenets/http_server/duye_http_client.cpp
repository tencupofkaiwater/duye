/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_client.cpp
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
#include <duye_sys.h>
#include <duye_tcp_client.h>
#include <duye_http_client.h>

#define HTTP_RESPONSE_TEMP_SIZE 10*1024
#define HTTP_RESPONSE_SIZE 1024*1024

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duyenets.http.client";

HttpClient::HttpClient() : m_server_port(80), m_exit_thread(false), m_ud(NULL) {
}

HttpClient::HttpClient(const std::string& server_ip, const uint16 server_port) 
	: m_server_ip(server_ip), m_server_port(server_port), m_exit_thread(false), m_ud(NULL) {
}

HttpClient::~HttpClient() {
	disconnect();
}

bool HttpClient::setServer(const std::string& server_ip, const uint16 server_port) {
	m_server_ip = server_ip;
	m_server_port = server_port;
}

bool HttpClient::get(const std::string& url, HttpRes& res, const uint32 timeout) {
	if (!connect(timeout / 2)) {
		res.setStatusCode(HTTP_CODE_510);
		return false;
	}
	
	bool ret = request(HTTP_GET, url, res, timeout / 2);
	disconnect();
	return ret;
}

bool HttpClient::post(const std::string& url, HttpRes& res, const uint32 timeout) {
	if (!connect(timeout / 2)) {
		res.setStatusCode(HTTP_CODE_510);
		return false;
	}
	
	bool ret = request(HTTP_POST, url, res, timeout / 2);
	disconnect();
	return ret;
}

const std::string& HttpClient::getServerIP() {
	return m_server_ip;
}

uint16 HttpClient::getServerPort() {
	return m_server_port;
}

bool HttpClient::run() {
	for (;;) {
		m_to_req_cond.wait();

		m_ud_mutex.lock();
		if (!m_ud) {
			m_ud_mutex.unlock();
			continue;
		}
		
		std::string req_content = m_ud->http_req->getReqString();
		m_ud_mutex.unlock();

		HttpResCode code = HTTP_CODE_MAX;
		Buffer response(HTTP_RESPONSE_SIZE);
		
		int64 send_size = m_tcp_client.send(req_content.c_str(), req_content.length());
		if (send_size != req_content.length()) {
			DUYE_ERROR("send data failed");
			code = HTTP_CODE_507;
		} else {			
			while (1) {
				if (!m_ud) {
					DUYE_ERROR("request ternination");
					code = HTTP_CODE_508;
					break;
				}
				
				int8 temp[HTTP_RESPONSE_TEMP_SIZE] = {0};
				int64 recv_size = m_tcp_client.recv(temp, HTTP_RESPONSE_TEMP_SIZE);
				if (recv_size < 0) {
					DUYE_DEBUG("receied data finished, received data size = %d", response.size());
					break;
				}

				if (response.append(temp, recv_size)) {
					DUYE_ERROR("Buffer::append() failed:%s", response.error());
					code = HTTP_CODE_413;
					break;
				}
			}			
		}

		m_ud_mutex.lock();
		if (m_ud) {
			if (code != HTTP_CODE_MAX) {
				m_ud->http_res->setStatusCode(code);
			} else {		
				if (response.size() > 0) {
					if (!m_ud->http_res->parseResHtml(response)) {
						DUYE_ERROR("http response format is error");
						m_ud->http_res->setStatusCode(HTTP_CODE_506);
					}
				} else {
					DUYE_ERROR("received response is empty");
					m_ud->http_res->setStatusCode(HTTP_CODE_503);
				}
			}

			m_ud = NULL;
			m_res_notify_cond.signal();
		}		
		m_ud_mutex.unlock();
	}
}

bool HttpClient::connect(const uint32 timeout)
{   
	if (m_tcp_client.isCon()) {
		return true;
	}

	if (m_server_ip.empty()) {
		DUYE_ERROR("server ip is empty");
		return false;
	}
	
    if (!m_tcp_client.connect(m_server_ip, m_server_port, timeout))
    {
        DUYE_ERROR("connect to server:%s:%d timeout", m_server_ip.c_str(), m_server_port);
        return false;
    }

    return true;
}

bool HttpClient::disconnect() {
	return m_tcp_client.disconnect();
}

bool HttpClient::request(const HttpMethodType& type, const std::string& url, HttpRes& res, const uint32 timeout) {
	if (!m_tcp_client.isCon()) {
		DUYE_ERROR("HttpClient don't connect");
		res.setStatusCode(HTTP_CODE_509);
		return false;
	}

	duye::AutoLock lock(m_req_mutex);
	HttpReq req(HttpReqHeader(type, url));
	
	HttpUserData ud(&req, &res);
	HttpUserData* m_ud = &ud;
	m_to_req_cond.signal();
	
	if (!m_res_notify_cond.wait(timeout)) {
		m_ud_mutex.lock();
		m_ud = NULL;
		m_ud_mutex.unlock();
		res.setStatusCode(HTTP_CODE_408);
		return false;
	}
	
	return true;	
}

}

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

static const int8* DUYE_LOG_PREFIX = "duye.nets.http.client";

HttpUserData::HttpUserData(HttpReq* req, HttpRes* res) : http_req(req), http_res(res) {} 

HttpClient::HttpClient() : m_server_port(80), m_exit_thread(false), m_ud(NULL) {
	startTask();
}

HttpClient::HttpClient(const std::string& server_ip, const uint16 server_port) 
	: m_server_ip(server_ip), m_server_port(server_port), m_exit_thread(false), m_ud(NULL) {
	startTask();
}

HttpClient::~HttpClient() {
	disconnect();
}

void HttpClient::setServer(const std::string& server_ip, const uint16 server_port) {
	m_server_ip = server_ip;
	m_server_port = server_port;
}

bool HttpClient::get(const HttpUrl& url, HttpRes& res, const uint32 timeout) {
	HttpReqHeader header(HTTP_GET, url.getUrl());	
	return get(header, res, timeout);
}

bool HttpClient::get(const HttpReqHeader& header, HttpRes& res, const uint32 timeout) {
	if (!connect(0)) {
		res.setStatusCode(HTTP_CODE_510);
		return false;
	}
	
	HttpReq req(header);
	bool ret = request(req, res, timeout);
	
	disconnect();
	return ret;
}

bool HttpClient::post(const HttpUrl& url, HttpRes& res, const uint32 timeout) {
	HttpReqHeader header(HTTP_POST, url.getUrl());
	return post(header, res, timeout);
}

bool HttpClient::post(const HttpReqHeader& header, HttpRes& res, const uint32 timeout) {
	if (!connect(timeout / 2)) {
		res.setStatusCode(HTTP_CODE_510);
		return false;
	}
	
	HttpReq req(header);
	bool ret = request(req, res, timeout / 2);
	
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
	DUYE_DEBUG("HttpClient Thread:%u start", threadId());
	
	for (;;) {
		m_to_req_cond.wait();
		m_ud_mutex.lock();
		if (!m_ud) {
			m_ud_mutex.unlock();
			continue;
		}
		
		std::string req_content = m_ud->http_req->getReqString();
		DUYE_INFO("\n%s", req_content.c_str());
		m_ud_mutex.unlock();

		HttpResCode code = HTTP_CODE_MAX;
		Buffer response(HTTP_RESPONSE_SIZE);
		
		int64 send_size = m_tcp_client.send(req_content.c_str(), req_content.length());
		if (send_size != (int64)req_content.length()) {
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

	DUYE_DEBUG("HttpClient Thread:%u end", threadId());

	return true;
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

bool HttpClient::request(const HttpReq& req, HttpRes& res, const uint32 timeout) {
	DUYE_DEBUG("IN %s", __FUNCTION__);
	
	if (!m_tcp_client.isCon()) {
		DUYE_ERROR("HttpClient don't connect");
		res.setStatusCode(HTTP_CODE_509);
		DUYE_INFO("OUT %s", __FUNCTION__);
		return false;
	}

	duye::AutoLock lock(m_req_mutex);	
	HttpUserData ud((HttpReq*)&req, &res);
	m_ud = &ud;
	m_to_req_cond.signal();

	DUYE_DEBUG("request timeout : %d", timeout);
	if (!m_res_notify_cond.wait(timeout)) {
		m_ud_mutex.lock();
		m_ud = NULL;
		m_ud_mutex.unlock();
		res.setStatusCode(HTTP_CODE_408);
		DUYE_ERROR("HttpClient request timeout");
		DUYE_INFO("OUT %s", __FUNCTION__);
		return false;
	}

	DUYE_DEBUG("OUT %s", __FUNCTION__);
	
	return true;
}

}

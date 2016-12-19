/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_client.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/

#pragma once

#include <string>
#include <duye_type.h>
#include <duye_tcp_client.h>
#include <duye_http_url.h>
#include <duye_http_req.h>
#include <duye_http_res.h>

namespace duye {

class HttpUserData {
public:
	explicit HttpUserData(HttpReq* req, HttpRes* res);

	HttpReq* http_req;
	HttpRes* http_res;
};

/**
 * @brief http client
 */
class HttpClient : public duye::ThreadTask {
public:
    HttpClient();
	HttpClient(const std::string& server_ip, const uint16 server_port = 80);
    ~HttpClient();

	void setServer(const std::string& server_ip, const uint16 server_port = 80);

    /**
     * @brief http request.
     * @param [in] req : http request.
     * @param [out] res : http response.
     * @param [in] timeout : http request timeout, default is 3000 millisecond 
     * @return : true/false
     */
    bool get(const HttpUrl& url, HttpRes& res, const uint32 timeout = 3000);
	bool post(const HttpUrl& url, HttpRes& res, const uint32 timeout = 3000);

	const std::string& getServerIP();
	uint16 getServerPort();

private:
	// implementation from duye::ThreadTask
	virtual bool run();
	bool connect(const uint32 timeout);
	bool disconnect();
	bool request(const HttpMethodType& type, const HttpUrl& url, HttpRes& res, const uint32 timeout);

private:
    duye::TcpClient m_tcp_client;
    std::string m_server_ip;
    uint16 m_server_port;
	duye::Mutex m_req_mutex;
	duye::Mutex m_ud_mutex;
	bool m_exit_thread;
	duye::Condition m_to_req_cond;
	duye::Condition m_res_notify_cond;
	HttpUserData* m_ud;
};

}

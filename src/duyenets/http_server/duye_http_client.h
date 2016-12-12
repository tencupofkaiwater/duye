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
#include <duye_http_req.h>
#include <duye_http_res.h>

namespace duye {

/**
 * @brief http client
 */
class HttpClient
{
public:
    HttpClient();
	HttpClient(const std::string& server_ip, const uint16 server_port = 80);
    ~HttpClient();

	/**
	 * @brief set server address and port
	 * @return error description.
	 */
	bool connect();
	bool connect(const std::string& server_ip, const uint16 server_port = 80);

    /**
     * @brief http request.
     * @param [in] req : http request.
     * @param [out] res : http response.
     * @param [in] is_block : request mode, default is block.
     * @return : true/false
     */
    bool request(const HttpReq& req, HttpRes& res, const bool is_block = true);

	/**
	 * @brief get error description.
	 * @return error description.
	 */
	uint8* getError();

private:
	Error 		m_error;
    TcpClient  	m_tcp_client;
    std::string m_server_ip;
    uint16      m_server_port;
    bool        m_is_connected;	
};
}

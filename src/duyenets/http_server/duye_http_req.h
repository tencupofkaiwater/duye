/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_req.h
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
#include <map>
#include <duye_type.h>
#include <duye_sys.h>
#include <duye_http_type.h>

namespace duye {

class HttpReq {
public:
	HttpReq();
	HttpReq(const HttpReqHeader& http_header);
	~HttpReq();

	void setHeader(const HttpReqHeader& http_header);
	bool addJsonPara(const std::string& name, const std::string& value);
	std::string getReqString(std::string& error);
	uint8* error();

private:
	Error m_error;
	HttpReqHeader m_header;
	ParamPairs m_jsons;
};
}
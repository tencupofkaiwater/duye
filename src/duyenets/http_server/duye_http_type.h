/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_http_type.h
* @version     
* @brief      
* @author   duye
* @date	    2016-12-8
* @note 
*
* 1. 2016-12-8 duye Created this file
*/

#pragma once

#include <duye_type.h>
#include <duye_helper.h>

namespace duye {

enum HttpResCode {
	// response ok
	HTTP_CODE_200 = 200,
	// don't found page
	HTTP_CODE_404 = 404,
	// request timeout
	HTTP_CODE_408 = 408,
	// response too large
	HTTP_CODE_413 = 413,
	// service unabled
	HTTP_CODE_503 = 503,
	// page error, can't parse
	HTTP_CODE_506 = 506,	
	// send request failed
	HTTP_CODE_507 = 507,	
	// request ternination
	HTTP_CODE_508 = 508,	
	// http client don't connect
	HTTP_CODE_509 = 509,	
	// connect to server timeout
	HTTP_CODE_510 = 510,	
	// nothing
	HTTP_CODE_MAX
};

enum HttpMethodType {
	HTTP_GET,
	HTTP_HEAD,
	HTTP_PUT,
	HTTP_DELETE,
	HTTP_POST,
	HTTP_METHOD_MAX
};

enum HttpParaType {
	HTTP_QUERY,
	HTTP_JSON,
	HTTP_PARA_MAX
};

enum HttpHeaderType {
	// common type
	HTTP_METHOD,
	HTTP_PROTOCOL,
	HTTP_CONNECTION,

	// request type
	HTTP_REQ_URL,
	HTTP_REQ_HOST,
	HTTP_REQ_USER_AGENT,
	HTTP_REQ_ACCEPT,
	HTTP_REQ_REFERER,
	HTTP_REQ_ACCEPT_ENCODING,	
	HTTP_REQ_LANGUAGE,	
	
	// response type
	HTTP_RES_CODE,
	HTTP_RES_CODE_DESC,
	HTTP_RES_DATE,
	HTTP_RES_SERVER,
	HTTP_RES_LAST_MODIFIED,
	HTTP_RES_ETAG,
	HTTP_RES_ACCEPT_RANGES,
	HTTP_RES_CONTENT_LENGTH,
	HTTP_RES_KEEP_ALIVE,
	HTTP_RES_CONTENT_TYPE,
	
	HTTP_HEADER_MAX
};

}
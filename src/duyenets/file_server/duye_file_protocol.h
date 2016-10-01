/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_protocol.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-01
* @note 
*
* 1. 2016-04-01 duye Created this file
*/

#pragma once

#include <list>
#include <string>
#include <duye_type.h>

/*
=====================get file message xml format===================================
-------CLI_GET_FILE_REQ format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="client" type="file_cli_get_req" version="1.0">
    <file>
        <path>file_path</path>
    </file>
    <file>
        <path>file_path</path>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

-------SER_GET_FILE_RESP format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="server" type="file_ser_get_resp" version="1.0">
    <file>
        <path>file_path</path>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

-------SER_GET_FILE_COMPLE format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="server" type="get_file_comple" version="1.0">
    <file>
        <path>file_path</path>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>
=====================put file message format===================================
-------CLI_GET_FILE_REQ format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="client" type="file_cli_put_req" version="1.0">
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

-------SER_PUT_FILE_RESP format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="client" type="file_ser_put_resp" version="1.0">
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

-------CLI_PUT_FILE_COMPLE format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="client" type="file_cli_put_comple" version="1.0">
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

=====================put/get file suspend/cancel message format===================================
-------CLI_TRANSFER_SUSPEND format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="client" type="file_cli_tran_suspend" version="1.0">
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

-------CLI_TRANSFER_CANCEL format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="client" type="file_cli_tran_cancel" version="1.0">
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
    <file>
        <name>file_name</name>
        <size>file_size</size>
        <type>file_type</type>
        <md5>file_md5</md5>
    </file>
        *
        *
    <file>
    </file>
</duye_file_msg>

=====================server error response format===================================
-------SER_ERROR format:
<?xml version="1.0" encoding="utf-8"?>
<duye_file_msg from="server" type="file_ser_error" version="1.0">
    <error_id>error ID</error_id>
    <error_desp>error description</desp>
</duye_file_msg>

*/

#define FILE_E_BASE 200

namespace duye {

/**
 * @brief file transfer client message type
 */
typedef enum
{
    // get file request, in xml name "file_cli_get_req"
    FILE_CLI_GET_REQ,
    // put file request, in xml name "file_cli_put_req"
    FILE_CLI_PUT_REQ,
    // put file completly, in xml name "file_cli_put_comple"
    FILE_CLI_PUT_COMPLE,
    // transfer suspend, in xml name "file_cli_tran_suspend"
    FILE_CLI_TRANSFER_SUSPEND,
    // transfer cancel, in xml name "file_cli_tran_cancel"
    FILE_CLI_TRANSFER_CANCEL,
    // unknown message type
    FILE_CLI_UNKNOWN
} FileClientMsgType;

/**
 * @brief file transfer server message type
 */
typedef enum
{
    // get file request, in xml name "file_ser_get_resp"
    FILE_SER_GET_RESP,
    // put file request, in xml name "file_ser_put_resp"
    FILE_SER_PUT_RESP,    
    // get file completly, in xml name "file_ser_get_comple"
    FILE_SER_GET_COMPLE,
    // interal error, in xml name "file_ser_error"
    FILE_SER_ERROR,
    // unknown message type
    FILE_SER_UNKNOWN 
} FileServerMsgType;

/**
 * @brief file transfer server message type
 */
typedef enum
{
    // file message format wrong
    FILE_E_FORMAT = FILE_E_BASE,
    // file message parameter wrong
    FILE_E_PARA,
    // file message version wrong
    FILE_E_VERSION,    
    // file error max number
    FILE_E_MAX
} FileServerErrorType;

// file path list
typedef std::list<std::string> FilePathList;

/**
 * @brief network file server parameters
 */
class FileProtocolParser
{
public:
    /**
     * @brief verify client protocol
     * @param [in] clientMsg : client message
     * @param [in] msgLen : message length
     * @param [out] errorID : error ID
     * @return : true/false
     */
    static bool verifyClientProtocol(const int8* clientMsg, const uint32 msgLen, uint32& errorID);

    /**
     * @brief parser client message type
     * @param [in] clientMsg : client message
     * @param [in] msgLen : message length
     * @return : client message type
     */
    static FileClientMsgType getClientMsgType(const int8* clientMsg, const uint32 msgLen);

    /**
     * @brief parser client message type
     * @param [in] clientMsg : client message
     * @param [in] msgLen : message length
     * @param [out] filePathList : output file path list
     * @return : true/false
     */
    static bool parserClientGetReqMsg(const int8* clientMsg, const uint32 msgLen, FilePathList& filePathList);

    /**
     * @brief parser client message type
     * @param [in] errorID : error ID
     * @param [out] outXmlMsg : output xml format
     * @return true/false
     */
    static bool formatServerErrorRespMsg(const uint32 errorID, std::string& outXmlMsg);    
};

}

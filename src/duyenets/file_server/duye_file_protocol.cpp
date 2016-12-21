/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_file_protocol.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-01
* @note 
*
* 1. 2016-04-01 duye Created this file
*/

#include <duye_logger.h>
#include <duye_xml.h>
#include <duye_helper.h>
#include <duye_file_protocol.h>

static const int8* DUYE_LOG_PREFIX = "duye.nets.file.protocol";

namespace duye {

// current protocol version
static const int8* FILE_TRAN_PROTOCOL_VERSION = "1.0";

typedef struct
{
    uint32      errorID;
    const char* errorDesp;
} FileServerError;

static const FileServerError FileErrorArray[FILE_E_MAX] {
    {FILE_E_FORMAT, "file message format wrong"},
    {FILE_E_PARA, "file message parameter wrong"},
    {FILE_E_VERSION, "file message version wrong"}
};
    
bool FileProtocolParser::verifyClientProtocol(const int8* clientMsg, const uint32 msgLen, uint32& errorID)
{
    FileClientMsgType msgType = FILE_CLI_UNKNOWN;
    if (clientMsg == NULL || msgLen == 0)
        return msgType;

    XmlDocument doc;
    if (doc.parse(clientMsg) == NULL)
    {
        DUYE_ERROR("doc.parse() failed");
        errorID = FILE_E_FORMAT;
        return msgType;
    }

    XmlElement* rootElement = doc.rootElement();
    if (rootElement == NULL)
    {
        DUYE_ERROR("rootElement == NULL");
        errorID = FILE_E_FORMAT;
        return msgType;
    }

    if (rootElement->valueStr() != "duye_file_msg")
    {
        DUYE_ERROR("rootElement->valueStr() != \"duye_file_msg\"");
        errorID = FILE_E_FORMAT;
        return msgType;
    }       

    std::string msgFromStr(rootElement->attribute("from"));
    std::string msgTypeStr(rootElement->attribute("type"));
    std::string msgVersionStr(rootElement->attribute("version"));
    if (msgFromStr != "client")
    {
        DUYE_ERROR("client message attribute from = '%s', don't exist this value", msgFromStr.c_str());
        errorID = FILE_E_PARA;
        return false;
    }
       
    if (!(msgTypeStr == "get_file_req" || 
        msgTypeStr == "put_file_req" || 
        msgTypeStr == "put_file_comple" ||
        msgTypeStr == "transfer_suspend" ||
        msgTypeStr == "transfer_cancel"))
    {
        DUYE_ERROR("don't have message type = '%s'", msgTypeStr.c_str());
        errorID = FILE_E_PARA;
        return false;
    }

    if (msgVersionStr != FILE_TRAN_PROTOCOL_VERSION)
    {
        DUYE_ERROR("current transfer protocol version is %s, message version is %s", 
            FILE_TRAN_PROTOCOL_VERSION, msgVersionStr.c_str());
        errorID = FILE_E_VERSION;
        return false;
    }    
    
    return true;
}

FileClientMsgType FileProtocolParser::getClientMsgType(const int8* clientMsg, const uint32 msgLen)
{
    FileClientMsgType msgType = FILE_CLI_UNKNOWN;
    if (clientMsg == NULL || msgLen == 0)
        return msgType;

    XmlDocument doc;
    if (doc.parse(clientMsg) == NULL)
    {
        DUYE_ERROR("doc.parse() failed");
        return msgType;
    }

    // <duye_file_transfer> node
    XmlElement* rootElement = doc.rootElement();
    if (rootElement == NULL)
    {
        DUYE_ERROR("rootElement == NULL");
        return msgType;
    }

    if (rootElement->valueStr() != "duye_file_transfer")
    {
        DUYE_ERROR("rootElement->valueStr() != \"duye_file_transfer\"");
        return msgType;
    }       

    const int8* msgTypeCStr = rootElement->attribute("type");
    if (msgTypeCStr == NULL)
    {
        DUYE_ERROR("msgType == NULL");
        return msgType;
    }

    std::string msgTypeStr(msgTypeCStr);
    if (msgTypeStr == "file_cli_put_req")
        return FILE_CLI_GET_REQ;
    else if (msgTypeStr == "file_cli_put_comple")
        return FILE_CLI_PUT_REQ;
    else if (msgTypeStr == "put_file_comple")
        return FILE_CLI_PUT_COMPLE;
    else if (msgTypeStr == "file_cli_tran_suspend")
        return FILE_CLI_TRANSFER_SUSPEND;    
    else if (msgTypeStr == "file_cli_tran_cancel")
        return FILE_CLI_TRANSFER_CANCEL;  
    else
        return msgType;
    
    return msgType;
}

bool FileProtocolParser::parserClientGetReqMsg(const int8* clientMsg, const uint32 msgLen, FilePathList& filePathList)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;

    XmlDocument doc;
    if (doc.parse(clientMsg) == NULL)
    {
        DUYE_ERROR("doc.parse() failed");
        return false;
    }   

    XmlElement* rootElement = doc.rootElement();
    if (rootElement == NULL)
    {
        DUYE_ERROR("rootElement == NULL");
        return false;
    }
    
    // first <file> node
    XmlElement* fileElement = rootElement->firstChildElement();
    // loop file node
    for (; fileElement != NULL; fileElement = fileElement->nextSiblingElement())
    {
        XmlElement* pathElement = fileElement->firstChildElement();
        if (pathElement == NULL)
            return false;

        if (pathElement->valueStr() != "path")
            return false;

        const int8* path = pathElement->getText();
        if (path == NULL)
            return false;

         filePathList.push_back(path);
    }
    
    return true;
}

bool FileProtocolParser::formatServerErrorRespMsg(const uint32 errorID, std::string& outXmlMsg)
{
    if (errorID >= FILE_E_MAX)
        return false;

    const FileServerError& error = FileErrorArray[errorID];       
	XmlDocument doc;  
	XmlDeclaration* decl = new XmlDeclaration("1.0", "utf-8", ""); 
	XmlElement* rootElement = new XmlElement("duye_file_msg");  
    rootElement->setAttribute("from", "server");
    rootElement->setAttribute("type", "server_error");
    rootElement->setAttribute("version", FILE_TRAN_PROTOCOL_VERSION);
    
	XmlElement* errorIDElement = new XmlElement("error_id");  
	errorIDElement->linkEndChild(new XmlText(StrHelper::toStr(error.errorID)));

	XmlElement* errorDespElement = new XmlElement("error_desp");  
	errorDespElement->linkEndChild(new XmlText(error.errorDesp));   

    rootElement->linkEndChild(errorIDElement);
    rootElement->linkEndChild(errorDespElement);

	doc.linkEndChild(decl);  
	doc.linkEndChild(rootElement);   

    doc.xmlToStr(outXmlMsg);
    if (outXmlMsg.empty())
    {
        DUYE_ERROR("doc.xmlToStr()");
        return false;
    }
    
    return true;
}

}

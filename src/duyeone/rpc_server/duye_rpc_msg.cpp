/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_rpc_msg.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-11
* @note 
*
* 1. 2016-04-11 duye Created this file
*/
#include <string.h>
#include <duye_logger.h>
#include <duye_xml.h>
#include <duye_helper.h>
#include <duye_rpc_msg.h>

static const int8* DUYE_LOG_PREFIX = "duyeone.rpc.msg";

namespace duye {

// current protocol version
//static const int8* RPC_MSG_VERSION = "1.0";

typedef struct
{
    uint32      errorID;
    const char* errorDesp;
} RpcServerError;

static const RpcServerError RpcErrorArray[RPC_E_MAX - RPC_E_BASE] {
    {RPC_E_FORMAT, "rpc message format wrong"},
    {RPC_E_PARA, "rpc message parameter wrong"},
    {RPC_E_VERSION, "rpc message version wrong"}
};
    
bool RpcMsgParser::formatReqMsg(const int8* clientMsg, const uint32 msgLen, RpcReqMsg& rpcReqMsg, uint32& errorID)
{
    if (clientMsg == NULL || msgLen == 0)
        return false;

    XmlDocument xmlDoc;
    if (xmlDoc.parse(clientMsg, 0, XML_ENCODING_UTF8))
    {
        DUYE_ERROR("doc.parse() failed:%s", xmlDoc.errorDesc());
        errorID = RPC_E_FORMAT;
        return false;
    }

    XmlElement* rootElement = xmlDoc.rootElement();
    if (rootElement == NULL)
    {
        DUYE_ERROR("rootElement == NULL");
        errorID = RPC_E_FORMAT;
        return false;
    }

    if (rootElement->valueStr() != "duye_rpc_msg")
    {
        DUYE_ERROR("rootElement->valueStr() != \"duye_rpc_msg\"");
        errorID = RPC_E_PARA;
        return false;
    }       

    const char* tmpPtr = rootElement->attribute("where");
    if (tmpPtr == NULL)
    {
        DUYE_ERROR("client message attribute where = NULL");
        errorID = RPC_E_PARA;
        return false;        
    }

    std::string where = tmpPtr;
    if (where != "client")
    {
        DUYE_ERROR("client message attribute from = '%s', don't exist this value", where.c_str());
        errorID = RPC_E_PARA;
        return false;
    }

    tmpPtr = rootElement->attribute("fun_name");
    if (tmpPtr == NULL)
    {
        DUYE_ERROR("client message attribute fun_name = NULL");
        errorID = RPC_E_PARA;
        return false;        
    }

    RpcFun& rpcFun = rpcReqMsg.rpcFun;
    rpcFun.name.assign(tmpPtr);
    if (rpcFun.name.empty())
    {
        DUYE_ERROR("client message attribute fun_name = empty");
        errorID = RPC_E_PARA;
        return false;
    }    

    XmlElement* funAttrElement = rootElement->firstChildElement();
    for (; funAttrElement != NULL; funAttrElement = funAttrElement->nextSiblingElement())
    {
        RpcFunPara para;
        if (funAttrElement->valueStr() == "parameter")
        {
            RpcFunPara para;
            tmpPtr = funAttrElement->attribute("type");
            if (tmpPtr == NULL)
            {
                errorID = RPC_E_FORMAT;
                return false;
            }
            para.type.assign(tmpPtr);
            if (!(para.type == "bool" || para.type == "int" || para.type == "uint" || para.type == "string"))
            {
                DUYE_ERROR("request xml format error");
                errorID = RPC_E_FORMAT;
            }            
            
            tmpPtr = funAttrElement->attribute("name");
            if (tmpPtr == NULL)
            {
                errorID = RPC_E_FORMAT;
                return false;
            }        
            para.name.assign(tmpPtr);
            para.from.assign("input");
            tmpPtr = funAttrElement->getText();
            if (tmpPtr == NULL)
            {
                errorID = RPC_E_FORMAT;
                return false;
            }      
            
            para.val.setVal(tmpPtr, para.type);
            rpcFun.inParaMap.insert(std::make_pair(para.name, para));
            DUYE_TRACE("para.name=%s value=%s", para.name.c_str(), para.val.getVal().c_str());
        }
        else
        {
            DUYE_ERROR("request xml format error");
            errorID = RPC_E_FORMAT;
        }        
    }    
    
    return true;
}

bool RpcMsgParser::formatRespErrorMsg(const uint32 errorID, std::string& outXmlMsg)
{
    if (errorID >= RPC_E_MAX)
        return false;

    const RpcServerError& error = RpcErrorArray[errorID - RPC_E_BASE];            
	XmlDocument doc;  
	XmlDeclaration* decl = new XmlDeclaration("1.0", "utf-8", ""); 
	XmlElement* rootElement = new XmlElement("duye_rpc_msg");  
    rootElement->setAttribute("where", "server");
    rootElement->setAttribute("fun_name", "server_error");
    
	XmlElement* errorIDElement = new XmlElement("parameter");  
    errorIDElement->setAttribute("type", "uint");
    errorIDElement->setAttribute("name", "error_id");
	errorIDElement->linkEndChild(new XmlText(StrHelper::toStr(error.errorID)));
    DUYE_DEBUG("errorID = %s", StrHelper::toStr(error.errorID).c_str());

	XmlElement* errorDespElement = new XmlElement("parameter");  
    errorDespElement->setAttribute("type", "string");
    errorDespElement->setAttribute("name", "error_desp");
	errorDespElement->linkEndChild(new XmlText(error.errorDesp));   
    DUYE_DEBUG("errorDesp = %s", error.errorDesp);

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

bool RpcMsgParser::formatRespMsg(RpcReqMsg& reqMsg, std::string& outXmlMsg)
{
    RpcFun& rpcFun = reqMsg.rpcFun;
    
	XmlDeclaration* decl = new XmlDeclaration("1.0", "utf-8", ""); 
	XmlElement* rootElement = new XmlElement("duye_rpc_msg");  
    rootElement->setAttribute("where", "server");
    rootElement->setAttribute("fun_name", rpcFun.name);

    RpcFunParaMap::iterator iter = rpcFun.outParaMap.begin();
    for (; iter != rpcFun.outParaMap.end(); ++iter)
    {
    	XmlElement* parameterElement = new XmlElement("parameter");  
        parameterElement->setAttribute("type", iter->second.type);
        parameterElement->setAttribute("name", iter->first);
    	parameterElement->linkEndChild(new XmlText(iter->second.val.getVal()));
        rootElement->linkEndChild(parameterElement);
    }

    XmlDocument xmlDoc;
    xmlDoc.linkEndChild(decl); 
	xmlDoc.linkEndChild(rootElement);

    xmlDoc.xmlToStr(outXmlMsg);
    if (outXmlMsg.empty())
    {
        DUYE_ERROR("doc.xmlToStr()");
        return false;
    }
        
    return true;

}

}

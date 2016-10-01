/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_rpc_msg.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-11
* @note 
*
* 1. 2016-04-11 duye Created this file
*/

#pragma once

#include <list>
#include <string>
#include <map>
#include <duye_type.h>
#include <duye_helper.h>
#include <duye_xml.h>

/*
=====================get file message xml format===================================
-------CLI_GET_FILE_REQ format:
type=(bool, int, uint, string)

<?xml version="1.0" encoding="utf-8"?>
<duye_rpc_msg where="client">
    <fun_name>name</fun_name>
    <parameter type="bool" name="para_name">value</parameter>
    <parameter type="int" name="para_name">value</parameter>
    <parameter type="uint" name="para_name">value</parameter>
    <parameter type="string" name="para_name">value</parameter>
</duye_rpc_msg>

-------SER_GET_FILE_RESP format:
<?xml version="1.0" encoding="utf-8"?>
<duye_rpc_msg where="server">
    <fun_name>name</fun_name>
    <parameter type="bool" name="para_name">value</parameter>
    <parameter type="int" name="para_name">value</parameter>
    <parameter type="uint" name="para_name">value</parameter>
    <parameter type="string" name="para_name">value</parameter>
</duye_rpc_msg>
*/

namespace duye {

/**
 * @brief rpc client message type
 */
typedef enum
{
    // get file request, in xml name "rcp_cli_req"
    RPC_CLI_REQ,
    // unknown message type
    RPC_CLI_UNKNOWN
} RpcClientMsgType;

/**
 * @brief rpc server message type
 */
typedef enum
{
    // get file request, in xml name "rpc_ser_resp"
    RPC_SER_RESP,
    // interal error, in xml name "rpc_ser_error"
    RPC_SER_ERROR,
    // unknown message type
    RPC_SER_UNKNOWN 
} RcpServerMsgType;

#define RPC_E_BASE 100

/**
 * @brief file transfer server message type
 */
typedef enum
{
    // rpc message format wrong
    RPC_E_FORMAT = RPC_E_BASE,
    // rpc message parameter wrong
    RPC_E_PARA,
    // rpc message version wrong
    RPC_E_VERSION,
    // rpc error max number
    RPC_E_MAX
} RcpServerErrorType;

class RpcParaVal
{
public:
    RpcParaVal() {}
    explicit RpcParaVal(const std::string& strVal, const std::string& type) 
        : m_boolVal(false), m_intVal(0), m_uintVal(0)
    {
        setVal(strVal, type);
    }

    void setVal(const std::string& value, const std::string& type)
    {  
        if (type == "bool")
        {
            if (value == "true")
               m_boolVal = true;
            else
               m_boolVal = false;
        }
        else if (type == "int")
        {
            m_intVal = (int32)StrHelper::toInt(value);
        }
        else if (type == "uint")
        {
            m_uintVal = (uint32)StrHelper::toInt(value);
        }
        else if (type == "string")
        {
            m_strVal = value;
        }    
        else
            return;

        m_value = value;
    }
    
    std::string getVal() { return m_value; }

    bool boolVal() { return m_boolVal; }
    void setBoolVal(const bool val) { m_boolVal = val; }
    int32 intVal() { return m_intVal; }
    void setIntVal(const int32 val) { m_intVal = val; }
    uint32 uintVal() { return m_uintVal; }
    void setUintVal(const uint32 val) { m_uintVal = val; }
    const std::string& strVal() const { return m_strVal; }
    void setStrVal(const std::string& val) { m_strVal = val; }
    
private:
    bool        m_boolVal;
    int32       m_intVal;
    uint32      m_uintVal;
    std::string m_strVal;
    std::string m_value;
};

/**
 * @brief rpc fun define
 */
class RpcFunPara
{
public:
    RpcFunPara() {}
    RpcFunPara(const std::string& inname, const std::string& intype, const std::string& inval)
        : name(inname), type(intype)
    {
        val.setVal(inval, intype);
    }

    std::string     name;
    // (boo, int, uint, string)
    std::string     type;
    // input/output
    std::string     from;
    // value
    RpcParaVal val;
};

// <para_name, RpcFunPara>
typedef std::map<std::string, RpcFunPara> RpcFunParaMap;

/**
 * @brief rpc fun define
 */
class RpcFun
{
public:
    RpcFun() {}

    bool getInParaVal(const std::string& paraName, std::string& value)
    {
        RpcFunParaMap::iterator iter = inParaMap.find(paraName);
        if (iter == inParaMap.end())
            return false;

        value = iter->second.val.getVal();
        
        return true;
    }

    bool getOutParaVal(const std::string& paraName, std::string& value)
    {
        RpcFunParaMap::iterator iter = outParaMap.find(paraName);
        if (iter == outParaMap.end())
            return false;

        value = iter->second.val.getVal();
        
        return true;
    }    

    // function name
    std::string    name;
    // input parameters 
    RpcFunParaMap  inParaMap;
    // output parameters 
    RpcFunParaMap  outParaMap;
};

// <fun_name, RpcFun>
typedef std::map<std::string, RpcFun> RpcFunMap;

/**
 * @brief rpc message data, to user
 */
class RpcReqMsg
{
public:
    RpcReqMsg() /*: orgData(NULL), orgLen(0)*/ {}

    //XmlDocument    xmlDoc;
    RpcFun         rpcFun;
    //int8*          orgData;
    //uint32         orgLen;
};

/**
 * @brief rpc message data, to user
 */
class RpcRespMsg
{
public:
    RpcRespMsg() {}
    RpcFun         rpcFun;
};

/**
 * @brief network file server parameters
 */
class RpcMsgParser
{
public:
    /**
     * @brief verify client protocol
     * @param [in] clientMsg : client message
     * @param [in] msgLen : message length
     * @param [out] rpcReqMsg : output RpcReqMsg
     * @param [out] errorID : error ID
     * @return : true/false
     */
    static bool formatReqMsg(const int8* clientMsg, const uint32 msgLen, RpcReqMsg& rpcReqMsg, uint32& errorID);

    /**
     * @brief parser client message type
     * @param [in] errorID : error ID
     * @param [out] outXmlMsg : output xml format
     * @return true/false
     */
    static bool formatRespErrorMsg(const uint32 errorID, std::string& outXmlMsg);   

    /**
     * @brief parser client message type
     * @param [in] respMsg : input 
     * @param [out] outXmlMsg : output xml format
     * @return true/false
     */    
    static bool formatRespMsg(RpcReqMsg& reqMsg, std::string& outXmlMsg);
};
}

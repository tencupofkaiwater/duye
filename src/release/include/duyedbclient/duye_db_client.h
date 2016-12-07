/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_client.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-26
* @note 
*
* 1. 2016-04-26 duye Created this file
*/
#pragma once

#include <string>
#include <duye_type.h>
#include <duye_tcp_client.h>

namespace duye {

/**
 * @brief : db client
 */
class DBClient
{
public:
    DBClient();
    ~DBClient();

    /**
     * @brief connect to db server by network socket, keep db service is running
     * @para [in] dbAddr : db service address
     * @para [in] dbPort : db service port
     * @para [in] user : db service user name
     * @para [in] pwd : db service user pwd
     * @return true/false 
     */
    bool connect(const std::string& dbAddr, const uint16 dbPort, const std::string& user, const std::string& pwd);

    /**
     * @brief : connect to db server by UINX socket, keep db service is running
     * @para [in] user : db service user name
     * @para [in] pwd : db service user pwd
     * @para [in] socketFile : UINX socket file, default is /tmp/duyedb.socket, by db service generate
     * @return true/false 
     */
    bool connect(const std::string& user, const std::string& pwd, const std::string& socketFile);
    
     /**
     * @brief : query data
     * @para [in] sql : query sql string
     * @return true/false 
     */
    bool query(const int8* sql);
    bool query(const std::string& sql);   

private:
    bool close();
    
private:
    TcpClient   m_tcpClient;
    bool        m_isConnected;
};

}

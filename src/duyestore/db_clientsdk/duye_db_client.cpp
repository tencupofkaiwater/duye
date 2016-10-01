/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_client.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-26
* @note 
*
* 1. 2016-04-26 duye Created this file
*/
#include <duye_logger.h>
#include <duye_db_client.h>

static const int8* DUYE_LOG_PREFIX = "duyefour.db.clientsdk";

namespace duye {

DBClient::DBClient() : m_isConnected(false) {}
DBClient::~DBClient() {}

bool DBClient::connect(const std::string& dbAddr, const uint16 dbPort, const std::string& user, const std::string& pwd)
{
    if (m_isConnected)
        return true;
    
    m_isConnected = m_tcpClient.connect(dbAddr, dbPort, 3000);
    return m_isConnected;
}

bool DBClient::connect(const std::string& user, const std::string& pwd, const std::string& socketFile)
{
    return true;
}

bool DBClient::query(const int8* sql)
{
    if (sql == NULL || *sql == 0)
    {
        DUYE_ERROR("sql == NULL || *sql == 0");
        return false;
    }
    
    return true;
}

bool DBClient::query(const std::string& sql)
{
    return query(sql.c_str());
}

bool DBClient::close()
{
    m_isConnected = false;
    return false;
}

}

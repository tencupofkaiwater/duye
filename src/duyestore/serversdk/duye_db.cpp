/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-29
* @note 
*
* 1. 2016-04-29 duye Created this file
*/
#include <duye_logger.h>
#include <duye_db_query.h>
#include <duye_db.h>

//static const int8* DUYE_LOG_PREFIX = "duye.db";

namespace duye {

Database::Database(){}
Database::~Database() {}

const std::string& Database::name() const
{
    return m_name;
}

const DBTableMap& Database::tables() const
{
    return m_tableMap;
}

bool Database::create(const TabAttr& tabAttr, const TabColumnAttrMap columns)
{
    return true;
}

bool Database::remove(const std::string& name)
{
    return true;
}

bool Database::insert(const std::string& name, const TabRowData& rows)
{
    return true;
}

bool Database::up(const std::string& name, const TabRowData& rows)
{
    return true;
}

bool Database::del(const std::string& name, const TabRowData& rows)
{
    return true;
}

bool Database::query(const std::string& name, const QueryCond& condition, QueryResult& result)
{
    return true;
}

DatabaseMgr::DatabaseMgr() 
{
    DBOpVector adminOp;
    for (uint32 i = DB_USER_LOGIN; i < DB_OP_MAX; i++)
        adminOp.push_back((DBOperaterId)i);
    
    DBOpVector userOp;
    for (uint32 i = DB_TAB_CREATE; i < DB_OP_MAX; i++)
        userOp.push_back((DBOperaterId)i);

    DBOpVector visitorOp;
    visitorOp.push_back(DB_DATA_QUERY);
    
    m_permissionsMap[DB_ADMIN] = adminOp;
    m_permissionsMap[DB_USER] = userOp;
    m_permissionsMap[DB_VISITOR] = visitorOp;

    m_operaterIdMap[DB_USER_LOGIN]    = "login";
    m_operaterIdMap[DB_USER_LOGOUT]   = "logout";
    m_operaterIdMap[DB_USER_ADD]      = "user_add";
    m_operaterIdMap[DB_USER_DELETE]   = "user_delete";
    m_operaterIdMap[DB_USER_MODIFY]   = "user_modify";
    m_operaterIdMap[DB_CREATE]        = "db_create";
    m_operaterIdMap[DB_REMOVE]        = "db_remove";
    m_operaterIdMap[DB_MODIFY]        = "db_modify";
    m_operaterIdMap[DB_TAB_CREATE]    = "tab_create";
    m_operaterIdMap[DB_TAB_REMOVE]    = "tab_remove";    
    m_operaterIdMap[DB_TAB_MODIFY]    = "tab_modify";
    m_operaterIdMap[DB_DATA_INSERT]   = "data_insert";
    m_operaterIdMap[DB_DATA_UPDATE]   = "data_update";
    m_operaterIdMap[DB_DATA_DELETE]   = "data_delete";
    m_operaterIdMap[DB_DATA_QUERY]    = "data_query"; 

    DBOperaterIdMap::iterator iter = m_operaterIdMap.begin();
    for (; iter != m_operaterIdMap.end(); ++iter)
        m_operaterNameMap[iter->second] = iter->first;   
}

DatabaseMgr::~DatabaseMgr() {}

bool DatabaseMgr::create(const std::string& name, const std::string& user, const std::string pwd)
{
    return true;
}

bool DatabaseMgr::remove(const std::string& name, const std::string& user, const std::string pwd) 
{
    return true;
}

}

/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-29
* @note 
*
* 1. 2016-04-29 duye Created this file
*/
#pragma once

#include <string>
#include <duye_type.h>
#include <duye_singleton.h>
#include <duye_db_const.h>
#include <duye_db_tab.h>
#include <duye_db_query.h>

namespace duye {

/**
 * @brief database
 */
class Database
{     
public:
    Database();
    ~Database();

    /**
     * @brief get database name
     * @return table name
     */
    const std::string& name() const;

    /**
     * @brief get all table
     * @return : all tables
     */
    const DBTableMap& tables() const;

    /**
     * @brief create table
     * @para [in] tabAttr : table attribute
     * @para [in] columns : columns
     * @return : true/false
     */
    bool create(const TabAttr& tabAttr, const TabColumnAttrMap columns);

    /** 
     * @brief remove table
     * @para [in] name : table name
     * @return : true/false
     */
    bool remove(const std::string& name);

    /**
     * @brief insert record
     * @para [in] name : table name
     * @para [in] rows : will insert row data
     * @return : true/false
     */
    bool insert(const std::string& name, const TabRowData& rows);

    /**
     * @brief update record
     * @para [in] name : table name
     * @para [in] rows : will update row data
     * @return : true/false
     */
    bool up(const std::string& name, const TabRowData& rows);    

    /**
     * @brief delete record
     * @para [in] name : table name
     * @para [in] rows : will update row data
     * @return : true/false
     */
    bool del(const std::string& name, const TabRowData& rows);

    /**
     * @brief delete record
     * @para [in] name : table name
     * @para [in] rows : will update row data
     * @return : true/false
     */
    bool query(const std::string& name, const QueryCond& condition, QueryResult& result);

private:
    // database name
    std::string     m_name;
    DBTableMap      m_tableMap;
};

/**
 * @brief database
 */
class DatabaseMgr : public Singleton<DatabaseMgr>
{
public:
    // <database_name, Database>
    typedef std::map<const std::string, Database> DatabaseMap;
    
public:
    DatabaseMgr();
    ~DatabaseMgr();
    
    /**
     * @brief create database
     * @para [in] name : database name
     * @para [in] user : user name
     * @para [in] pwd : user pwd
     * @return : true/false
     */
    bool create(const std::string& name, const std::string& user, const std::string pwd);

    /**
     * @brief remove database
     * @para [in] name : database name
     * @para [in] user : user name
     * @para [in] pwd : user pwd
     * @return : true/false
     */  
    bool remove(const std::string& name, const std::string& user, const std::string pwd); 

    /**
     * @brief find operation name
     * @para [in] id : operater id
     * @return : operation name
     */  
    const DBOperaterName& opName(const DBOperaterId& id) const;

    /**
     * @brief find operation id
     * @para [in] name : operater name
     * @return : operation id
     */  
    const DBOperaterId& opId(const DBOperaterName& name) const;
    
private:
    // database name
    DatabaseMap         m_databaseMap;
    DBPermissionsMap    m_permissionsMap;
    DBOperaterIdMap     m_operaterIdMap;
    DBOperaterNameMap   m_operaterNameMap;
};

}

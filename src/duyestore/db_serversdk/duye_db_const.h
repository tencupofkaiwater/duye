/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_const.h
* @version     
* @brief      
* @author   duye
* @date	    2016-05-04
* @note 
*
* 1. 2016-05-04 duye Created this file
*/
#pragma once

#include <string>
#include <vector>
#include <map>
#include <duye_type.h>

namespace duye {

/**
 * @brief data type define
 */
typedef enum
{
    // unknown type
    DB_UNKNOWN,
    // file type
    DB_FILE,
    // bool type
    DB_BOOL,
    // integer type
    DB_INT,
    // unsigned integer type
    DB_UINT,
    // float type
    DB_FLOAT,
    // string type
    DB_STR,
    // bytes type
    DB_BYTE,
    // DB type max
    DB_TYPE_MAX
}DBDataType;

/**
 * @brief database user role
 */
typedef enum
{
    // database administrator
    // mapping DBOperater (DB_USER_LOGIN -- DB_DATA_QUERY)
    DB_ADMIN,
    // database user
    // mapping DBOperater (DB_TAB_CREATE -- DB_DATA_QUERY)
    DB_USER,
    // database visitor
    // mapping DBOperater (DB_DATA_QUERY)
    DB_VISITOR,
    // max number value
    DB_ROLE_MAX
} DBUserRole;

/**
 * @brief database operation
 */
typedef enum
{
    //-------database user operation----
    // user login
    DB_USER_LOGIN,
    // user logout
    DB_USER_LOGOUT,
    // add user
    DB_USER_ADD,
    // delete user
    DB_USER_DELETE,
    // modify user
    DB_USER_MODIFY,
    
    //-------database operation----
    // create database
    DB_CREATE,
    // remove database
    DB_REMOVE,
    // modify database
    DB_MODIFY,
    
    //-------table operation-------
    // create table
    DB_TAB_CREATE,
    // remove table
    DB_TAB_REMOVE,
    // modify table
    DB_TAB_MODIFY,
    
    //-------data operation---
    // insert record
    DB_DATA_INSERT,
    // update record
    DB_DATA_UPDATE,
    // delete record
    DB_DATA_DELETE,
    // query record
    DB_DATA_QUERY,
    // max value
    DB_OP_MAX    
} DBOperater;

typedef DBOperater DBOperaterId;
typedef std::string DBOperaterName;
typedef std::map<DBOperaterId, DBOperaterName> DBOperaterIdMap;
typedef std::map<DBOperaterName, DBOperaterId> DBOperaterNameMap;

typedef DBUserRole DBUserRoleId;
typedef std::vector<DBOperaterId> DBOpVector;
typedef std::map<DBUserRoleId, DBOpVector> DBPermissionsMap;

}

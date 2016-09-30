/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_query.h
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
#include <duye_db_tab.h>

namespace duye {

/**
 * @brief query condition
 */
class QueryCond
{
public:
    QueryCond();
    ~QueryCond();
};

/**
 * @brief query result
 */
class QueryResult
{
public:
    QueryResult();
    ~QueryResult();
};

/**
 * @brief query
 */
class Query
{
public:
    Query();
    ~Query();
};

}

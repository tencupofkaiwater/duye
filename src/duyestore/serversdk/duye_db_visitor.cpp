/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_visitor.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-29
* @note 
*
* 1. 2016-04-29 duye Created this file
*/
#include <duye_logger.h>
#include <duye_db_visitor.h>

//static const int8* DUYE_LOG_PREFIX = "duye.db.visitor";

namespace duye {

DBVisitor::DBVisitor()
{
}

DBVisitor::DBVisitor(const IPv4Addr& clientAddr, const AcceptSocket& clientSocket)
{
}

DBVisitor::~DBVisitor() {}

bool DBVisitor::handleReq(const int8* data, const uint64 len)
{
    return true;
}

}

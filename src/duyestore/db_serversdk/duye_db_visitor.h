/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_visitor.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-29
* @note 
*
* 1. 2016-04-29 duye Created this file
*/
#pragma once

#include <duye_type.h>
#include <duye_system.h>

namespace duye {

/**
 * @brief db visitor
 */
class DBVisitor
{
public:
    DBVisitor();
    explicit DBVisitor(const IPv4Addr& clientAddr, const AcceptSocket& clientSocket);
    ~DBVisitor();

    /**
     * @brief handle client request message
     * @param [in] data : client message
     * @param [in] len : message length
     * @return : true/false
     */   
    bool handleReq(const int8* data, const uint64 len);

private:
    IPv4Addr       m_clientAddr;
    AcceptSocket   m_clientSocket;
};

}

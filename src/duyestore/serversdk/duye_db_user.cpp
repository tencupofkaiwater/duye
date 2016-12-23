
/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_user.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-29
* @note 
*
* 1. 2016-04-29 duye Created this file
*/
#include <duye_logger.h>
#include <duye_db_user.h>

//static const int8* DUYE_LOG_PREFIX = "duye.db.user";

namespace duye {

DBUser::DBUser(){}
DBUser::DBUser(const std::string& name, const std::string& pwdMd5, const DBUserRole& role)
    : m_name(name), m_pwdMd5(pwdMd5), m_role(role) {}
DBUser::~DBUser() {}
    
void DBUser::setName(const std::string& name)
{
    m_name = name;
}

const std::string& DBUser::name() const
{
    return m_name;
}

void DBUser::setPwdMd5(const std::string& pwdMd5)
{
    m_pwdMd5 = pwdMd5;
}

const std::string& DBUser::pwdMd5() const
{
    return m_pwdMd5;
}

void DBUser::setRole(const DBUserRole& role)
{
    m_role = role;
}

const DBUserRole& DBUser::role() const
{
    return m_role;
}

}

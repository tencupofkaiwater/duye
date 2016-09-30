/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duyetwo_user_mgr.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-04-13
* @note 
*
* 1. 2016-04-13 duye Created this file
*/
#include <duyetwo_user_session.h>
#include <duyetwo_user_mgr.h>

static const int8* DUYE_LOG_PREFIX = "duyetwo.user.mgr";

namespace duyetwo {

UserMgr::UserMgr() : m_session(NULL)
{
    m_session = new UserSession();
}

UserMgr::~UserMgr()
{
}

UserMgr& UserMgr::instance()
{
    static UserMgr ins;
    return ins;
}

bool UserMgr::load(const std::string& name, const std::string& pwd)
{
    return true;
}

bool UserMgr::setpwd(const std::string& name, const std::string& pwd)
{
    return true;
}

}
/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duyetwo_user_mgr.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-13
* @note 
*
* 1. 2016-04-13 duye Created this file
*/
#pragma once

#include <duye_system.h>

namespace duyetwo {

class UserSession;

/**
 * @brief user manager
 */
class UserMgr
{
public:
	UserMgr();
	~UserMgr();

    static UserMgr& instance();

    /**
     * @brief user load
     * @param [in] name : user name
     * @param [in] pwd : user pwd
     * @return : on successed, return true. on failed, return false
     */
    bool load(const std::string& name, const std::string& pwd);

    /**
     * @brief reset pwd
     * @param [in] name : user name
     * @param [in] pwd : user pwd
     * @return : on successed, return true. on failed, return false
     */
    bool setpwd(const std::string& name, const std::string& pwd);

private:
    UserSession*    m_session;
};
}
/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duyetwo_user_session.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-13
* @note 
*
* 1. 2016-04-13 duye Created this file
*/
#pragma once

#include <map>
#include <duye_system.h>

namespace duyetwo {

/**
 * @brief user status
 */
typedef enum 
{
    USER_OFF,
    USER_ON, 
    USER_LOCKED
} UserStatus;
 
/**
 * @brief user session
 */
class UserInfo
{
public:
    UserInfo() : status(USER_OFF) {}
    
    UserStatus  status;
    std::string name;
    uint32      id;
};

// <name, UserInfo>
typedef std::map<std::string, UserInfo> UserInfoMap;

/**
 * @brief user session
 */
class UserSession
{    
public:
    UserSession();
    ~UserSession();

private:
    UserInfoMap     m_userInfoMap;
};
}
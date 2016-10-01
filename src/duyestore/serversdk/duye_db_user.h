/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_user.h
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
#include <duye_type.h>
#include <duye_db_const.h>

namespace duye {

/**
 * @brief database user
 */
class DBUser
{     
public:
    DBUser();
    explicit  DBUser(const std::string& name, const std::string& pwdMd5, const DBUserRole& role);
    ~DBUser();

    /**
     * @brief set user name
     */
    void setName(const std::string& name);

    /**
     * @brief get user name
     * @return user name
     */
    const std::string& name() const;

    /**
     * @brief set pwd md5
     */
    void setPwdMd5(const std::string& pwdMd5);

    /**
     * @brief get pwd md5
     * @return pwd md5
     */
    const std::string& pwdMd5() const;    

    /**
     * @brief set role
     */
    void setRole(const DBUserRole& role);

    /**
     * @brief get role
     * @return role
     */
    const DBUserRole& role() const;        

private:
    // database user name
    std::string     m_name;
    // database user pwd md5
    std::string     m_pwdMd5;
    // user role
    DBUserRole      m_role;    
};

}

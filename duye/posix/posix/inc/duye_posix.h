/*************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_posix.h
* @version     
* @brief      
* @author   duye
* @date     2014-03-09
* @note 
*
*  1. 2014-03-09 duye Created this file
* 
*/

#pragma once

#include <stdio.h>
#include <duye/posix/inc/duye_posix_def.h>
#include <duye/posix/system/inc/duye_system.h>

DUYE_POSIX_NS_BEG 

class DuyePosix
{
public:
    DuyePosix()
    {
        System system;
        printf("===============%d \n", system.GetMaxFileNameSize());
    }
    
    ~DuyePosix();
};

DUYE_POSIX_NS_END 

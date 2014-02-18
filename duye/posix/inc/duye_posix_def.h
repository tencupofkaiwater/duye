/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_posix_def.h
* @version     
* @brief      
* @author   duye
* @date     2013-12-8
* @note 
*
*  1. 2013-12-8 duye Created this file
* 
*/

#pragma once

#include <stdio.h>

#include <duye/inc/duye_type.h>

#define POSIX_ERROR(prefix, x) \    
    printf("<ERROR><%s>%s", prefix, x);

#define POSIX_WARN(prefix, x) \
    printf("<WARN><%s>%s", prefix, x);

#define POSIX_INFO(prefix, x) \
    printf("<INFO><%s>%s", prefix, x);

#define POSIX_DEBUG(prefix, x) \
    printf("<DEBUG><%s>%s", prefix, x);

#define POSIX_TARCE(prefix, x) \
    printf("<TRACE><%s>%s", prefix, x);    
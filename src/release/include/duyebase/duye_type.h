/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_type.h
* @version  	   
* @brief      
* @author   duye
* @date	    2014-07-12
* @note 
*
*  1. 2014-07-12 duye Created this file
* 
*/
#pragma once

/** 
 * @brief base type define
 */
#ifndef YTPEDEF_INT8_H
#define YTPEDEF_INT8_H
typedef char               int8;
#endif
typedef short		       int16;
typedef int		           int32;
typedef long long	       int64;
typedef unsigned char	   uint8;
typedef unsigned short	   uint16;
typedef unsigned int	   uint32;
typedef unsigned long long uint64;

/** 
 * @brief limits number for path max length
 */
#define PATH_MAX 1024

/** 
 * @brief limits number for file name max length
 */
#define FILE_NAME_MAX 256

/** 
 * @brief limits number for error info buffer size
 */
#define ERROR_BUF_SIZE 1024

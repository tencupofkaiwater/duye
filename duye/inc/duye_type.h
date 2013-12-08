/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file		duye_type.h
* @version     
* @brief      
* @author   duye
* @date     2013-11-15
* @note 
*
*  1. 2013-11-15 duye Created this file
* 
*/

#pragma once

#include <limits.h>
#include <assert.h>

#ifndef NULL
#define NULL 0
#endif

// limits       
#define DUYE_INT_MIN 		INT_MIN
#define DUYE_INT_MAX 	    INT_MAX
#define DUYE_UINT_MAX 		UINT_MAX
#define DUYE_LONG_MIN 		LONG_MIN
#define DUYE_LONG_MAX 		LONG_MAX
#define DUYE_ULONG_MAX 		ULONG_MAX

// return value define
#define DUYE_SUCCESS        0
#define DUYE_FAILURE        (-1)

#ifdef DUYE_ASSERT
#define D_ASSERT(x)
#else
#define D_ASSERT(x) assert(x)
#endif

// base type define
typedef char                Int8_t;
typedef short int           Int16_t;
typedef int                 Int32_t;
typedef long int            Int64_t;

typedef unsigned char       UInt8_t;
typedef unsigned short int  UInt16_t;
typedef unsigned int        UInt32_t;
typedef unsigned long int   UInt64_t;

typedef Int32_t				Ret_t;

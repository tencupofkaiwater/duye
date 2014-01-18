/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_type.h
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
typedef void                D_Void;
typedef bool                D_Bool;
typedef char                D_Int8;
typedef short int           D_Int16;
typedef int                 D_Int32;
typedef long int            D_Int64;

typedef unsigned char       D_UInt8;
typedef unsigned short int  D_UInt16;
typedef unsigned int        D_UInt32;
typedef unsigned long int   D_UInt64;

typedef D_Int32				D_Result;

// define all namespace 
#define DUYE_NS_BEG namespace duye {
#define DUYE_NS_END }

DUYE_NS_BEG
DUYE_NS_END

// stl namespace, path : /duye/stl
#define DUYE_STL_NS_BEG namespace duye { namespace stl {
#define DUYE_STL_NS_END }}

DUYE_STL_NS_BEG
DUYE_STL_NS_END

// posix namespace, path : /duye/posix
#define DUYE_POSIX_NS_BEG namespace duye { namespace posix {
#define DUYE_POSIX_NS_END }}

DUYE_POSIX_NS_BEG  
DUYE_POSIX_NS_END

// ut namespace, path : /duye/ut
#define DUYE_UT_NS_BEG namespace duye { namespace ut {
#define DUYE_UT_NS_END }}

DUYE_UT_NS_BEG
DUYE_UT_NS_END

// util namespace, path : /duye/util
#define DUYE_UTIL_NS_BEG namespace duye { namespace util {
#define DUYE_UTIL_NS_END }}

DUYE_UTIL_NS_BEG
DUYE_UTIL_NS_END
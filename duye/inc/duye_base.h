/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_base.h
* @version     
* @brief      
* @author   duye
* @date     2014-02-27
* @note 
*
*  1. 2014-02-27 duye Created this file
* 
*/

#pragma once

#include <assert.h>

#ifndef NULL
#define NULL 0
#endif

// limits       
#define D_INT_MIN        INT_MIN
#define D_INT_MAX        INT_MAX
#define D_UINT_MAX       UINT_MAX
#define D_LONG_MIN       LONG_MIN
#define D_LONG_MAX       LONG_MAX
#define D_ULONG_MAX      ULONG_MAX

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

// return value define
typedef D_Int32				D_Result;

#define D_SUCCESS           0
#define D_FAILURE           (-1)

#define D_RETYES(ret) { return ret == D_SUCCESS; }
#define D_RETNO(ret) { return ret != D_SUCCESS; }

#ifdef DUYE_ASSERT
#define D_ASSERT(x)
#else
#define D_ASSERT(x)  assert(x)
#endif
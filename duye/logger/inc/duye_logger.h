/***********************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		duye_logger.h
* @version     
* @brief      
* @author   duye
* @date     2014-2-18
* @note 
*
*  1. 2014-2-18 duye Created this file
* 
*/

#pragma once

#include <stdio.h>

#include <duye/inc/duye_logger_def.h>

#define DUYE_LOG_INIT() \
    DuyeLogger::Init();
    
#define DUYE_LOG_UNINIT() \
    DuyeLogger::Uninit();

#define DUYE_LOG_ERROR(prefix, x) \
    DuyeLogger::PrintError(prefix, "error");

#define DUYE_LOG_WARN(prefix, x) \
    DuyeLogger::PrintWarn(prefix, "warn");

#define DUYE_LOG_INFO(prefix, x) \
    DuyeLogger::PrintWarn(prefix, "info");

#define DUYE_LOG_DEBUG(prefix, x) \
    DuyeLogger::PrintWarn(prefix, "debug");    

#define DUYE_LOG_TRACE(prefix, x) \
    DuyeLogger::PrintWarn(prefix, "trace");  

// brief : posix socket wrapper class
class DuyeLogger
{
public:
	// brief : init
	// note		
    static D_Bool Init();

	// brief : uninit
	// note		    
    static D_Bool Uninit();

	// brief : print error
	// @para [in]str : error information
	// note		    
    static void PrintError(const D_Int8* prefix, const D_Int8* str);

	// brief : print warn
	// @para [in]str : error information
	// note		    
    static void PrintWarn(const D_Int8* prefix, const D_Int8* str);

	// brief : print info
	// @para [in]str : error information
	// note		    
    static void PrintInfo(const D_Int8* prefix, const D_Int8* str);

	// brief : print debug
	// @para [in]str : error information
	// note		    
    static void PrintDebug(const D_Int8* prefix, const D_Int8* str);

	// brief : print trace
	// @para [in]str : error information
	// note		    
    static void PrintTrace(const D_Int8* prefix, const D_Int8* str);
};

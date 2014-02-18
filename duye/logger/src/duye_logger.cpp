/***********************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		duye_logger.cpp
* @version     
* @brief      
* @author   duye
* @date     2014-2-18
* @note 
*
*  1. 2014-2-18 duye Created this file
* 
*/

#include <duye/logger/inc/duye_logger.h>

D_Bool DuyeLogger::Init()
{
    return true;
}
       
D_Bool DuyeLogger::Uninit()
{
    return true;
}
      
void DuyeLogger::PrintError(const D_Int8* prefix, const D_Int8* str)
{
    printf("<ERROR><%s>%s", prefix, str);
}
   
void DuyeLogger::PrintWarn(const D_Int8* prefix, const D_Int8* str)
{
    printf("<WARN><%s>%s", prefix, str);
}
       
void DuyeLogger::PrintInfo(const D_Int8* prefix, const D_Int8* str)
{
    printf("<INFO><%s>%s", prefix, str);
}
       
void DuyeLogger::PrintDebug(const D_Int8* prefix, const D_Int8* str)
{
    printf("<DEBUG><%s>%s", prefix, str);
}

void DuyeLogger::PrintTrace(const D_Int8* prefix, const D_Int8* str)
{
    printf("<TRACE><%s>%s", prefix, str);
}

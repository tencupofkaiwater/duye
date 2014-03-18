/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_singleton.h
* @version     
* @brief      
* @author   duye
* @date     2014-03-04
* @note 
*
*  1. 2014-03-04 duye Created this file
* 
*/

#pragma once

#include <list>
#include <duye/dstl/inc/duye_stl_def.h>

DUYE_STL_NS_BEG

template<typename T>
class Singleton
{
public:
    typedef T object_type;
    
public:
    static T* GetInstance();
    
protected:
    Singleton() {}
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);

private:
    static T* m_instance;
};

DUYE_STL_NS_END
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

#include <duye/component/inc/duye_component_def.h>
#include <list>

DUYE_COMPONENT_NS_BEG

template<typename T>
class Singleton
{
public:
    typedef T object_type;
    
public:
    static T* GetInstance();
    
private:
    Singleton() {}
    Singleton(const Singleton&);
    void operator=(const Singleton&);

private:
    static T* m_instance;
};

DUYE_COMPONENT_NS_END
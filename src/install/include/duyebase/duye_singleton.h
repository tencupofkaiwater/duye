/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_singleton.h
* @version     
* @brief      
* @author   duye
* @date     2014-06-18
* @note 
*
*  1. 2014-06-18 duye created this file
* 
*/
#pragma once

#include <duye_system.h>

namespace duye {

/** 
 * @brief singletion class template, be inherit
 */
template<typename T>
class Singleton
{
public:
    static T& instance();
    
protected:
    Singleton() {}
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
};

template<typename T>
T& Singleton<T>::instance()
{
    static T t;
    return t;
}

/**
 * @brief singletion class template, used at declaration
 */
template<typename T>
class SingletonObj : public T
{
public:
    static T& instance();
    
protected:
    SingletonObj() {}
    SingletonObj(const SingletonObj&);
    SingletonObj& operator=(const SingletonObj&);
};

template<typename T>
T& SingletonObj<T>::instance()
{
    static T t;
    return t;
}

}

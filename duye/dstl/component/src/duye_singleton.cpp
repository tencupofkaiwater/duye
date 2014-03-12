/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_singleton.cpp
* @version     
* @brief      
* @author   duye
* @date     2014-03-04
* @note 
*
*  1. 2014-03-04 duye Created this file
* 
*/

#include <duye/dstl/component/inc/duye_singleton.h>

DUYE_COMPONENT_NS_BEG

template<typename T> typename Singleton<T>::object_type* Singleton<T>::m_instance = NULL;

template<typename T>
T* Singleton<T>::GetInstance()
{
    if (m_instance == NULL)
    {
        static T instance;
        m_instance = &instance;
    }

    return m_instance;
}

DUYE_COMPONENT_NS_END
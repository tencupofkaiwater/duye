/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_obj_pool.h
* @version     
* @brief      
* @author   duye
* @date     2014-03-01
* @note 
*
*  1. 2014-03-01 duye Created this file
* 
*/

#pragma once

#include <list>

#include <duye/component/inc/duye_component_def.h>


DUYE_COMPONENT_NS_BEG

/*
class ObjPoolUserIf
{
public:
    virtual ~ObjPoolUserIfe() {}
    virtual D_Result Init() = 0;
    virtual D_Result Uninit() = 0;
};
*/

template <class T>
class ObjPool
{
public:
    typedef std::list<T*> ObjList;

public:
    ObjPool();
    ObjPool(const D_UInt32 count);
    ~ObjPool();

    void SetCount(const D_UInt32 count);
    

private:
    ObjPool(const ObjPool<T>&);
    ObjPool<T>& operator=(const ObjPool<T>&); 

    void InitObjPool();
    void ReleaseObjPool();
    
private:    
    D_UInt32    m_count;
    ObjList     m_used;
    ObjList     m_idle;
};

template <class T>
ObjPool<T>::ObjPool() : m_count(0)
{
}

template <class T>
ObjPool<T>::ObjPool(const D_UInt32 count) : m_count(count)
{
    InitObjPool();
}

template <class T>
ObjPool<T>::~ObjPool()
{
    ReleaseObjPool();   
}

template <class T>
void ObjPool<T>::SetCount(const D_UInt32 count)
{
    ReleaseObjPool();
    m_count = count;
    InitObjPool();
}

template <class T>
void ObjPool<T>::InitObjPool()
{
    if (m_count == 0)
    {
        return;
    }
    
    for (D_UInt32 i = 0; i < m_count; i++)
    {
        T* t = new T;
        if (t->Init())
        {
            m_idle.push_back(new T); 
        }
    }
}

template <class T>
void ObjPool<T>::ReleaseObjPool()
{
    if (m_count == 0)
    {
        return;
    }
    
    
}

DUYE_COMPONENT_NS_END
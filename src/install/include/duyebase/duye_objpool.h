/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Gohoop Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_objpool.h
* @version     
* @brief      
* @author   duye
* @date	    2014-06-18
* @note 
*
*  1. 2014-06-18 duye created this file
* 
*/
#pragma once

#include <list>
#include <duye_system.h>

namespace duye {

/** 
 *  @brief provide user inheritance
 */
class ObjPoolIf
{
public:
    virtual ~ObjPoolIf() {}

    /**
     * @brief be call by object pool, before used object
     * @return true/false
     */    
    virtual bool init() = 0;

    /**
     * @brief be call by object pool, after using finished
     * @return true/false
     */   
    virtual bool uninit() = 0;
};

/** 
 * @brief mamagement object set
 */
template <class T>
class ObjPool
{
public:
    typedef std::list<T*> ObjList;

public:
    ObjPool();
    
    /**
     * @brief constructor
     * @param count : the size of object pool
     */    
    ObjPool(const uint32 count);
    ~ObjPool();

    /**
     * @brief set the size of object pool
     * @param count : the size of object pool
     */
    void setCount(const uint32 count);

    /**
     * @brief get the size of object pool
     * @return count : the size of object pool
     */
    uint32 getCount() const;

private:
    ObjPool(const ObjPool<T>&);
    ObjPool<T>& operator=(const ObjPool<T>&); 

    void initObjPool();
    void releaseObjPool();
    
private:    
    uint32     		m_count;
    ObjList    m_used;
    ObjList    m_idle;
};

template <class T>
ObjPool<T>::ObjPool() : m_count(0) {}

template <class T>
ObjPool<T>::ObjPool(const uint32 count) : m_count(count)
{
    initObjPool();
}

template <class T>
ObjPool<T>::~ObjPool()
{
    releaseObjPool();   
}

template <class T>
void ObjPool<T>::setCount(const uint32 count)
{
    releaseObjPool();
    m_count = count;
    initObjPool();
}

template <class T>
uint32 ObjPool<T>::getCount() const
{
    return m_count;
}

template <class T>
void ObjPool<T>::initObjPool()
{
    if (m_count == 0)
    {
    	return;
    }

    for (uint32 i = 0; i < m_count; i++)
    {
    	T* t = new T;
    	if (t->Init())
	    {
			m_idle.push_back(new T); 
        }
    }
}

template <class T>
void ObjPool<T>::releaseObjPool()
{
    if (m_count == 0)
    {
    	return;
    }
}
}

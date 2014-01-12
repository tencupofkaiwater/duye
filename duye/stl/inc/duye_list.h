/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_list.h
* @version     
* @brief      
* @author   duye
* @date     2013-12-22
* @note 
*
*  1. 2013-12-22 duye Created this file
* 
*/

#pragma once

#include <duye/stl/inc/duye_stl_def.h>
#include <duye/stl/inc/duye_bytemem.h>
#include <duye/stl/inc/duye_stl_iterator.h>
#include <duye/stl/inc/duye_stl_node.h>

DUYE_STL_NS_BEG

// brief : stl list implemention
//	
// usage :
template <typename T>
class List 
{
public:
    typedef _Iterator<T> Iterator;
    
public:
	List() : m_count(0), m_head(NULL), m_tail(NULL) {}

    Iterator 
	void PushBack(const Item& item);
	void PushFront(const Item& item);

    T& GetBack();
    T& GetFront();
    
	void RemoveBack();
	void RemoveFront();	

private:
    D_UInt32    m_count;
    Node<T>*    m_head;     
    Node<T>*    m_tail;
}; 

DUYE_STL_NS_END

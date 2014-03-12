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

#include <duye/dstl/inc/duye_stl_def.h>
#include <duye/dstl/vector/inc/duye_bytemem.h>
#include <duye/dstl/vector/inc/duye_stl_iterator.h>
#include <duye/dstl/vector/inc/duye_stl_node.h>

DUYE_STL_NS_BEG

// brief : stl list implemention
//	
// usage :
//  List<int> MyList;
//  List<int>::Iterator iter = MyList.BegIter();
//  for (; iter.IsEnd(); ++iter)
//  {
//      // TBD
//  }
template <typename T>
class List 
{
public:
    typedef _Iterator<T> Iterator;
    
public:
	List() : m_count(0), m_head(NULL), m_tail(NULL) {}

    // brief : return the begin of iterator
    Iterator& BegIter()
    {
        m_iter = m_head;
        return m_iter;
    }

    // brief : return the end of iterator
    Iterator& EndIter()
    {
        m_iter = m_tail->GetNext();
        return m_iter;
    }

    // brief : insert a node at the back of list
	void PushBack(const T& item)
	{
	        
	}

	// brief : insert a node at the front of list
	void PushFront(const T& item)
	{
	}

    // brief : return the reference of the last node
    T& GetBack()
    {
    }

    // brief : return the reference of the first node
    T& GetFront()
    {
    }

    // brief : remove the last node
	void RemoveBack()
	{
	}

	// brief : remove the frist node
	void RemoveFront()
	{
	}

    // brief : clear the all node
	void Clear()
	{
	}

	// brief : get the count of list
	D_UInt32 Size()
	{
	    return m_count;
	}

	// brief : sort the list
	void Sort()
	{
	}

	// brief : delete a node 
	Iterator erase(const Iterator& iter)
	{
	    return ++iter;
	}

	// brief : insert a node to the list
	Iterator Insert(Iterator& pos, const T& value)
	{
	    return ++pos;    
	}

private:
    D_UInt32    m_count;
    Node<T>*    m_head;     
    Node<T>*    m_tail;
    Iterator    m_iter;
}; 

DUYE_STL_NS_END

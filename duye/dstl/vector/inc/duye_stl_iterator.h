/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_stl_iterator.h
* @version     
* @brief      
* @author   duye
* @date     2014-01-12
* @note 
*
*  1. 2014-01-12 duye Created this file
* 
*/
#pragma once

#include <duye/dstl/inc/duye_stl_def.h>
#include <duye/dstl/vector/inc/duye_stl_node.h>

DUYE_STL_NS_BEG

// brief : iterator
//	
// usage :
template <typename T>
class _Iterator
{
public:
    _Iterator() : m_node(NULL) {}
    explicit _Iterator(Node<T>* node) : m_node(node) {}
    _Iterator(const _Iterator& iter) : m_node(iter.m_node) {}

    // brief : whether is end
    bool IsEnd()
    {
        return (m_node == NULL ? true : false);
    }

    // brief : get data reference
    T& operator*() 
    { 
        return m_node->GetData(); 
    }

    // brief : get data const referenced
    const T& operator*() const 
    { 
        return m_node->GetData(); 
    }

    // brief : get data pointer
    T* operator->() const 
    { 
        return &m_node->GetData(); 
    }

    // brief : prefix ++ rewrite
    _Iterator& operator++()  
    { 
        m_node = m_node->GetNext();
        return (*this); 
    }

    // brief : postfix rewrite
    _Iterator operator++(int) 
    { 
        _Iterator currIter = *this;
        m_node = m_node->GetNext();
        return currIter;
    }

    // brief : prefix -- rewrite
    _Iterator& operator--() 
    { 
        m_node = m_node->GetPrev();
        return (*this); 
    }

    // brief : postfix -- rewrite
    _Iterator operator--(int) 
    {
        _Iterator currIter = *this;
        m_node = m_node->GetPrev();
        return currIter;
    }

    bool operator==(const _Iterator& other) const 
    {
        return m_node == other.m_node;
    }
    
    bool operator!=(const _Iterator& other) const 
    {
        return m_node != other.m_node;
    }
    
    void operator=(const _Iterator& other) 
    {
        m_node = other.m_node;
    }
    
    void operator=(Node<T>* node) 
    {
        m_node = node;
    }
        
private:
    Node<T>* m_node;
};

DUYE_STL_NS_END

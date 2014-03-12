/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file		duye_stl_node.h
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

DUYE_STL_NS_BEG

// brief : node for list
//	
// usage :
template <typename T>
class Node
{
public:
    explicit Node(const T& data) : m_data(data), m_next(NULL), m_prev(NULL) {}

    void SetData(const T& data) 
    { 
        m_data = data; 
    }
    
    const T& GetData() const 
    { 
        return m_data; 
    }
    
    T& GetData() 
    { 
        return m_data; 
    }

    void SetNext(Node* next) 
    { 
        m_next = next; 
    }
    
    Node* GetNext() 
    { 
        return m_next; 
    }

    void SetPrev(Node* prev) 
    { 
        m_prev = prev; 
    }
    
    Node* GetPrev() 
    { 
        return m_prev; 
    }

private:
    T       m_data;
    Node*   m_next;
    Node*   m_prev;
};

DUYE_STL_NS_END
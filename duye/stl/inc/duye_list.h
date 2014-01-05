/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
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

DUYE_STL_NS_BEG

template <typename T>
class List 
{
public:
	List() {}
	~List() {}

	void PushBack(T item);

private:
};

template <typename T>
void List<T>::PushBack(T item)
{
	
}

DUYE_STL_NS_END

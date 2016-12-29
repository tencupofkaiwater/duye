/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_list.h
* @version     
* @brief      
* @author   duye
* @date     2016-12-28
* @note 
*
*  1. 2016-12-28 duye created this file
* 
*/
#pragma once

#include <list>
#include <duye_type.h>

namespace duye {

/** 
 * @brief list class template
 */
template<typename T>
class List {
public:
    List();
    List(const T& var1);
    List(const T& var1, const T& var2);
    List(const T& var1, const T& var2, const T& var3);
    List(const T& var1, const T& var2, const T& var3, const T& var4);
    List(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5);
    List(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6);
    List(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6, const T& var7);
    List(const T& var1, const T& var2, const T& var3, const T& var4, 
    	const T& var5, const T& var6, const T& var7, const T& var8);
	List(const T& var1, const T& var2, const T& var3, const T& var4, 
    	const T& var5, const T& var6, const T& var7, const T& var8, const T& var9);
    ~List();

    void pushBack(const T& t);
    uint32 size();
    bool empty();
    const std::list<T>& getList() const;

private:
	std::list<T> m_list;
};

template<typename T>
List<T>::List() {
}

template<typename T>
List<T>::List(const T& var1) {
	m_list.push_back(var1);
}

template<typename T>
List<T>::List(const T& var1, const T& var2) {
	m_list.push_back(var1);
	m_list.push_back(var2);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3, const T& var4) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
	m_list.push_back(var4);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
	m_list.push_back(var4);
	m_list.push_back(var5);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
	m_list.push_back(var4);
	m_list.push_back(var5);
	m_list.push_back(var6);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6, const T& var7) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
	m_list.push_back(var4);
	m_list.push_back(var5);
	m_list.push_back(var6);
	m_list.push_back(var7);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3, const T& var4, 
	const T& var5, const T& var6, const T& var7, const T& var8) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
	m_list.push_back(var4);
	m_list.push_back(var5);
	m_list.push_back(var6);
	m_list.push_back(var7);
	m_list.push_back(var8);
}

template<typename T>
List<T>::List(const T& var1, const T& var2, const T& var3, const T& var4, 
	const T& var5, const T& var6, const T& var7, const T& var8, const T& var9) {
	m_list.push_back(var1);
	m_list.push_back(var2);
	m_list.push_back(var3);
	m_list.push_back(var4);
	m_list.push_back(var5);
	m_list.push_back(var6);
	m_list.push_back(var7);
	m_list.push_back(var8);
	m_list.push_back(var9);
}

template<typename T>
List<T>::~List() {
}

template<typename T>
void List<T>::pushBack(const T& t) {
	m_list.push_back(t);
}

template<typename T>
uint32 List<T>::size() {
	return m_list.size();
}

template<typename T>
bool List<T>::empty() {
	return m_list.size() == 0;
}

template<typename T>
const std::list<T>& List<T>::getList() const
	return m_list;
}
/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_vector.h
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

#include <vector>

namespace duye {

/** 
 * @brief Vector class template
 */
template<typename T>
class Vector {
public:
    Vector();
    Vector(const T& var1);
    Vector(const T& var1, const T& var2);
    Vector(const T& var1, const T& var2, const T& var3);
    Vector(const T& var1, const T& var2, const T& var3, const T& var4);
    Vector(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5);
    Vector(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6);
    Vector(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6, const T& var7);
    Vector(const T& var1, const T& var2, const T& var3, const T& var4, 
    	const T& var5, const T& var6, const T& var7, const T& var8);
	Vector(const T& var1, const T& var2, const T& var3, const T& var4, 
    	const T& var5, const T& var6, const T& var7, const T& var8, const T& var9);
    ~Vector();

    void pushBack(const T& t);
    uint32 size();
    bool empty();
    //const std::vector<T>& getVector() const;
	T operator [] (uint32 index) const {
		T t;
		if (index >= m_vector.size()) {
			return t;
		}
		
		return m_vector[index];
	}    

private:
	std::vector<T> m_vector;
};

template<typename T>
Vector<T>::Vector() {
}

template<typename T>
Vector<T>::Vector(const T& var1) {
	m_vector.push_back(var1);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3, const T& var4) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
	m_vector.push_back(var4);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
	m_vector.push_back(var4);
	m_vector.push_back(var5);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
	m_vector.push_back(var4);
	m_vector.push_back(var5);
	m_vector.push_back(var6);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3, const T& var4, const T& var5, const T& var6, const T& var7) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
	m_vector.push_back(var4);
	m_vector.push_back(var5);
	m_vector.push_back(var6);
	m_vector.push_back(var7);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3, const T& var4, 
	const T& var5, const T& var6, const T& var7, const T& var8) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
	m_vector.push_back(var4);
	m_vector.push_back(var5);
	m_vector.push_back(var6);
	m_vector.push_back(var7);
	m_vector.push_back(var8);
}

template<typename T>
Vector<T>::Vector(const T& var1, const T& var2, const T& var3, const T& var4, 
	const T& var5, const T& var6, const T& var7, const T& var8, const T& var9) {
	m_vector.push_back(var1);
	m_vector.push_back(var2);
	m_vector.push_back(var3);
	m_vector.push_back(var4);
	m_vector.push_back(var5);
	m_vector.push_back(var6);
	m_vector.push_back(var7);
	m_vector.push_back(var8);
	m_vector.push_back(var9);
}

template<typename T>
Vector<T>::~Vector() {
}

template<typename T>
void Vector<T>::pushBack(const T& t) {
	m_vector.push_back(t);
}

template<typename T>
uint32 Vector<T>::size() {
	return m_vector.size();
}

template<typename T>
bool Vector<T>::empty() {
	return m_vector.size() == 0;
}

/*
template<typename T>
const std::vector<T>& Vector<T>::getVector() const
	return m_vector;
}
*/
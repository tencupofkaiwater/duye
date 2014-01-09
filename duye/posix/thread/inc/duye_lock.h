/***************************************************************************
**  
*    @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
/**
* @file	    duye_lock.h
* @version     
* @brief      
* @author   duye
* @date     2013-11-26
* @note 
*
* 3. 2014-01-09 duye Add comments
* 
* 2. 2014-01-04 duye 
* 	a. Modify Mutex function TryLock to Trylock()
* 	b. Add function Trylock() for class OrgLock
* 	c. Modify TryLock class implimenting
*
* 1. 2013-11-26 duye Created this file
*/

#pragma once

#include <pthread.h>
#include <unistd.h>

#include <duye/posix/inc/duye_posix_def.h> 

DUYE_POSIX_NS_BEG

// brief:
//  POSIX 互斥变量封装
//	
// usage:
//	Mutex mutex;
//  mutex.Lock();
//  mutex.Trylock();
//  mutex.Unlock();
class Mutex
{
public:
	// brief:
	//  无参构造函数
	// @para
	// @return 
	// note:
	//  默认锁类型PTHREAD_MUTEX_RECURSIVE
	Mutex();
	
	// brief:
	//  带参构造函数
	// @para [in] kind 锁类型
	// @return 
	// note:
	//  有四种锁类型:PTHREAD_MUTEX_NORMAL、PTHREAD_MUTEX_RECURSIVE
	//  PTHREAD_MUTEX_ERRORCHECK、PTHREAD_MUTEX_DEFAULT
	explicit Mutex(const D_Int32 kind);
	~Mutex();

	// brief:
	//  对互斥变量加锁，进入等待队列
	// @para 
	// @return true/false
	// note:
	bool Lock();

	// brief:
	//  尝试对互斥变量加锁，失败后立马返回
	// @para 
	// @return true/false
	// note:	
	bool Trylock();

	// brief:
	//  释放互斥变量，Lock()和Trylock()的反操作
	// @para 
	// @return true/false
	// note:	
	bool Unlock();

private:
	// brief:
	//  防止拷贝，仅声明不实现
	// @para 
	// @return 
	// note:
	Mutex(const Mutex&); 
	void operator=(const Mutex&);	

	// brief:
	//  初始化互斥变量
	// @para 
	// @return
	// note:	
	void Init(const D_Int32 kind);
    
private:
    // 系统互斥变量
	pthread_mutex_t	m_mutex;	
};

// brief:
//  对Mutex封装成原始锁
//	
// usage:
//	OrgLock orgLock;
//  orgLock.Lock();
//  orgLock.Trylock();
//  orgLock.Unlock();
class OrgLock
{
public:
	// brief:
	//  无参构造函数
	// @para
	// @return 
	// note:
	//  默认锁类型PTHREAD_MUTEX_RECURSIVE
	OrgLock();
	
	// brief:
	//  带参构造函数
	// @para [in] kind 锁类型
	// @return 
	// note:
	//  有四种锁类型:PTHREAD_MUTEX_NORMAL、PTHREAD_MUTEX_RECURSIVE
	//  PTHREAD_MUTEX_ERRORCHECK、PTHREAD_MUTEX_DEFAULT	
	explicit OrgLock(const D_Int32 kind);
	virtual ~OrgLock();

	// brief:
	//  加锁，进入等待队列
	// @para 
	// @return true/false
	// note:
	bool Lock();

	// brief:
	//  尝试加锁，失败后立马返回
	// @para 
	// @return true/false
	// note:	
	bool Trylock();

	// brief:
	//  释放锁，Lock()和Trylock()的反操作
	// @para 
	// @return true/false
	// note:		
	bool Unlock();

private:
	// brief:
	//  防止拷贝，仅声明不实现
	// @para 
	// @return 
	// note:
	OrgLock(const OrgLock&); 
	void operator=(const OrgLock&);	

private:
    // 封装后的互斥变量
	Mutex*	m_mutex;
};

// brief:
//  对Mutex封装成尝试锁
//	
// usage:
//  // static mutex
//  Mutex mutex;
//
//  void MyFun()
//  {
//      // auto release lock
//	    TryLock autoTryLock(mutex);
//      if (!autoTryLock.Lock(1000))
//      {
//          return;
//      }
//      
//      // to do
//
//      // not auto release lock
//      TryLock notAutoTryLock(mutex, false);
//      if (!autoTryLock.Lock(1000))
//      {
//          notAutoTryLock.Unlock();
//          return;
//      }     
//      
//      // to do
//      
//      notAutoTryLock.Unlock();
//  }
class TryLock
{
public:
	// brief:
	//  构造函数
	// @para [in] mutex 锁的互斥变量
	// @para [in] autoUnlock 是否自动释放锁，默认自动释放
	// @return 
	// note:
	TryLock(Mutex& mutex, const bool autoUnlock = true);
	
	~TryLock();

	// brief:
	//  尝试加锁
	// @para [in] timeout 锁超时时间，默认0，表示只尝试一次，失败立刻返回
	// @return true/false
	// note:
	bool Lock(const D_UInt32 timeout = 0);

	// brief:
	//  释放锁
	// @para
	// @return true/false
	// note:如果是自动释放锁，可不用调用，就算调用也不起作用	
	bool Unlock();

private:
	// brief:
	//  防止拷贝，仅声明不实现
	// @para 
	// @return 
	// note:
	TryLock(const TryLock&); 
	void operator=(const TryLock&);	
    
private:
	Mutex&	m_mutex;
	bool	m_autoUnlock;
};

// brief:
//  对Mutex封装自动锁
//	
// usage:
//  // static mutex
//  Mutex mutex;
//
//  void MyFun()
//  {
//      // auto release lock
//	    AutoLock autoLock(mutex);
//
//      // to do
//      // 返回时，自动释放锁
//  }
class AutoLock
{
public:
	// brief:
	//  构造函数
	// @para [in] mutex 锁的互斥变量
	// @return 
	// note:
	explicit AutoLock(Mutex& mutex);
	~AutoLock();

private:
	// brief:
	//  防止拷贝，仅声明不实现
	// @para 
	// @return 
	// note:
	AutoLock(const AutoLock&);
	void operator=(const AutoLock&);

private:
	Mutex& m_mutex;
};

DUYE_POSIX_NS_END

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
//  POSIX ���������װ
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
	//  �޲ι��캯��
	// @para
	// @return 
	// note:
	//  Ĭ��������PTHREAD_MUTEX_RECURSIVE
	Mutex();
	
	// brief:
	//  ���ι��캯��
	// @para [in] kind ������
	// @return 
	// note:
	//  ������������:PTHREAD_MUTEX_NORMAL��PTHREAD_MUTEX_RECURSIVE
	//  PTHREAD_MUTEX_ERRORCHECK��PTHREAD_MUTEX_DEFAULT
	explicit Mutex(const D_Int32 kind);
	~Mutex();

	// brief:
	//  �Ի����������������ȴ�����
	// @para 
	// @return true/false
	// note:
	bool Lock();

	// brief:
	//  ���ԶԻ������������ʧ�ܺ�������
	// @para 
	// @return true/false
	// note:	
	bool Trylock();

	// brief:
	//  �ͷŻ��������Lock()��Trylock()�ķ�����
	// @para 
	// @return true/false
	// note:	
	bool Unlock();

private:
	// brief:
	//  ��ֹ��������������ʵ��
	// @para 
	// @return 
	// note:
	Mutex(const Mutex&); 
	void operator=(const Mutex&);	

	// brief:
	//  ��ʼ���������
	// @para 
	// @return
	// note:	
	void Init(const D_Int32 kind);
    
private:
    // ϵͳ�������
	pthread_mutex_t	m_mutex;	
};

// brief:
//  ��Mutex��װ��ԭʼ��
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
	//  �޲ι��캯��
	// @para
	// @return 
	// note:
	//  Ĭ��������PTHREAD_MUTEX_RECURSIVE
	OrgLock();
	
	// brief:
	//  ���ι��캯��
	// @para [in] kind ������
	// @return 
	// note:
	//  ������������:PTHREAD_MUTEX_NORMAL��PTHREAD_MUTEX_RECURSIVE
	//  PTHREAD_MUTEX_ERRORCHECK��PTHREAD_MUTEX_DEFAULT	
	explicit OrgLock(const D_Int32 kind);
	virtual ~OrgLock();

	// brief:
	//  ����������ȴ�����
	// @para 
	// @return true/false
	// note:
	bool Lock();

	// brief:
	//  ���Լ�����ʧ�ܺ�������
	// @para 
	// @return true/false
	// note:	
	bool Trylock();

	// brief:
	//  �ͷ�����Lock()��Trylock()�ķ�����
	// @para 
	// @return true/false
	// note:		
	bool Unlock();

private:
	// brief:
	//  ��ֹ��������������ʵ��
	// @para 
	// @return 
	// note:
	OrgLock(const OrgLock&); 
	void operator=(const OrgLock&);	

private:
    // ��װ��Ļ������
	Mutex*	m_mutex;
};

// brief:
//  ��Mutex��װ�ɳ�����
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
	//  ���캯��
	// @para [in] mutex ���Ļ������
	// @para [in] autoUnlock �Ƿ��Զ��ͷ�����Ĭ���Զ��ͷ�
	// @return 
	// note:
	TryLock(Mutex& mutex, const bool autoUnlock = true);
	
	~TryLock();

	// brief:
	//  ���Լ���
	// @para [in] timeout ����ʱʱ�䣬Ĭ��0����ʾֻ����һ�Σ�ʧ�����̷���
	// @return true/false
	// note:
	bool Lock(const D_UInt32 timeout = 0);

	// brief:
	//  �ͷ���
	// @para
	// @return true/false
	// note:������Զ��ͷ������ɲ��õ��ã��������Ҳ��������	
	bool Unlock();

private:
	// brief:
	//  ��ֹ��������������ʵ��
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
//  ��Mutex��װ�Զ���
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
//      // ����ʱ���Զ��ͷ���
//  }
class AutoLock
{
public:
	// brief:
	//  ���캯��
	// @para [in] mutex ���Ļ������
	// @return 
	// note:
	explicit AutoLock(Mutex& mutex);
	~AutoLock();

private:
	// brief:
	//  ��ֹ��������������ʵ��
	// @para 
	// @return 
	// note:
	AutoLock(const AutoLock&);
	void operator=(const AutoLock&);

private:
	Mutex& m_mutex;
};

DUYE_POSIX_NS_END

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
*  1. 2013-11-26 duye Created this file
* 
*/

#pragma once

#include <pthread.h>
#include <unistd.h>

#include <duye/posix/inc/duye_posix_def.h> 

DUYE_POSIX_NS_BEG

class Mutex
{
public:
	Mutex();
	explicit Mutex(const Int32_t kind);
	~Mutex();

	bool Lock();
	bool TryLock();
	bool Unlock();

private:
	Mutex(const Mutex&); 
	void operator=(const Mutex&);	
	void Init(const Int32_t kind);
    
private:
	pthread_mutex_t	m_mutex;	
};

// Thread lock
//
class OrgLock
{
public:
    OrgLock();
    explicit OrgLock(const Int32_t kind);
    virtual ~OrgLock();

	bool Lock();
	bool Unlock();

private:
	OrgLock(const OrgLock&); 
	void operator=(const OrgLock&);	

private:
	Mutex*	m_mutex;
};

// Try lock
//
class TryLock
{
public:
	explicit TryLock(const bool autoUnlock = true);
    TryLock(const Int32_t kind, const bool autoUnlock = true);
	~TryLock();

	// lock
	// @timeout, try lock time out, millisecond
	bool Lock(const UInt32_t timeout = 0);
	bool Unlock();

private:
	TryLock(const TryLock&); 
	void operator=(const TryLock&);	
    
private:
	Mutex*	m_mutex;
	bool	m_autoUnlock;
};

// Auto lock 
//
class AutoLock
{
public:
	AutoLock();
    explicit AutoLock(const Int32_t kind);
	~AutoLock();

private:
	AutoLock(const AutoLock&);
	void operator=(const AutoLock&);

private:
	Mutex* m_mutex;
};

DUYE_POSIX_NS_END

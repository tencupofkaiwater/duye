/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_shm.cpp
* @version     
* @brief      
* @author   duye
* @date	    2014-02-22
* @note 
*
*  2. 2014-06-21 duye move to gohoop 
*  1. 2014-02-22 duye Created this file
* 
*/
#include <duye_shm.h>

namespace duye {

// default shm size is 10M
static const uint64 DEF_SHM_SIZE = 1024 * 1024 * 10;

Shm::Shm() : m_shmSize(0), m_shmAddr(NULL), m_initFlags(false)
{
    m_shmPath[0] = 0;
}

Shm::~Shm()
{
    uninit();    
}

bool Shm::init(const int8* shmPath, const uint64 shmSize)
{
    if (m_initFlags)
    {
    	return false;
    }

    uint32 len = strlen(shmPath);
	if (len == 0 || len >= PATH_MAX)
	{
		return false;
	}
	
    memcpy(m_shmPath, shmPath, len);
    m_shmPath[len] = 0;	
	m_shmSize = shmSize;

    int32 fd = ::open(m_shmPath, O_RDWR | O_CREAT);
    if (fd < 0)
    {
    	return false;
    }

    // setting file size
    if (m_shmSize == 0)
    {
    	m_shmSize = DEF_SHM_SIZE;   
    }

    ftruncate(fd, m_shmSize);
    m_shmAddr = mmap(NULL, m_shmSize, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (m_shmAddr == MAP_FAILED)
    {
    	close(fd);
    	return false;
    }

    close(fd);
    m_initFlags = true;
	
    return true;
}

const int8* Shm::path() const
{
	return (int8*)m_shmPath;
}

uint64 Shm::size() const
{
	return m_shmSize;
}
     
bool Shm::sync()
{
    if (!m_initFlags)
    {
    	return false;
    }

    if (msync(m_shmAddr, m_shmSize, MS_SYNC) < 0)
    {
    	return SYNC_SHM_FAILED;
    }

    return true;    
} 
 
bool Shm::write(const uint32 offset, const int8* data, const uint32 length)
{
    if (!m_initFlags)
    {
    	return false;
    } 

    if (data == NULL)
    {
    	return WRITE_SHM_PARA_FAILED;
    }

    if (length == 0)
    {
    	return WRITE_SHM_PARA_FAILED;
    }

    if (offset + length > m_shmSize)
    {
    	return WRITE_SHM_PARA_FAILED;
    }

    memcpy((int8*)m_shmAddr + offset, data, length);
    return true;        
}

bool Shm::read(const uint32 offset, int8* buffer, const uint32 size)
{
    if (!m_initFlags)
    {
    	return false;
    } 

    if (buffer == NULL)
    {
    	return WRITE_SHM_PARA_FAILED;
    }

    if (size == 0)
    {
    	return WRITE_SHM_PARA_FAILED;
    }

    if (offset + size > m_shmSize)
    {
    	return WRITE_SHM_PARA_FAILED;
    }

    memcpy((int8*)buffer, (int8*)m_shmAddr + offset, size);
    return true;     
}
    
bool Shm::uninit()
{
    if (!m_initFlags)
    {
    	return false;
    }

    if (munmap(m_shmAddr, m_shmSize) < 0)
    {
    	return MUNMAP_SHM_FAILED;
    }

    m_shmAddr = NULL;
    m_initFlags = false;
	
    return true;
}
}

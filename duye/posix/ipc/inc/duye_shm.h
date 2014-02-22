/*************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_shm.h
* @version     
* @brief      
* @author   duye
* @date     2014-02-22
* @note 
*
*  1. 2014-02-22 duye Created this file
* 
*/

#pragma once

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <duye/posix/inc/duye_posix_def.h>

DUYE_POSIX_NS_BEG 

// brief : shared memory for ipc
// 
class Shm
{
public:
    Shm();
    Shm(const D_Int8* path, const D_UInt32 size);
    ~Shm();

    D_Bool Init()
    {
    	D_Int32 fd = open(path, O_RDWR | O_CREAT);
    	if (fd < 0)
    	{
    		return false;
    	}

        ftruncate(fd, shmFileSize);
    	m_pShmAddr = mmap(NULL, shmFileSize, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    	if (m_pShmAddr == MAP_FAILED)
    	{
    	    close(fd);
    		BSTM_DEBUG_ERROR(SHM_LOG, "Out %s, shm server init failed(m_pShmAddr == MAP_FAILED). \n", __FUNCTION__);
    		return false;
    	}

        close(fd);
        
    	m_shmSize = shmFileSize;

    	BSTM_DEBUG_DEBUG(SHM_LOG, "Out %s \n", __FUNCTION__);

    	return true;    
    }
    
	bool Uninit()
    {
        return !(munmap(m_pShmAddr, m_shmSize) < 0);
    }

    bool Sync()
    {
        return !(msync(m_pShmAddr, m_shmSize, MS_SYNC) < 0);
    } 

    virtual bool WriteData(const unsigned int offset, const char* pData, const unsigned int dataLen)
    {
        BSTM_DEBUG_DEBUG(SHM_LOG, "In %s \n", __FUNCTION__);

        BSTM_DEBUG_DEBUG(SHM_LOG, "%s, offset=%d m_shmSize=%d data=%s \n", __FUNCTION__, offset, m_shmSize, pData);
        
    	if (offset + dataLen > m_shmSize
    	    || pData == NULL)
    	{
    	    BSTM_DEBUG_ERROR(SHM_LOG, "Out %s, Failed offset + sizeof(FilterShmNode_S) > m_shmSize \n", __FUNCTION__);
    		return false;
    	}

        memcpy((char*)m_pShmAddr + offset, pData, dataLen);
        
        BSTM_DEBUG_DEBUG(SHM_LOG, "Out %s \n", __FUNCTION__);
        
        return true;        
    }

    virtual bool ReadData(const unsigned int offset, char*& pData, const unsigned int dataLen)
    {
        BSTM_DEBUG_DEBUG(SHM_LOG, "In %s \n", __FUNCTION__);

        BSTM_DEBUG_DEBUG(SHM_LOG, "%s:offset=%d m_shmSize=%d \n", __FUNCTION__, offset, m_shmSize);
        
    	if (offset + dataLen > m_shmSize)
    	{
    	    BSTM_DEBUG_ERROR(SHM_LOG, "Out %s, Failed offset + sizeof(FilterShmNode_S) > m_shmSize \n", __FUNCTION__);
    		return false;
    	}

    	pData = new char[dataLen];
        memcpy((char*)m_pShmAddr + offset, pData, dataLen);
        
    	BSTM_DEBUG_DEBUG(SHM_LOG, "Out %s \n", __FUNCTION__);

    	return true;     
    }

protected:
	void* m_pShmAddr;
	unsigned int m_shmSize;	
};

DUYE_POSIX_NS_END

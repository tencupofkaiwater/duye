/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_shm.h
* @version     
* @brief      
* @author   duye
* @date	    2014-02-22
* @note 
*
*  2. 2014-06-20 duye move to gohoop project 
*  1. 2014-02-22 duye Created this file
* 
*/
#pragma once

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <duye_type.h>

namespace duye {
	
/** 
 * @brief shm error code
 */
typedef enum 
{ 
    /** 
     * @brief open shm failed
     */        
    OPEN_SHM_FAILED = -2,
    /** 
     * @brief munmap failed
     */           
    MUNMAP_SHM_FAILED = -3,
    /** 
     * @brief mmap failed
     */           
    MMAP_SHM_FAILED = -4,
    /** 
     * @brief sync shm failed
     */           
    SYNC_SHM_FAILED = -5,
    /** 
     * @brief write shm parameter failed
     */           
    WRITE_SHM_PARA_FAILED = -6,
    /** 
     * @brief read shm parameter failed
     */           
    READ_SHM_PARA_FAILED = -7,
    /** 
     * @brief shm not init
     */           
    SHM_NO_INIT = -8,
    /** 
     * @brief shm path is empty
     */           
    SHM_PATH_EMPTY = -9
} ShmErrorCode;

/** 
 * @brief shared memory for ipc
 */
class Shm
{
public:
    Shm();    
    ~Shm();

    /**
     * @brief constructor
     * @param [in] shmPath : shm mapping file path
     * @param [in] shmSize : shm size
     * @return true/false
     * @note 
     */	 	
    bool init(const int8* shmPath, const uint64 shmSize); 

	/**
     * @brief get shm path
     * @return shm path  
     * @note 
     */	
    const int8* path() const;

	/**
     * @brief get shm size
     * @return shm size  
     * @note 
     */	
    uint64 size() const;	

    /**
     * @brief sync the shm
     * @return true/false  
     * @note 
     */	
    bool sync();

    /**
     * @brief write data to shm
     * @param [in] offset : offset of shm
     * @param [in] data : input data
     * @param [in] size : write size     
     * @return true/false  
     * @note 
     */		
    bool write(const uint32 offset, const int8* data, const uint32 length);

    /**
     * @brief read data from shm
     * @param [in] offset : offset of shm
     * @param [in] buffer : output buffer
     * @param [in] size : read size    
     * @return true/false  
     * @note 
     */	
    bool read(const uint32 offset, int8* buffer, const uint32 size);

private:
    /**
     * @brief uninit the shm
     * @return true/false  
     * @note 
     */	 	
    bool uninit();

private:
    int8     m_shmPath[PATH_MAX];
    uint64   m_shmSize;	
    void*    m_shmAddr;
    bool     m_initFlags;
};
}

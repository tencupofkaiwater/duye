/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_file_stream.h
* @version     
* @brief      
* @author   duye
* @date     2016-04-01
* @note 
*
*  1. 2016-04-01 duye Created this file
* 
*/
#pragma once

#include <string>
#include <duye_type.h>
#include <duye_file.h>
#include <duye_lock.h>

namespace duye {

// 10M
static const uint32 FILE_CACHE_SIZE = 10*1024*1024;

class FileAttr
{
public:
    FileAttr() : size(0) {}

    std::string     name; 
    std::string     path; // full path
    std::string     md5;  
    uint32          size;
};

/**
 * @brief configuration manager class
 */
class FileStream
{
public:
    FileStream();
    ~FileStream();

    /**
     * @breif init
     * @param [in] path : file full path
     * @return true/false
     */    
    bool initStream(const std::string& path); 
    
    /**
     * @breif write data to file back
     * @param [in] data : in data 
     * @param [in] len : in data size
     * @return true/false
     */
    bool writeStream(const int8* data, const uint32 len); 

    /**
     * @breif push data to file back
     * @param [out] buffer : out buffer
     * @param [in] size : out buffer size
     * @param [in] offset : read offset from file begin. default is -1, indicate read current file position
     * @return pop size. on -1, error. on 0, reach end. on > 0, pop size.
     */
    int64 readStream(int8* buffer, const uint32 size, const int64 offset = -1);    

    /**
     * @breif get file attribute
     * @return true/false
     */
    const FileAttr& fileAttr() const;

    /**
     * @breif write cache data to device 
     * @return true/false
     */
    bool flush();
    
private:
    File       m_fileOp;
    FileAttr   m_fileAttr;
    uint64     m_currSize;
    uint64     m_cacheOffset;
    int8       m_cache[FILE_CACHE_SIZE];
    Mutex      m_cacheMutex;
};
}

/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_file_stream.cpp
* @version     
* @brief      
* @author   duye
* @date     2016-04-01
* @note 
*
*  1. 2016-04-01 duye Created this file
*/

#include <string.h>
#include <duye_lock.h>
#include <duye_helper.h>
#include <duye_logger.h>
#include <duye_file_stream.h>

static const int8* DUYE_LOG_PREFIX = "duyezero.public.filestream";

namespace duye {

FileStream::FileStream() : m_currSize(0), m_cacheOffset(0) {}
FileStream::~FileStream() {}

bool FileStream::initStream(const std::string& path)
{
    if (!m_fileOp.open(path.c_str(), OPEN_RDWR))
    {
        DUYE_ERROR("m_fileOp.open(%s) failed", path.c_str());
        return false;
    }

    m_fileAttr.name = StrHelper::basename(path);
    m_fileAttr.path = path;
    m_fileAttr.md5 = AlgHelper::md5Bytes(path.c_str(), path.length());
    m_fileAttr.size = m_fileOp.size();
     
    return true;
}

bool FileStream::writeStream(const int8* data, const uint32 len)
{
    if (data == NULL || len == 0)
    {
        DUYE_ERROR("data == NULL || len == 0");
        return false;
    }

    if (len >=  FILE_CACHE_SIZE)
    {
        int64 size = m_fileOp.write(data, len);
        if (size != len)
        {
            DUYE_ERROR("m_fileOp.write(), size != len");
            return false;     
        }
        
        return true;
    }

    AutoLock autoLock(m_cacheMutex);
    if (FILE_CACHE_SIZE - m_cacheOffset <= len)
    {
        if (!flush())
        {
            DUYE_ERROR("flush() failed");
            return false;
        }
    }

    memcpy(m_cache + m_cacheOffset, data, len);
    m_cacheOffset += len;
    
    return true;
}

int64 FileStream::readStream(int8* buffer, const uint32 size, const int64 offset)
{
    if (buffer == NULL || size == 0)
    {
        DUYE_ERROR("buffer == NULL || size == 0");
        return -1;    
    }

    if (offset >= 0)
    {        
        if (m_fileOp.seek(offset, D_SEEK_BEG) < 0)
        {
            DUYE_ERROR("m_fileOp.seek() failed");
            return -1;
        }
    }

    return m_fileOp.read(buffer, size);
}

const FileAttr& FileStream::fileAttr() const
{
    return m_fileAttr;
}

bool FileStream::flush()
{
    AutoLock autoLock(m_cacheMutex);
    int64 size = m_fileOp.write(m_cache, m_cacheOffset);
    if (size != (int64)m_cacheOffset)
    {
        DUYE_ERROR("m_fileOp.write(), size != (int64)m_cacheOffset");
        return false; 
    }
    
    m_cacheOffset = 0;
    
    return true;
}

}

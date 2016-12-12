/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_file.cpp
* @version     
* @brief      
* @author   duye
* @date	    2013-06-20
* @note
*
*  1. 2013-06-20 duye Created this file
* 
*/
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <duye_file.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.system.file";

// default create file permissions
static const uint32 FILE_MASK = 0x775;

bool FileUtil::createFile(const int8* filePath, const uint64& initSize)
{
    int32 fd = ::creat(filePath, FILE_MASK);
    if (fd == -1)
    {
    	return false;
    }

	if (initSize != 0)
	{
	    if (ftruncate(fd, initSize) == -1)
	    {
	    	::close(fd);
	    	return false;
	    }
	}

    ::close(fd);

    return true;
}

bool FileUtil::createDir(const int8* dirPath) {
	return System::shell("mkdir -p %s", dirPath) == 0;
}

bool FileUtil::isExist(const int8* filePath)
{
    if (filePath == NULL)
    {
    	return false;
    }
    
    if (access(filePath, F_OK) != 0)
    {
    	return false;
    }

    return true;
}

bool FileUtil::removeFile(const int8* filePath)
{
    if (filePath == NULL)
    {
    	return false;
    }

	remove(filePath);
	return true;
}

uint64 FileUtil::fileSize(const std::string& filePath)
{
	FILE* fp = fopen(filePath.c_str(), "r");
	if (!fp) return 0;
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

File::File() : m_fd(-1), m_flags(0), m_pathLen(0)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);
    m_path[0] = 0;		
}

File::File(const int8* filePath) : m_fd(-1), m_flags(0), m_pathLen(0)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);	
    setFilePath(filePath);   
}

File::~File() 
{
    close();
}

bool File::open(const FileOpenFlags fileOpenFlags)
{
    return open(fileOpenFlags, FILE_MASK);          
}

bool File::open(const int8* filePath, const FileOpenFlags fileOpenFlags)
{   
    setFilePath(filePath);
    return open(fileOpenFlags, FILE_MASK);
}

bool File::open(const FileOpenFlags fileOpenFlags, const int32 mode)
{
    int32 openFlags = 0;
    if (fileOpenFlags | OPEN_READ)
    {
    	openFlags = O_RDONLY;
    }
    else if (fileOpenFlags | OPEN_WRITE)
    {
        openFlags = O_WRONLY | O_CREAT;
    }
    else if (fileOpenFlags | OPEN_RDWR)
    {
    	openFlags = O_RDWR | O_CREAT;        
    }
    else if (fileOpenFlags | OPEN_APPEND)
    {
    	if (openFlags == 0)
    	{
            return false;
    	}
        openFlags |= O_APPEND;
    }

    if (openFlags == 0)
    {
    	ERROR_DUYE_LOG("input open mode error");
    	return false;
    }

    return orgOpen(openFlags, mode);          
}

bool File::open(const int8* filePath, const FileOpenFlags fileOpenFlags, const int32 fileOpenMode)
{
    setFilePath(filePath);
    return open(fileOpenFlags, fileOpenMode);
}

bool File::close()
{
    if (m_fd < 0)
    {
        ERROR_DUYE_LOG("file don't open");
        return false;
    }

    bool ret = (::close(m_fd) != -1 ? true : false);

    m_fd = -1;
    m_path[0] = 0;
    m_flags = 0;

    return ret;
}

uint64 File::size()
{
    if (m_fd <= 0)
    {
    	ERROR_DUYE_LOG("file don't open");
    	return false;
    } 

    struct stat	fileStat;
    fstat(m_fd, &fileStat); 

    return (uint64)(fileStat.st_size);
}

int64 File::seek(const int64 offset, const FileSeekFlags& flags)
{
    if (m_fd <= 0)
    {
    	ERROR_DUYE_LOG("file don't open");
    	return false;
    }  

    int32 sysFlags = -1;

    switch(flags)
    {
	case D_SEEK_BEG:
            sysFlags = SEEK_SET;
            break;
	case D_SEEK_CUR:
            sysFlags = SEEK_CUR;
            break;
	case D_SEEK_END:
            sysFlags = SEEK_END;
            break;
	default:
	    return false;
	    break;
    }

    return ::lseek(m_fd, offset, sysFlags);
}

int64 File::tell()
{
    return seek(0, D_SEEK_CUR);
}

int64 File::read(int8* buffer, const uint64 size)
{
    if (buffer == NULL || size <= 0)
    {
    	ERROR_DUYE_LOG("input parameter is error");
    	return false;        
    }

    if (m_fd <= 0)
    {
    	ERROR_DUYE_LOG("file don't open");
    	return false;
    }

    return ::read(m_fd, buffer, size);
}

int64 File::write(const int8* data, const uint64 length)
{
    if (data == NULL || length <= 0)
    {
    	ERROR_DUYE_LOG("input parameter is error");
    	return false;        
    }

    if (m_fd <= 0)
    {
        ERROR_DUYE_LOG("file don't open");
        return false;
    }

    return ::write(m_fd, data, length);
}

uint8* File::error()
{
    return m_error.error;
}

bool File::orgOpen(const int32 flags, const uint32 mode)
{    
    if (m_fd > 0)
    {
    	ERROR_DUYE_LOG("file had opened");
    	return false;
    }

    if (m_pathLen == 0)
    {
    	ERROR_DUYE_LOG("hasn't set file path");
    	return false;   
    }

    m_fd = ::open(m_path, flags, mode);
    if (m_fd > 0)
    {
    	m_flags = flags;
    }
    else
    {
    	ERROR_DUYE_LOG("open file failed, check whether exist this file path");
    }

    return (m_fd != -1 ? true : false);
}

bool File::setFilePath(const int8* filePath)
{
    uint32 len = strlen(filePath);
    if (len < PATH_MAX)
    {
    	memcpy(m_path, filePath, len);
    	m_path[len] = 0;
    	m_pathLen = len;
    }    

    return true;
}

}

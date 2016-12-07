/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_file.h
* @version     
* @brief      
* @author   duye
* @date	    2014-06-20
* @note 
*
*  1. 2014-06-20 duye created this file
* 
*/
#pragma once

#include <sys/stat.h>

#include <duye_type.h>
#include <duye_sys.h>

namespace duye {
	
/** 
 * file open flags
 */
typedef enum
{
    OPEN_READ = 1, 
    OPEN_WRITE = 2,
    OPEN_RDWR = 4,
    OPEN_APPEND = 8
} FileOpenFlags;

/** 
 * seek flags
 */
typedef enum
{
    D_SEEK_BEG = 1,
    D_SEEK_CUR,
    D_SEEK_END
} FileSeekFlags;

/** 
 * file utility
 */
class FileUtil
{
public:
    /**
     * @brief create file.
     * @param [in] filePath : file path.
     * @param [in] initSize : initial size, default is zero. 
     * @return true/false
     * @note 
     */		
    static bool createFile(const int8* filePath, const uint64& initSize = 0); 
	
    /**
     * @brief create directory.
     * @param [in] dirPath : directory path.
     * @return true/false
     * @note 
     */	
	static bool createDir(const int8* dirPath); 
	
    /**
     * @brief judge file whether is exist.
     * @param [in] filePath : file path
     * @return true/false
     * @note 
     */	
    static bool isExist(const int8* filePath);	
	
    /**
     * @brief remove file
     * @param [in] filePath : file path
     * @return true/false
     * @note 
     */	
    static bool removeFile(const int8* filePath);
};

/** 
 * file operation wrapper
 */
class File
{
public:
    File();

    /**
     * @brief set file path
     * @param [in] filePath : file path
     * @note 
     */	    
    explicit File(const int8* filePath);
    ~File();

    /**
     * @brief open file for reading
     * @param [in] filePath : file full path
     * @param [in] fileOpenFlags : open mode flags, from type OpenFlags
     * @return true/false
     * @note 
     */		
    bool open(const FileOpenFlags fileOpenFlags);
    bool open(const int8* filePath, const FileOpenFlags fileOpenFlags);

    /**
     * @brief open file for reading
     * @param [in] filePath : file full path
     * @param [in] fileOpenFlags : open mode flags, from type OpenFlags
     * @param [in] fileOpenMode : permission
     * @return true/false
     * @note 
     */		
    bool open(const FileOpenFlags fileOpenFlags, const int32 fileOpenMode);	
    bool open(const int8* filePath, const FileOpenFlags fileOpenFlags, const int32 fileOpenMode);

    /**
     * @brief close file
     * @return true/false
     * @note 
     */		
    bool close();

    /**
     * @brief get file size  
     * @return size
     * @note 
     */			
    uint64 size();

    /**
     * @brief set file seek
     * @param [in] offset : offset
     * @param [in] flags : D_SEEK_BEG, D_SEEK_CUR, D_SEEK_END  
     * @return offset/false
     * @note 
     */			
    int64 seek(const int64 offset, const FileSeekFlags& flags = D_SEEK_BEG);	

    /**
     * @brief get file pointer offset from header
     * @return offset from file header
     * @note 
     */			
    int64 tell();

    /**
     * @brief read file
     * @param [out] buffer : output buffer
     * @param [in] size : the size of buffer     
     * @return size/-1
     * @note 
     */			
    int64 read(int8* buffer, const uint64 size);

    /**
     * @brief write file
     * @param [in] buffer : input buffer
     * @param [in] size : the size of buffer
     * @return size/-1
     * @note 
     */		
    int64 write(const int8* data, const uint64 length);

    /**
     * @brief get last error string
     * @param [out] error : output buffer
     * @param [in] size : output buffer size
     * @return true/false
     * @note 
     */		
    int8* error();	

private:
    /**
     * @brief origin API for open file
     * @param [in] flags : operation flags
     * @param [in] mode : operation mode
     * @return true/false
     * @note 
     */			
    bool orgOpen(const int32 flags, const uint32 mode);

    // set file path
    bool setFilePath(const int8* filePath);

private:
    int32   m_fd;
    int32   m_flags;
    int8    m_path[PATH_MAX];
    uint32  m_pathLen;
	Error* m_error;
};
}

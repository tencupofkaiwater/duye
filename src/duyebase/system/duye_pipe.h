/*************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_pipe.h
* @version     
* @brief      
* @autho    duye
* @date	    2013-11-15
* @note 
*
*  1. 2013-11-15 duye Created this file
* 
*/
#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <duye_type.h>

namespace duye {
	
/** 
 * @brief pipe base class, be inherited by WritePipe and ReadPipe class
 */
class Pipe
{
public:
    Pipe() {}
    virtual ~Pipe() {}

    /**
     * @brief Open the pipe
     * @param [in] pipeName : the GPipe name 
     * @return true/false
     * @note 
     */			
    virtual bool open(const int8* pipeName) = 0;

protected:
    /**
     * @brief Open the pipe
     * @param [in] pipeName : the GPipe name
     * @param [in] mode : open mode
     * @return true/false
     * @note 
     */		
    bool orgOpen(const int8* pipeName, const int32 mode);
    
protected:
    /** 
     * @brief pipe descriptor
     */	
    int32	m_pipefd;
};

/** 
 * @brief Be used to write GPipe
 */
class WritePipe : public Pipe
{
public:
    WritePipe() {}
    virtual ~WritePipe() {}

    /**
     * @brief Open the pipe
     * @param [in] GPipeName : the GPipe name
     * @return true/false
     * @note 
     */			
    virtual bool open(const int8* pipeName);	

    /**
     * @brief Write data to pipe
     * @param [in] data : write data
     * @param [in] length : data length
     * @return size/-1
     * @note 
     */		
    int64 write(const int8* data, const uint64 length);
	
private:
    /**
     * @brief prevent copying
     * @note
     */	
     WritePipe(const WritePipe&);

    /**
     * prevent copying
     * @note
     */		
    void operator=(const WritePipe&);
};

/** 
 * @brief be used to read GPipe
 */
class ReadPipe : public Pipe
{
public:
    ReadPipe() {}
    virtual ~ReadPipe() {}

    /**
     * @brief open pipe
     * @param [in] pipeName : GPipe name
     * @return true/false
     * @note 
     */    
    virtual bool open(const int8* pipeName);

    /**
     * @brief read data from pipe
     * @param [out] buffer : output buffer
     * @param [in] size : output buffer size
     * @return size/-1
     * @note 
     */  	
    int64 read(int8* buffer, const uint64 size);  

private:
    /**
     * @brief prevent copying
     * @note
     */	
    ReadPipe(const ReadPipe&);

    /**
     * @brief prevent copying
     * @note
     */		
    void operator=(const ReadPipe&);	
};
}

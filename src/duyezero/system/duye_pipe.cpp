/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_pipe.cpp
* @version     
* @brief      
* @author   duye
* @date     2013-12-1
* @note 
*
*  2. 2014-06-21 duye move to gohoop 
*  1. 2013-12-01 duye Created this file
* 
*/
#include <duye_pipe.h>

namespace duye {

bool Pipe::orgOpen(const int8* pipeName, const int32 mode)
{
    if (pipeName == NULL)
    {
        return false;
    }

    if (access(pipeName, F_OK) == -1)
    {
        if (mkfifo(pipeName, 0777) != 0)
        {
            return false;
        }
    }    

    m_pipefd = ::open(pipeName, mode);
    if (m_pipefd == -1)
    {
        return false;
    }

    return true;   
}

bool WritePipe::open(const int8* pipeName)
{
    return orgOpen(pipeName, O_WRONLY | O_NONBLOCK);          
}

int64 WritePipe::write(const int8* data, const uint64 length)
{
    if (m_pipefd == -1)
    {
        return -1;
    }

    if (data == NULL)
    {
        return -1;
    }

    if (length == 0)
    {
        return -1;        
    }    

    int64 bytes = -1;
    if ((bytes = ::write(m_pipefd, data, length)) == -1)
    {
    	return -1;
    }

    return bytes;    
}

bool ReadPipe::open(const int8* pipeName)
{
    return orgOpen(pipeName, O_RDONLY);        
}

int64 ReadPipe::read(int8* buffer, const uint64 size)
{
    if (m_pipefd == -1)
    {
    	return -1;
    }

    if (buffer == NULL)
    {
    	return -1;
    }

    if (size == 0)
    {
    	return -1;       
    }

    int32 bytes = -1;
    if ((bytes = ::read(m_pipefd, buffer, size)) == -1)
    {
    	return -1;
    }

    return bytes;    
}
}

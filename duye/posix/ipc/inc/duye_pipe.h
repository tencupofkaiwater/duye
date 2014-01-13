/*************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_pipe.h
* @version     
* @brief      
* @author   duye
* @date     2013-11-15
* @note 
*
*  1. 2013-11-15 duye Created this file
* 
*/

#pragma once

#include <duye/posix/inc/duye_posix_def.h>
#include <duye/stl/string>

DUYE_POSIX_NS_BEG 
// brief : Pipe base class, be inherited by WritePipe and ReadPipe class
// 
class Pipe
{
public:
	Pipe() {}
	virtual ~Pipe() {}
	
	// brief : Open the pipe
	// @para [in]pipeName : the pipe name
	// return : true/false
	// note
	virtual D_Bool Open(const stl::String& pipeName) = 0;
	
protected:
	// pipe descriptor
	D_Int32		m_pipefd;
};

// brief : Be used to write pipe
// usage :
//	void MyWritePipe()
//	{
// 		WritePipe writePipe;
//		if (writePipe.Open("/tmp/testFifoFile"))
//		{
//          char* data = "test data";
//		    writePipe.Write(data, strlen(data));
//		}
//	}
class WritePipe : public Pipe
{
public:
	WritePipe() {}
	virtual ~WritePipe() {}
	
	// brief : Open the pipe
	// @para [in]pipeName : pipe name
	// return : true/false
	// note
	D_Bool Open(const stl::String& pipeName);	
	
	// brief : Write data to pipe
	// @para [in]data 
	// @para [in]dataLen 
	// return : true/false
	// note
	D_Bool Write(D_Int8* data, const D_UInt32 dataLen);
	
private:
	// brief : To pervent copy 
	WritePipe(const WritePipe&);
	void operator=(const WritePipe&);
};

// brief : be used to read pipe
// usage :
//	void MyReadPipe()
//  {
//      ReadPipe readPipe;
//      if (readPipe.Open("/tmp/testFifoFile"))
//      {
//          char buffer[100] = {'\0'};
//          readPipe.Read(buffer, 100);
//          printf("read pipe : %s\n", buffer);
//      }
//  }
class ReadPipe : public Pipe
{
public:
    ReadPipe() {}
    virtual ~ReadPipe() {}

    // brief : open pipe
    // @para [in]pipeName : pipe name
    // return : true/false
    // note
    D_Bool Open(const stl::String& pipeName);

	// brief : read data from pipe
	// @para [out]buffer : template buffer
	// @para [in]bufferSize : template buffer size
	// return : true/false
	// note
	D_Bool Read(D_Int8* buffer, const D_UInt32 bufferSize);    
};

DUYE_POSIX_NS_END 




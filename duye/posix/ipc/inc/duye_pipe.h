/***************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
***************************************************************************/
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

DUYE_POSIX_NS_BEG 
// brief : 进程通信，管道基类，被读管道和写管道继承
// 浣犲ソ鍚�	
class Pipe
{
public:
	Pipe() {}
	virtual ~Pipe() {}
	
	// brief : 鎵撳紑绠￠亾
	// @para pipeName 绠￠亾鍚�
	// return true/false
	// note
	D_BOOL Open(const stl::string& pipeName) = 0;
	
proteced:
	// 绠￠亾鎻忚堪绗�
	D_INT32		m_pipefd;
};

// brief : 鍐欑閬�
// usage :
//	void MyWritePipe()
//	{
// 		WritePipe writePipe;
//		if (writePipe.Open("/tmp/testFifoFile"))
//		{
//		
//		}
//	}
class WritePipe : public Pipe
{
public:
	WritePipe() {}
	virtual ~WritePipe() {}
	
	// brief : 鎵撳紑绠￠亾
	// @para pipeName 绠￠亾鍚�
	// return true/false
	// note
	D_BOOL Open(const stl::string& pipeName);	
	
	// brief : 鍚戠閬撳啓鏁版嵁
	// @para data 鍐欏叆鏁版嵁
	// @para dataLen 鍐欏叆鏁版嵁闀垮害
	// return true/false
	// note
	D_BOOL Write(D_INT8* data, const D_UINT32 dataLen);
	
private:
	// brief : 闃叉鎷疯礉
	WritePipe(const WritePipe&);
	void operator=(const WritePipe&);
};

// brief : 璇荤閬�
// usage :
//	
// ??????


DUYE_POSIX_NS_END 




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
// brief : ����ͨ�ţ��ܵ����࣬�����ܵ���д�ܵ��̳�
// 你好吗	
class Pipe
{
public:
	Pipe() {}
	virtual ~Pipe() {}
	
	// brief : 打开管道
	// @para pipeName 管道名
	// return true/false
	// note
	D_BOOL Open(const stl::string& pipeName) = 0;
	
proteced:
	// 管道描述符
	D_INT32		m_pipefd;
};

// brief : 写管道
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
	
	// brief : 打开管道
	// @para pipeName 管道名
	// return true/false
	// note
	D_BOOL Open(const stl::string& pipeName);	
	
	// brief : 向管道写数据
	// @para data 写入数据
	// @para dataLen 写入数据长度
	// return true/false
	// note
	D_BOOL Write(D_INT8* data, const D_UINT32 dataLen);
	
private:
	// brief : 防止拷贝
	WritePipe(const WritePipe&);
	void operator=(const WritePipe&);
};

// brief : 读管道
// usage :
//	
// ??????


DUYE_POSIX_NS_END 




/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_buffer.h
* @version     
* @brief      
* @author   duye
* @date     2014-01-17
* @note 
*
*  1. 2014-01-17 duye Created this file
* 
*/

#pragma once

#include <duye/stl/inc/duye_stl_def.h>
#include <duye/stl/inc/duye_bytemem.h>

DUYE_STL_NS_BEG

// brief : memory malloc
//	
// usage :
class Buffer 
{
public: 
    // brief : Create new buffer
    // @para [in]allocated : allocate length
    // return : buffer address
    static D_Int8* Create(const D_UInt32 allocated);

    // brief : Create new buffer
    // @para [in]str : buffer init string
    // return : buffer address
    static D_Int8* Create(const D_Int8* str);

    // brief : Create new buffer
    // @para [in]str : buffer init string
    // @para [in]length : the length of string
    // return : buffer address
    static D_Int8* Create(const D_Int8* str, const D_UInt32 length);

    // brief : Get buffer size
    D_UInt32 Size();
    
    // brief : Free buffer
    void Destroy();

private:
    // brief : constructor
    Buffer(const D_UInt32 size);
    
    // brief : malloc memory
    // @para [in]allocated : will allocate length
    // @para [in]length : the length of string
    static Buffer* Allocate(const D_UInt32 allocated);

    // brief : Get C pointer
    D_Int8* GetStart(); 

private:
	// buffer size
	D_UInt32	m_size;
};

DUYE_STL_NS_END

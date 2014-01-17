/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	    duye_buffer.cpp
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

D_Int8* Buffer::Create(const D_UInt32 allocated)
{
    Buffer* buffer = Allocate(allocated);
    D_ASSERT(buffer != NULL);
    return buffer->GetChars();
}

static D_Int8* Buffer::Create(const D_Int8* str)
{
    D_UInt32 length = Bytemem::Strlen(str);
    Buffer* buffer = Allocate(length, length);
    D_ASSERT(buffer != NULL);
    Bytemem::Memcpy(buffer->GetChars(), str, length);
    return buffer->GetChars();    
}

static D_Int8* Buffer::Create(const D_Int8* str, const D_UInt32 length)
{
    Buffer* buffer = Allocate(length, length);
    D_ASSERT(buffer != NULL);
    Bytemem::Memcpy(buffer->GetChars(), str, length);
    return buffer->GetChars();
}

D_UInt32 Buffer::GetLength() const
{
    return m_length;
}

D_UInt32 Buffer::GetAllocated() const
{
    return m_allocated;
}

D_Int8* Buffer::GetChars()
{
    return reinterpret_cast<D_Int8*>(this + 1);       
}

void Buffer::Destroy()
{
    ::operator delete((void*)this);    
}

Buffer* Buffer::Allocate(const D_UInt32 allocated, const D_UInt32 length = 0)
{
    void* mem = ::operator new(sizeof(Buffer) + allocated + 1);
    return new(mem) Buffer(allocated, length);    
}
    
Buffer::Buffer(const D_UInt32 allocated, D_UInt32 length = 0) 
    : m_allocated(allocated) 
    , m_length(length)
{
}

DUYE_STL_NS_END

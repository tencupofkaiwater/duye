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
#include <duye/stl/inc/duye_stl_def.h>
#include <duye/stl/inc/duye_bytemem.h>
#include <duye/stl/inc/duye_buffer.h>

DUYE_STL_NS_BEG

D_Int8* Buffer::Create(const D_UInt32 allocated)
{
    if (allocated == NULL)
    {
        return NULL;
    }
    
    Buffer* buffer = Allocate(allocated);
    D_ASSERT(buffer != NULL);
    
    return buffer->GetStart();
}

D_Int8* Buffer::Create(const D_Int8* str)
{
    if (str == NULL)
    {
        return NULL;
    }
    
    D_UInt32 length = Bytemem::Strlen(str);
    return Create(str, length);
}

D_Int8* Buffer::Create(const D_Int8* str, const D_UInt32 length)
{
    if (str == NULL || length == 0)
    {
        return NULL;
    }
    
    Buffer* buffer = Allocate(length + 1);
    D_ASSERT(buffer != NULL);

    D_Int8* ptr = buffer->GetStart();
    Bytemem::Memcpy(ptr, str, length);
    ptr[length] = '\0';
    
    return ptr;
}

D_UInt32 Buffer::Size()
{
    return m_size;
}

void Buffer::Destroy()
{
    ::operator delete((void*)this);    
}

Buffer::Buffer(const D_UInt32 size) : m_size(size) 
{
}

Buffer* Buffer::Allocate(const D_UInt32 allocated)
{
    void* mem = ::operator new(sizeof(Buffer) + allocated);
    return reinterpret_cast<Buffer*>(mem);  
}

D_Int8* Buffer::GetStart()
{
    return reinterpret_cast<D_Int8*>(this + 1);       
}

DUYE_STL_NS_END

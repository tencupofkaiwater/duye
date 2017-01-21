/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file     duye_msg_queue.h
* @version     
* @brief      
* @author   duye
* @date     2014-10-13
* @note 
*
*  1. 2014-10-13 duye created this file
* 
*/
#pragma once

#include <queue>
#include <duye_system.h>

namespace duye {

static const uint64 DEF_QUEUE_SIZE = 1024;
  
/**
 * @brief access mode
 */
typedef enum
{
    MSG_BLOCK = 0,
    MSG_NONBLOCK
} MsgQueueMode;

/**
 * @brief message queue
 */
template <class T>
class MsgQueue
{
public:
    /**
     * @brief constructor
     * @param [in] queue_size : queue size, default is DEF_QUEUE_SIZE
     */
    MsgQueue(const uint64 queue_size = DEF_QUEUE_SIZE);
    ~MsgQueue();
    
    /**
     * @brief push message
     * @param [in] msg : message
     */
    bool push(T* msg);
    
    /**
     * @brief pop message
     * @param [in] mode : pop block
     * @return message
     */
    T* pop(const MsgQueueMode& mode = MSG_BLOCK);

    /**
     * @brief pop message
     * @param [in] timeout : millisecond
     * @return message
     */
    T* pop(const uint32 timeout);
    
private:
    std::queue<T*>  m_queue;
    Semaphore       m_semaphore;
    uint64          m_queueSize;
};

template <class T>
MsgQueue<T>::MsgQueue(const uint64 queue_size) : m_queueSize(queue_size) {}

template <class T>
MsgQueue<T>::~MsgQueue() {}

template <class T>
bool MsgQueue<T>::push(T* msg)
{
    if (m_queue.size() >= m_queueSize)
    {
        return false;
    }

    m_queue.push(msg);
    m_semaphore.post();
    
    return true;
}

template <class T>
T* MsgQueue<T>::pop(const MsgQueueMode& mode)
{
    if (m_queue.size() == 0) {
        if (mode == MSG_BLOCK)
        {
            m_semaphore.wait();
        }
        else if (mode == MSG_NONBLOCK)
        {
            if (!m_semaphore.tryWait()) {
                return NULL;
            }
        }
        else
        {
            return NULL;
        }
    }
    
    T* msg = m_queue.front();
    m_queue.pop();
    
    return msg;
}

template <class T>
T* MsgQueue<T>::pop(const uint32 timeout)
{
    if (m_queue.size() == 0) {
        if (!m_semaphore.timedWait(timeout)) {
            return NULL;
        }
    }
    
    T* msg = m_queue.front();
    m_queue.pop();
    
    return msg;
}

}

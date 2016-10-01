/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_hcn_server.h
* @version     
* @brief      
* @author   duye
* @date	    2016-03-30
* @note 
*
* 1. 2016-03-30 duye Created this file
*/

#pragma once

#include <map>
#include <duye_type.h>
#include <duye_epoll.h>
#include <duye_thread.h>
#include <duye_lock.h>
#include <duye_thread_pool.h>
#include <duye_net_server.h>

namespace duye {

class HcnServer;

class HcnEvent
{
public:
    HcnEvent(HcnServer* hcnServer, const int32 fd, const EpollEventType type) 
        : m_hcnServer(hcnServer), m_fd(fd), m_type(type) {}

    HcnServer* hcnServer() { return m_hcnServer; }
    int32 fd() { return m_fd; }
    EpollEventType type() { return m_type; }

private:
    HcnServer*     m_hcnServer;
    int32          m_fd;
    EpollEventType m_type;
};

/**
 * @brief Highly Concurrent Network Server Listener
 */
class HcnServerListener : public ThreadJob
{
public:
    virtual ~HcnServerListener() {}
    virtual bool onNetEvent(HcnEvent* event) = 0;
    
protected:
    // implementation for ThreadJob
    virtual bool work(void* userData);
};

class ThreadPool;

/**
 * @brief highly concurrent network server
 * @example:
 * HCNServer hcn_server;
 * if (hcn_server.startServer())
 * {
 *     socket fd;
 *     HcnServerListener* listener = new MyListener();
 *     hcn_server.registerListener(fd, listener);
 * }
 *
 * hcn_server.unregisterListener(fd);
 */
class HcnServer : public NetServer, public ThreadTask
{
public:
    // <sockfd, listener*>
    typedef std::map<int, HcnServerListener*> ListenerContainer;
    
public:
    HcnServer();
    ~HcnServer();

    /**
     * @brief init service
     * @param [in] maxConn : max concurrent connection numbers, default is 1024
     * @return true/false
     */    
    bool initServer(const uint32 maxConn = 1024);

    /**
     * @brief start server, abstract interface from NetServer
     * @return true/false
     */    
    virtual bool startServer();

    /**
     * @brief stop server, abstract interface from NetServer
     * @return true/false
     */        
    virtual bool stopServer();

    /**
     * @brief register listener
     * @param [in] sockfd : socket fd
     * @param [in] listener : listener
     * @param [in] epollMode : epoll events(EPOLLIN, EPOLLOUT, EPOLLPRI, EPOLLERR, 
     * 		EPOLLHUP, EPOLLET, EPOLLONESHOT), default is EPOLLIN | EPOLLOUT
     *	EPOLLIN  : ��ʾ��Ӧ���ļ����������Զ��������Զ�SOCKET�����رգ�
     *  EPOLLOUT : ��ʾ��Ӧ���ļ�����������д
     * 	EPOLLPRI : ��ʾ��Ӧ���ļ��������н��������ݿɶ�������Ӧ�ñ�ʾ�д������ݵ�����
     *  EPOLLERR : ��ʾ��Ӧ���ļ���������������
     *	EPOLLHUP : ��ʾ��Ӧ���ļ����������Ҷ�
     *  EPOLLRDHUP : Stream  socket peer closed connection, or shut down writing half
              of connection.  (This flag is especially useful for writing sim-
              ple code to detect peer shutdown when using Edge Triggered moni-
              toring.)
     *  EPOLLLT : ˮƽ������ȱʡ��ʽ,�ں˸�������һ���ļ��������Ƿ񱻾����ˣ�ͬʱ֧��block��no-block socket��
     *			  ��������ˣ���Ϳ��Զ����������fd����IO����������㲻���κβ������ں˻��ǻ����֪ͨ���
     * 	EPOLLET : ���ش��������ٹ�����ʽ,ֻ֧��no-block socket��������ģʽ�£�����������δ������Ϊ����״̬ʱ��
     *			  �ں�ͨ��epoll�����㡣Ȼ�����������֪���ļ��������Ѿ����������Ҳ�����Ϊ�Ǹ����������͸���ľ���֪ͨ��
     *			  ֱ��������ĳЩ���������Ǹ��ļ�����������Ϊ����״̬��(���磺���ڷ��͡����ܻ��߽�������
     *			  ���߷��ͽ��ܵ���������һ����ʱ������һ��EWOULDBLOCK����)��������ע�⣬���һֱ�������fs��IO����
     *			  (�Ӷ��������ٴα��δ����״̬)���ں˲��ᷢ�͸����֪ͨ��
     * 	EPOLLONESHOT : ֻ����һ���¼���������������¼�֮���������Ҫ�����������socket�Ļ�����Ҫ�ٴΰ����socket
     *			  ���뵽EPOLL������
     * @return true/false
     */       
    bool registerListener(const int32 sockfd, HcnServerListener* listener);
	bool registerListener(const int32 sockfd, HcnServerListener* listener, const uint32 epollMode);

    /**
     * @brief unregister listener
     * @param [in] sockfd : socket fd
     * @return true/false
     */    
    bool unregisterListener(const int32 sockfd);

    /**
     * @brief unregister listener
     * @param [in] sockfd : socket fd
     * @param [in] epollMode : 
     *       EPOLLIN
     *                     The associated file is available for read(2) operations.
     *       EPOLLOUT
     *                     The associated file is available for write(2) operations.
     *       EPOLLRDHUP
     *                     Stream  socket peer closed connection, or shut down writing half
     *                     of connection.  (This flag is especially useful for writing sim-
     *                     ple code to detect peer shutdown when using Edge Triggered moni-
     *                     toring.)
     *       EPOLLPRI
     *                     There is urgent data available for read(2) operations.
     *       EPOLLERR
     *                     Error condition happened  on  the  associated  file  descriptor.
     *                     epoll_wait(2)  will always wait for this event; it is not neces-
     *                     sary to set it in events.
     *       EPOLLHUP
     *                     Hang  up   happened   on   the   associated   file   descriptor.
     *                     epoll_wait(2)  will always wait for this event; it is not neces-
     *                     sary to set it in events.
     *       EPOLLET
     *                     Sets  the  Edge  Triggered  behavior  for  the  associated  file
     *                     descriptor.   The default behavior for epoll is Level Triggered.
     *                     See epoll(7) for more detailed information about Edge and  Level
     *                     Triggered event distribution architectures.
     *       EPOLLONESHOT (since Linux 2.6.2)
     *                     Sets  the  one-shot behavior for the associated file descriptor.
     *                     This means that after an event is pulled out with  epoll_wait(2)
     *                     the  associated  file  descriptor  is internally disabled and no
     *                     other events will be reported by the epoll interface.  The  user
     *                     must  call  epoll_ctl() with EPOLL_CTL_MOD to re-enable the file
     *                     descriptor with a new event mask.
     * @return true/false
     */    
    bool modifyMode(const int32 sockfd, const uint32 epollMode);	

protected:
    // uninit server
    bool uninitServer();
    // implementation for ThreadTask
    virtual bool run();
    // notify to listener
    bool notifyEvent(const EpollEvent& event);
    
private:
    ListenerContainer   m_listenerContainer;
    Mutex               m_listenerMutex;
    Epoll               m_epoll;
    ThreadPool          m_threadPool;
};

}

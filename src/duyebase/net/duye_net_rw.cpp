/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_net_rw.cpp
* @version     
* @brief      
* @author   duye
* @date	    2016-12-27
* @note 
*
* 1. 2016-12-27 duye Created this file
*/

#include <duye_system.h>
#include <duye_socket.h>
#include <duye_net_rw.h>

namespace duye {

int64 NetRW::read(const int32 fd, Buffer& buffer, NetRWStatus& status, const bool block) {
    status = RW_INIT;

    while (1) {
        int8 temp[1024] = {0};
        int64 bytes = Transfer::recv(fd, temp, sizeof(temp), block);
        if (bytes == 0) {
        	status = FD_CLOSEED;
            break;
        } else if (bytes == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                status = RD_FINISHED;
            } else if (errno == EINTR) {
                status = FD_CLOSEED;
            } else {
            	status = FD_CLOSEED;
            }

            break;
        } else if (bytes >= 0) {
	        if (!buffer.append(temp, bytes)) {
	        	status = RD_OVERFLOW;
	        	break;
	        }

        	if (bytes == sizeof(temp)) {
        		status = RD_FINISHED;
        		break;
        	}
        }
    }	

    if (status != RD_FINISHED) {
        return -1;
    }

    return buffer.size();
}

int64 NetRW::read(const int32 fd, int8* buffer, const uint32 size, NetRWStatus& status, const bool block) {
    status = RW_INIT;
    int64 bytes_tatal = -1;

    while (1) {
        int8 temp[1024] = {0};
        int64 bytes = Transfer::recv(fd, temp, sizeof(temp), block);
        if (bytes == 0) {
        	status = FD_CLOSEED;
            break;
        } else if (bytes == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                status = RD_FINISHED;
                buffer[bytes_tatal] = 0;
            } else if (errno == EINTR) {
                status = FD_CLOSEED;
            } else {
            	status = FD_CLOSEED;
            }

            break;
        } else if (bytes >= 0) {
        	if (bytes_tatal + bytes > size) {
        		status = RD_OVERFLOW;
        		break;
        	}

        	memcpy(buffer + bytes_tatal, temp, bytes);
        	bytes_tatal += bytes;
        	if (bytes == sizeof(temp)) {
        		status = RD_FINISHED;
        		buffer[bytes_tatal] = 0;
        		break;
        	}
        }
    }	

    if (status != RD_FINISHED) {
        return -1;
    }    

    return bytes_tatal;
}

int64 NetRW::write(const int32 fd, const Buffer& data, NetRWStatus& status) {
    status = RW_INIT;
    int8* p = (int8*)data.data();
    int64 leave_len = data.size();

    while (1) {
        int64 bytes = Transfer::send(fd, p, leave_len);
        if (bytes == -1) {
            if (errno == EINTR) {
                status = FD_CLOSEED;
                break;
            }

            if (errno == EAGAIN) {
                System::msleep(1);
                continue;
            }
        }

        if (bytes == leave_len) {
            status = WR_FINISHED;
            leave_len = 0;
            break;
        }

        leave_len -= bytes;
        p += bytes;
    }

    if (status != WR_FINISHED) {
        return -1;
    }    

    return data.size() - leave_len;
}

int64 NetRW::write(const int32 fd, const int8* data, const uint32 len, NetRWStatus& status) {
    status = RW_INIT;
    int8* p = (int8*)data;
    int64 leave_len = len;

    while (1) {
        int64 bytes = Transfer::send(fd, p, leave_len);
        if (bytes == -1) {
            if (errno == EINTR) {
                status = FD_CLOSEED;
                return -1;
            }

            if (errno == EAGAIN) {
                System::msleep(1);
                continue;
            }
        }

        if (bytes == leave_len) {
            status = WR_FINISHED;
            leave_len = 0;
            break;
        }

        leave_len -= bytes;
        p += bytes;
    }

    if (status != WR_FINISHED) {
        return -1;
    }    

    return len - leave_len;
}

bool NetRW::close(const int32 fd) {
    return ::close(fd) == 0 ? true : false;
}

}
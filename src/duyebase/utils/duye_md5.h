/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_md5.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-18
* @note 
*
*  1. 2016-04-18 duye created this file
* 
*/
#pragma once

#include <duye_type.h>

namespace duye {

/* MD5 context. */
typedef struct {
  uint32 state[4];                                   /* state (ABCD) */
  uint32 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  int8 buffer[64];                         /* input buffer */
} MD5_CTX;

/*
typedef enum
{
    MD5_16 = 16,
    MD5_32 = 32
} Md5Len;
*/

class Md5
{
public:
    Md5();
    ~Md5();

	void md5Str(int8* instr, int8* digest);
	void md5For16(int8* instr, int8* digest);
	void md5Bytes(int8* bytes, const uint32 size, int8* digest);
	void md5File(int8* filePath, int8* digest);

private:
    // MD5 initialization. Begins an MD5 operation, writing a new context
    void md5Init(MD5_CTX* context);
    // MD5 block update operation. Continues an MD5 message-digest
    // operation, processing another message block, and updating the context.
    void md5Update(MD5_CTX* context, int8* input, uint32 inputLen);
    // MD5 finalization. Ends an MD5 message-digest operation, writing the
    //  the message digest and zeroizing the context
    void md5Final(int8 digest[16], MD5_CTX* context);
    // MD5 basic transformation. Transforms state based on block
    void md5Transform(uint32 state[4], int8 block[64]);
    // Encodes input (uint32) into output (uint8). Assumes len is
    //  a multiple of 4
    void encode(int8* output, uint32* input, uint32 len);
    // Decodes input (uint8) into output (uint32). Assumes len is
    // a multiple of 4.
    void decode(uint32* output, int8* input, uint32 len);   
    // Note: Replace "for loop" with standard memcpy if possible 
    void md5Memcpy(int8* output, int8* input, uint32 len);
    // Note: Replace "for loop" with standard memset if possible
    void md5Memset(int8* output, int32 value, uint32 len);
};
}
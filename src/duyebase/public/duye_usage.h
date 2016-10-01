/************************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
*************************************************************************************/
/**
* @file	     duye_usage.h
* @version     
* @brief      
* @author    duye
* @date	     2014-09-30
* @note 
*
*  1. 2014-09-30 duye created this file
* 
*/
#pragma once

#include <list>
#include <string>

#include <duye_type.h>
#include <duye_system.h>

namespace duye {

/**
 * @brief argument type
 */
typedef enum
{
    NEEDED,
    OPTION
} ArgType;

class Argument;

/**
 * @brief usage class
 */
class Usage
{
public:
    typedef std::list<Argument> ArgumentList;
    typedef std::list<std::string> ExampleList;

public:  
    Usage();
    ~Usage();
    
    void format(const int8* format);
    
    /**
     * @brief add usage example
     * @param [in] example : example
     */
    void addeg(const int8* example);
    
    /**
     * @brief add arguments
     * @param [in] shor_cmd : shor command
     * @param [in] arg_type : need or option
     * @param [in] long_cmd : long command
     * @param [in] description : argument description
     */
    void addArg(const int8 short_cmd,  
        const int8* long_cmd, 
        const ArgType& arg_type,
        const int8* description);
    
    /**
     * @brief print usage
     */
    void print();
    
private:
    ArgumentList   m_argList;
    ExampleList    m_egList;
};

/**
 * @brief argument class
 */
class Argument
{
public:
    Argument();
    ~Argument();
    
private:
    int8       	m_shortCmd;
    ArgType     m_argType;
    std::string m_longCmd;
    std::string m_description;
};
}

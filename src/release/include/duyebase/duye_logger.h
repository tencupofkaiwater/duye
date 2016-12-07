/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		duye_duye_logger.h
* @version     
* @brief      
* @author	duye
* @date		2014-2-18
* @note 
*
*  1. 2014-02-18 duye created this file
* 
*/
#pragma once

#include <map>
#include <string>
#include <duye_system.h>

/**
 * @brief : init log system
 * @para [in] file : log file full path
 */
#define DUYE_LOG_INIT(file) duye::Logger::instance().init(file)

/**
 * @brief : uninit log system
 */
#define DUYE_LOG_UNINIT() duye::Logger::instance().uninit()

/**
 * @brief : get log error description
 */
#define DUYE_LOG_EDESP() duye::Logger::instance().error()

/**
 * @brief : print log
 * @para [in] level : log level(LOG_ERROR,LOG_WARN,LOG_INFO,LOG_DEBUG,LOG_TRACE)
 * @para [in] args : others args
 */
#define DUYE_LOG(level, args...) duye::Logger::instance().printLog(level, DUYE_LOG_PREFIX, __FILE__, __LINE__, __FUNCTION__, ##args)

/**
 * @brief print error log
 * @param [in] args : parameters
 */
#define DUYE_ERROR(args...) DUYE_LOG(duye::LOG_ERROR, ##args)

/**
 * @brief : print warning log
 * @param [in] args : parameters
 */
#define DUYE_WARN(args...) DUYE_LOG(duye::LOG_WARN, ##args)

/**
 * @brief : print info log
 * @param [in] args : parameters
 */
#define DUYE_INFO(args...) DUYE_LOG(duye::LOG_INFO, ##args)

/**
 * @brief : print debug log
 * @param [in] args : parameters
 */	
#define DUYE_DEBUG(args...) DUYE_LOG(duye::LOG_DEBUG, ##args)

/**
 * @brief : print trace log
 * @param [in] args : parameters
 */ 
#define DUYE_TRACE(args...) DUYE_LOG(duye::LOG_TRACE, ##args)

namespace duye {

/**
 * @brief : system log level
 */	
typedef enum 
{
	LOG_NULL,
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
	LOG_TRACE
} LogLevel;

/**
 * @brief : system log print format
 */	
typedef enum 
{
    // time + log string
	PRINT_BASIC,
	// time + log string + file name
	PRINT_MORE,
	// time + log string + file name + function + line
	PRINT_FULL,
} PrintFormat;

/**
 * @brief : where to print log
 */
typedef enum
{
    // print to stdout
	SAVE_STDOUT,
	// print to stderr
	SAVE_STDERR,
	// print to file
	SAVE_FILE
} SaveWay;

/**
 * @brief : system log global configuration rule
 */	
class LogGlobalRule
{
public:
	LogGlobalRule();
	~LogGlobalRule();

	void setTopLogLevel(const LogLevel& logLevel);
	const LogLevel& topLogLevel() const;

	void setMaxFileNum(const uint32 maxFileNum);
	uint32 maxFileNum() const;

	void setMaxFileSize(const uint64 maxFileSize);
	uint64 maxFileSize() const;

	void setAutoWordwrap(const bool isAutoWordwrap);
	bool isAutoWordwrap() const;    

private:
    // global log level, be effectived when sub module hasn't setting 
	LogLevel	m_topLogLevel;
    // log file max number
	uint32		m_maxFileNum;
    // single log file max size
	uint64		m_maxFileSize;	
    // whether is to wordwrap for a log recording 
	bool		m_isAutoWordwrap;
};

/**
 * @brief : system log module configuration rule
 */
class LogModuleRule
{
public:
	LogModuleRule();
	~LogModuleRule();

	void setModuleName(const std::string& moduleName);
	const std::string& moduleName() const;   

	void setLogLevel(const LogLevel& logLevel);
	const LogLevel& logLevel() const;

	void setPrintFormat(const PrintFormat& printFormat);
	const PrintFormat& printFormat() const;   
	
	void setSaveWay(const SaveWay& saveWay);
	const SaveWay& saveWay() const;
	
	void setFilePrefix(const std::string& filePrefix);
	const std::string& filePrefix() const;
	
	void setFilePath(const std::string& filePath);
	const std::string& filePath() const;

    void setFileName(const std::string& fileName);
    const std::string& fileName() const;

private:
	std::string	m_moduleName;
	LogLevel	m_logLevel;
	PrintFormat	m_printFormat;
	SaveWay		m_saveWay;
	std::string	m_filePrefix;
	std::string	m_filePath;
    std::string	m_fileName;
};

/**
 * @brief : log file
 */
class LogFile
{
public:
	explicit LogFile(const std::string& fileName, 
        const uint32 maxFileNum,
        const uint64 maxFileSize);
    
	~LogFile();

    /**
     * @brief : write data to file
     * @para [in] data : data
     * @para [in] len : data length
     * @return : true/false
     */
	bool write(const int8* data, const uint64 len);

private:
	bool open();
	
private:
	File* 		m_file;
	std::string	m_fileName;
    uint32		m_maxFileNum;
    uint32		m_genFileCount;
    uint64		m_maxFileSize;
    uint64		m_currFileSize;
};

/**
 * @brief : system log
 */
class Logger
{
public:
	// <module_name, module_rule>
	typedef std::map<const std::string, LogModuleRule*>     LogModuleRuleMap;
	// <LogLevel, string>
	typedef std::map<const LogLevel, const std::string>     LogLevelMap;
	// <PrintFormat, string>
	typedef std::map<const PrintFormat, const std::string>  LogPrintFormatMap;
	// <SaveWay, string>
	typedef std::map<const SaveWay, const std::string>      LogSaveWayMap;
	// <file_name, LogFile*>
	typedef std::map<const std::string, LogFile*>           LogFileMap;
	
public:

	static Logger& instance();
	
	/**
	 * @brief : init
	 * @param [in] file : log conf file full path
	 * @return : true/false
	 */
	bool init(const char* file);
	
	/**
	 * @brief : uninit
	 * @return : true/false
	 */
	bool uninit();

 	/**
	 * @brief : uninit
	 * @return : error description
	 */
	char* error();   

    /**
     * @brief : print log
     * @para [in] logLevel : log level
     * @para [in] module : module name
     * @para [in] file : code src file full path
     * @para [in] line : code src file line number
     * @para [in] function : code src function name
     * @para [in] args : others args
     */
	void printLog(const LogLevel logLevel, 
		const int8* module, 
		const int8* file, 
		const uint32 line, 
		const int8* function,
		const int8* args, ...);	

private:
	Logger();
	~Logger();

	void defPrintLog(const LogLevel logLevel, 
		const int8* module, 
		const int8* file, 
		const uint32 line, 
		const int8* function,
		const int8* args, ...); 
	void saveToFile(const LogModuleRule* moduleRule, const int8* log, const uint64 len);
	bool parserLogConf(const char* file);
	bool initLogFile();
	bool findLogLevel(const int8* logLevelStr, LogLevel& logLevel) const;
	bool findPrintFormat(const int8* printFormatStr, PrintFormat& printFormat) const;
	bool findSaveWay(const int8* saveWayStr, SaveWay& saveWay) const;
	const LogModuleRule* findModuleRule(const std::string& moduleName) const;
    void getSysTime(int8* buffer, const uint32 size);

private:
	LogLevelMap		    m_logLevelMap;
	LogPrintFormatMap	m_printFormatMap;
	LogSaveWayMap		m_saveWayMap;
	LogGlobalRule		m_globalRule;
	LogModuleRuleMap	m_moduleRuleMap;
	LogFileMap			m_logFileMap;
    bool                m_isUseDefConf;
	Error*				m_error;
	Mutex				m_logMutex;
};
}

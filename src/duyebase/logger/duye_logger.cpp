/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file		duye_logger.cpp
* @version     
* @brief      
* @author	duye
* @date		2014-07-01
* @note 
*
*  1. 2014-07-01 duye Created this file
* 
*/
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <string>
#include <duye_file.h>
#include <duye_xml.h>
#include <duye_helper.h>
#include <duye_logger.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.logger";
static const int8* DEF_CONF_FILE_NAME = 

"duye_log_conf.xml";

LogGlobalRule::LogGlobalRule() 
    : m_topLogLevel(LOG_TRACE)
    , m_maxFileNum(0)
    , m_maxFileSize(0)
    , m_isAutoWordwrap(true)
{
}

LogGlobalRule::~LogGlobalRule()
{
}

void LogGlobalRule::setTopLogLevel(const LogLevel& logLevel)
{
    m_topLogLevel = logLevel;
}

const LogLevel& LogGlobalRule::topLogLevel() const
{
    return m_topLogLevel;
}

void LogGlobalRule::setMaxFileNum(const uint32 maxFileNum)
{
	m_maxFileNum = maxFileNum;
}

uint32 LogGlobalRule::maxFileNum() const
{
	return m_maxFileNum;
}

void LogGlobalRule::setMaxFileSize(const uint64 maxFileSize)
{ 
	m_maxFileSize = maxFileSize;   
}

uint64 LogGlobalRule::maxFileSize() const
{
	return m_maxFileSize;
}

void LogGlobalRule::setAutoWordwrap(const bool isAutoWordwrap)
{
	m_isAutoWordwrap = isAutoWordwrap;
}

bool LogGlobalRule::isAutoWordwrap() const
{
	return m_isAutoWordwrap;   
}
    
LogModuleRule::LogModuleRule() 
    : m_logLevel(LOG_ERROR)
    , m_printFormat(PRINT_BASIC)
    , m_saveWay(SAVE_STDOUT)
{
}

LogModuleRule::~LogModuleRule()
{
}

void LogModuleRule::setModuleName(const std::string& moduleName)
{
	m_moduleName = moduleName;
}

const std::string& LogModuleRule::moduleName() const
{
	return m_moduleName;
}

void LogModuleRule::setLogLevel(const LogLevel& logLevel)
{
	m_logLevel = logLevel;
}

const LogLevel& LogModuleRule::logLevel() const
{
	return m_logLevel;
}

void LogModuleRule::setPrintFormat(const PrintFormat& printFormat)
{
	m_printFormat = printFormat;
}

const PrintFormat& LogModuleRule::printFormat() const
{
	return m_printFormat;
}

void LogModuleRule::setSaveWay(const SaveWay& saveWay)
{
	m_saveWay = saveWay;
}

const SaveWay& LogModuleRule::saveWay() const
{
	return m_saveWay;
}

void LogModuleRule::setFilePrefix(const std::string& filePrefix)
{
	m_filePrefix = filePrefix;
}

const std::string& LogModuleRule::filePrefix() const
{
	return m_filePrefix;
}

void LogModuleRule::setFilePath(const std::string& filePath)
{
	m_filePath = filePath;
}

const std::string& LogModuleRule::filePath() const
{
	return m_filePath;
}

void LogModuleRule::setFileName(const std::string& fileName)
{
	m_fileName = fileName;	
}

const std::string& LogModuleRule::fileName() const
{
	return m_fileName;
}

LogFile::LogFile(const std::string& fileName, 
    const uint32 maxFileNum,
    const uint64 maxFileSize) 
	: m_file(NULL)
	, m_fileName(fileName) 
	, m_maxFileNum(maxFileNum)
	, m_genFileCount(0)
	, m_maxFileSize(maxFileSize)
	, m_currFileSize(0)
{
	// remove old log files
	int8 cmd[256] = {0};
	sprintf(cmd, "rm %s*.glog -f", m_fileName.c_str());
	System::shell(cmd);
}

LogFile::~LogFile()
{
	delete m_file;
}

bool LogFile::write(const int8* data, const uint64 len)
{
	if (m_file == NULL)
	{
		if (open() != true)
		{
			return false;	
		}
	}
	
	if (m_file->write(data, len) < 0)
	{
		return false;
	}
	
	m_currFileSize += len;
	
	if (m_currFileSize >= m_maxFileSize)
	{
		open();
	}
	
	return true;
}

bool LogFile::open()
{
	std::string fileFullName;
	
	while (true)
	{
		m_genFileCount++;
		
		if (m_genFileCount > m_maxFileNum)
		{
			std::string removeFileFullName = m_fileName + "_" + std::to_string(m_genFileCount - m_maxFileNum) + ".glog";
			FileUtil::removeFile(removeFileFullName.c_str());
		}
		
		fileFullName = m_fileName + "_" + std::to_string(m_genFileCount) + ".glog";
		
		break;
	}
	
	delete m_file;
	m_file = NULL;
	
	m_file = new File(fileFullName.c_str());
	if (m_file->open(OPEN_WRITE) != true)
	{
		return false;
	}	
	
	return true;
}

Logger::Logger() : m_isUseDefConf(false) 
{
	m_logLevelMap.insert(std::make_pair(LOG_NULL, "null"));
	m_logLevelMap.insert(std::make_pair(LOG_ERROR, "error"));
	m_logLevelMap.insert(std::make_pair(LOG_WARN, "warn"));
	m_logLevelMap.insert(std::make_pair(LOG_INFO, "info"));
	m_logLevelMap.insert(std::make_pair(LOG_DEBUG, "debug"));
	m_logLevelMap.insert(std::make_pair(LOG_TRACE, "trace"));
	     
	m_printFormatMap.insert(std::make_pair(PRINT_BASIC, "basic"));
	m_printFormatMap.insert(std::make_pair(PRINT_MORE, "more"));
	m_printFormatMap.insert(std::make_pair(PRINT_FULL, "full"));
	 
	m_saveWayMap.insert(std::make_pair(SAVE_STDOUT, "stdout"));
	m_saveWayMap.insert(std::make_pair(SAVE_STDERR, "stderr"));
	m_saveWayMap.insert(std::make_pair(SAVE_FILE, "file"));

	m_error.setPrefix(DUYE_LOG_PREFIX);
}

Logger::~Logger() 
{ 
}

Logger& Logger::instance()
{
	static Logger ins;
	return ins;
}

bool Logger::init(const char* file)
{
	// parser file
	if (file != NULL)
	{
		// load conf file
		if (!parserLogConf(file))
		{
      		return false;
		}
		
    	// init file
    	if (!initLogFile())
    	{
    		return false;
    	}  		
	}
    else
    {
        m_isUseDefConf = true;
    }

	return true;
}

bool Logger::uninit()
{
	LogModuleRuleMap::iterator ruleIter = m_moduleRuleMap.begin();
	for (; ruleIter != m_moduleRuleMap.end(); ++ruleIter)
	{
		delete ruleIter->second;
	}
	m_moduleRuleMap.clear();
	
	LogFileMap::iterator fileIter = m_logFileMap.begin();
	for (; fileIter != m_logFileMap.end(); ++fileIter)
	{
		delete fileIter->second;
	}
	m_logFileMap.clear();

	return true;
}

uint8* Logger::error()
{
    return m_error.error;
}

void Logger::printLog(const LogLevel logLevel, 
	const int8* module, 
	const int8* file, 
	const uint32 line, 
	const int8* function,
	const int8* args, ...)
{   
    if (m_isUseDefConf)
    {
        defPrintLog(logLevel, module, file, line, function, args);
        return;
    }

    const LogModuleRule* moduleRule = findModuleRule(module);
    if (moduleRule == NULL)
    {
        return;
    }

    if (logLevel > moduleRule->logLevel() || logLevel > m_globalRule.topLogLevel())
    {
        return;
    }    

	int8 printBuf[ERROR_BUF_SIZE] = {0};
	uint32 bufSize = ERROR_BUF_SIZE;
	uint64 pos = 0;

	// add time
	int8 timeStr[128] = {0};
    getSysTime(timeStr, sizeof(timeStr));
	pos += snprintf(printBuf + pos, bufSize - pos, "%s ", timeStr);

	// add log level and module name
	if (logLevel == LOG_ERROR)
	    pos += snprintf(printBuf + pos, bufSize - pos, "\033[1;31;40m<%s>\033[0m[%s]", m_logLevelMap[logLevel].c_str(), module);
	else if (logLevel == LOG_WARN)
	    pos += snprintf(printBuf + pos, bufSize - pos, "\033[1;33;40m<%s>\033[0m[%s]", m_logLevelMap[logLevel].c_str(), module);
    else
        pos += snprintf(printBuf + pos, bufSize - pos, "\033[1;32;40m<%s>\033[0m[%s]", m_logLevelMap[logLevel].c_str(), module);

	// add source file name, function name and line
	switch (moduleRule->printFormat())
	{
        case PRINT_BASIC:
            pos += snprintf(printBuf + pos, bufSize - pos, "LOG:");
            break;
        case PRINT_MORE:
            pos += snprintf(printBuf + pos, bufSize - pos, "%s LOG:", StrHelper::basename(file).c_str());
            break;
        case PRINT_FULL:
            pos += snprintf(printBuf + pos, bufSize - pos, "%s::%s()+%d LOG:", StrHelper::basename(file).c_str(), function, line);
            break;
        default:
            break;
	}

    // add log string
    #if 0
	pos += System::pformat(printBuf + pos, bufSize - pos, args);
	#else
	va_list vaList;
    va_start(vaList, args);
    pos += vsnprintf(printBuf + pos, bufSize - pos, args, vaList);
    va_end(vaList);	
	#endif

	// add word wrap
	if (m_globalRule.isAutoWordwrap())
		pos += snprintf(printBuf + pos, bufSize - pos, "\n");  
	printBuf[pos] = 0;

	//AutoLock autoLock(m_logMutex);
	switch (moduleRule->saveWay())
	{
	case SAVE_STDOUT:
		fprintf(stdout, "%s", printBuf);
		break;
	case SAVE_STDERR:
		fprintf(stderr, "%s", printBuf);
		break;
	case SAVE_FILE:
		saveToFile(moduleRule, printBuf, pos);
		break;
	}
}

void Logger::defPrintLog(const LogLevel logLevel, 
	const int8* module, 
	const int8* file, 
	const uint32 line, 
	const int8* function,
	const int8* args, ...)
{   
	int8 printBuf[ERROR_BUF_SIZE] = {0};
	uint32 bufSize = ERROR_BUF_SIZE;
	uint64 pos = 0;

	// add time
	int8 timeStr[128] = {0};
    getSysTime(timeStr, sizeof(timeStr));
	pos += snprintf(printBuf + pos, bufSize - pos, "%s  ", timeStr); 

	// add log level and module name
	if (logLevel == LOG_ERROR)
	    pos += snprintf(printBuf + pos, bufSize - pos, "\033[1;31;40m<%s>\033[0m[%s]", m_logLevelMap[logLevel].c_str(), module);
	else if (logLevel == LOG_WARN)
	    pos += snprintf(printBuf + pos, bufSize - pos, "\033[1;33;40m<%s>\033[0m[%s]", m_logLevelMap[logLevel].c_str(), module);
    else
        pos += snprintf(printBuf + pos, bufSize - pos, "\033[1;32;40m<%s>\033[0m[%s]", m_logLevelMap[logLevel].c_str(), module);
	
	// add source file name, function name and line
    pos += snprintf(printBuf + pos, bufSize - pos, "%s::%s()+%d LOG:", StrHelper::basename(file).c_str(), function, line);

    // add log string
	pos += System::pformat(printBuf + pos, bufSize - pos, args);

    // add word wrap
	pos += snprintf(printBuf + pos, bufSize - pos, "\n");    

    if (logLevel == LOG_ERROR)
	    fprintf(stderr, "%s", printBuf);
    else
        fprintf(stdout, "%s", printBuf);
}

void Logger::saveToFile(const LogModuleRule* moduleRule, const int8* log, const uint64 len)
{
	LogFileMap::iterator iter = m_logFileMap.find(moduleRule->fileName());
	if (iter == m_logFileMap.end())
	{
		return;
	}
	
	LogFile* logFile = iter->second;
	logFile->write(log, len);
}

bool Logger::parserLogConf(const char* file)
{
	if (file == NULL)
		return false;
	
	// read configuration file
	XmlDocument logDoc;
    if (!logDoc.loadFile(file))
	{
		ERROR_DUYE_LOG("load log conf file '%s' failed:%s", file, logDoc.errorDesc());
	    return false;
	}

	// debug
	//logDoc.print();
	
	XmlElement* rootElement = logDoc.rootElement();
	if (rootElement == NULL)
	{
		ERROR_DUYE_LOG("rootElement == NULL");
	    return false;		
	}
	
	if (rootElement->valueStr() != "logconf")
	{
		ERROR_DUYE_LOG("rrootElement->value() != 'logconf', rootElement->valueStr() = %s", rootElement->value());
	    return false;		
	}
	
	XmlElement* childElement = rootElement->firstChildElement();
	for (; childElement != NULL; childElement = childElement->nextSiblingElement())
	{
		if (childElement->valueStr() == "toplevel")
		{
			const int8* text = childElement->getText();
			if (text == NULL)
			{
				// set default value
				m_globalRule.setTopLogLevel(LOG_INFO);	
				continue;
			}
			
			LogLevel logLevel = LOG_NULL;
			if (findLogLevel(text, logLevel) != true)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <toplevel>, please check file '%s'", DEF_CONF_FILE_NAME);
				return false;
			}
			
			m_globalRule.setTopLogLevel(logLevel);
		}
		else if (childElement->valueStr() == "maxfilenum")
		{
			const int8* text = childElement->getText();
			if (text == NULL)
			{
				// set default value
				m_globalRule.setMaxFileNum(10);	
				continue;
			}
			
			int32 maxFileNum = std::stoi(text);
			if (maxFileNum <= 0)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <maxfilenum>, please check file '%s'", DEF_CONF_FILE_NAME);
				return false;					
			}
			
			m_globalRule.setMaxFileNum(maxFileNum);
		}
		else if (childElement->valueStr() == "maxfilesize")
		{
			const int8* text = childElement->getText();
			if (text == NULL)
			{
				m_globalRule.setMaxFileSize(10);
				continue;
			}
			
			int32 maxFileSize = std::stoi(text);
			if (maxFileSize <= 0)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <maxfilesize>, please check file '%s'", DEF_CONF_FILE_NAME);
				return false;
			}
			
			m_globalRule.setMaxFileSize(maxFileSize);
		}
		else if (childElement->valueStr() == "autowordwrap")
		{
			const int8* text = childElement->getText();
			if (strcmp(text, "true") == 0)
			{
				m_globalRule.setAutoWordwrap(true);	
			}
			else if (strcmp(text, "false") == 0)
			{
				m_globalRule.setAutoWordwrap(false);
			}
			else
			{
				ERROR_DUYE_LOG("parser log configuration error for get <autowordwrap>, please check file '%s", DEF_CONF_FILE_NAME);
				return false;
			}
		}
		else if (childElement->valueStr() == "module")
		{
			// get module rule
			const int8* moduleName = childElement->attribute("name");
			if (moduleName == NULL)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <module name>, please check file '%s'", DEF_CONF_FILE_NAME);
				return false;
			}
			
			if (m_moduleRuleMap.find(moduleName) != m_moduleRuleMap.end())
			{
				continue;
			}

			LogLevel logLevel = LOG_NULL;
			const int8* levelStr = childElement->attribute("level");
			if (levelStr == NULL)
			{
				// use top level
				logLevel = m_globalRule.topLogLevel();
			}
			else
			{			
				if (findLogLevel(levelStr, logLevel) < 0)
				{
					ERROR_DUYE_LOG("parser log configuration error for get <module level>, please check file '%s", DEF_CONF_FILE_NAME);
					return false;
				}
			}
			
			const int8* formatStr = childElement->attribute("format");
			if (formatStr == NULL)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <module format>, please check file '%s", DEF_CONF_FILE_NAME);
				return false;
			}
			
			PrintFormat printFormat = PRINT_BASIC;
			if (findPrintFormat(formatStr, printFormat) < 0)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <module format>, please check file '%s", DEF_CONF_FILE_NAME);
				return false;
			}
			
			const int8* outo = childElement->attribute("outo");
			if (outo == NULL)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <module outo>, please check file '%s", DEF_CONF_FILE_NAME);
				return false;
			}
			
			SaveWay saveWay = SAVE_STDOUT;
			if (findSaveWay(outo, saveWay) < 0)
			{
				ERROR_DUYE_LOG("parser log configuration error for get <module outo>, please check file '%s", DEF_CONF_FILE_NAME);
				return false;
			}
			
			LogModuleRule* moduleRule = new LogModuleRule;
			moduleRule->setModuleName(moduleName);
			moduleRule->setLogLevel(logLevel);
			moduleRule->setPrintFormat(printFormat);
			moduleRule->setSaveWay(saveWay);
			
			const int8* prefix = childElement->attribute("prefix");
			if (prefix != NULL)
			{
				moduleRule->setFilePrefix(prefix);
			}
			
			const int8* path = childElement->attribute("path");
			if (path != NULL)
			{
				moduleRule->setFilePath(path);
			}
			
			m_moduleRuleMap.insert(std::make_pair(moduleName, moduleRule));
		}        
	}
	
	return true;	
}

bool Logger::initLogFile()
{
	LogModuleRuleMap::iterator iter = m_moduleRuleMap.begin();
	for (; iter != m_moduleRuleMap.end(); ++iter)
	{
		LogModuleRule* moduleRule = iter->second;
		if (moduleRule->saveWay() != SAVE_FILE)
		{
			continue;
		}
		
		std::string filePath = moduleRule->filePath();
		if (filePath == "." || filePath.empty())
		{
			filePath = "./";
		}
		else if (filePath.at(filePath.length() - 1) != '/')
		{
			filePath.append('/', 1);
		}
		
		std::string fileName;
		if (moduleRule->filePrefix().empty())
		{
			fileName = filePath + moduleRule->moduleName();
		}
		else
		{
			fileName = filePath + moduleRule->filePrefix();
		}
		
		moduleRule->setFileName(fileName);
		if (m_logFileMap.find(fileName) == m_logFileMap.end())
		{
			m_logFileMap.insert(std::make_pair(fileName, 
                new LogFile(fileName, 
                m_globalRule.maxFileNum(),
                m_globalRule.maxFileSize()))); 
		}
	}
	
	return true;
}

bool Logger::findLogLevel(const int8* logLevelStr, LogLevel& logLevel) const
{
	LogLevelMap::const_iterator iter = m_logLevelMap.begin();
	for (; iter != m_logLevelMap.end(); ++iter)
	{
		if (iter->second.compare(logLevelStr) == 0)
		{
			logLevel = iter->first;
			return true;
		}
	}
	
	return false;	
}

bool Logger::findPrintFormat(const int8* printFormatStr, PrintFormat& printFormat) const
{
	LogPrintFormatMap::const_iterator iter = m_printFormatMap.begin();
	for (; iter != m_printFormatMap.end(); ++iter)
	{
		if (iter->second.compare(printFormatStr) == 0)
		{
			printFormat = iter->first;
			return true;
		}
	}
	
	return false;	
}

bool Logger::findSaveWay(const int8* saveWayStr, SaveWay& saveWay) const
{
	LogSaveWayMap::const_iterator iter = m_saveWayMap.begin();
	for (; iter != m_saveWayMap.end(); ++iter)
	{
		if (iter->second.compare(saveWayStr) == 0)
		{
			saveWay = iter->first;
			return true;
		}
	}

    return false;
}

const LogModuleRule* Logger::findModuleRule(const std::string& moduleName) const
{
	std::vector<std::string> outArray;
	StrHelper::split(moduleName, '.', outArray);

	for (uint32 i = outArray.size(); i > 0; i--)
	{
		std::string tempModuleName;
		for (uint32 j = 0; j < i; j++)
		{
			tempModuleName += outArray[j];
			if (j != i - 1) {
				tempModuleName.append(".");
			}
		}

		LogModuleRuleMap::const_iterator iter = m_moduleRuleMap.find(tempModuleName);
		if (iter == m_moduleRuleMap.end())
		{
			continue;
		}

		return iter->second;		
	}

	return NULL;
}

void Logger::getSysTime(int8* buffer, const uint32 size)
{
	if (buffer == NULL || size == 0)
    	return;

    TimeHelper::TimeValue timeValue;    
    TimeHelper::format(System::sysTime(), timeValue);

    snprintf(buffer, size, "%d-%d-%d %d:%d:%d:%03d", timeValue.year, timeValue.month, timeValue.day, 
        timeValue.hour, timeValue.minute, timeValue.sec, timeValue.msec);
}

}

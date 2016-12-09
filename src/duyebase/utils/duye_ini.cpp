/************************************************************************************
**  
*    @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_ini.cpp
* @version     
* @brief      
* @author   duye
* @date	    2013-11-15
* @note 
*
*  1. 2013-11-15 duye Created this file
* 
*/
#include <duye_ini_section.h>
#include <duye_ini.h>

namespace duye {

static const int8* DUYE_LOG_PREFIX = "duye.system.file";
static const uint64 INI_TMP_BUF_SIZE = 1024 * 10;

IniFile::IniFile() : m_error(NULL)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);
}

IniFile::IniFile(const std::string& filePath) : m_error(NULL)
{
	m_error.setPrefix(DUYE_LOG_PREFIX);
    loadFile(m_filePath);
}

IniFile::~IniFile()
{
	if (m_error)
	{
		delete m_error;
		m_error = NULL;
	}
}

bool IniFile::loadFile(const std::string& filePath)
{
    if (m_filePath == filePath)
    {
    	ERROR_DUYE_LOG("file has load");
    	return false;
    }

    if (!m_filePath.empty())
    {
    	cleanSectionMap();    
    }

    m_filePath = filePath;

    File file(m_filePath.c_str());
    if (!file.open(OPEN_READ))
    {
    	ERROR_DUYE_LOG("open file failed");
    	return false;
    }

    int64 fileSize = file.size();
    if (fileSize <= 0)
    {   
    	file.close();
    	ERROR_DUYE_LOG("file is empty");
    	return false;
    }

    int8* buffer = new int8[fileSize + 1];
    int64 readSize = file.read(buffer, fileSize);
    file.close();

    if (readSize != fileSize)
    {
    	ERROR_DUYE_LOG("read file failed");
    	return false;    
    }

    buffer[readSize] = 0;
    bool ret = importData(buffer, fileSize);

    delete [] buffer;
    buffer = NULL;

    return ret;
}

bool IniFile::importData(const std::string& fileData)
{
    return importData(fileData.c_str(), fileData.length());
}

bool IniFile::importData(const int8* data, const uint64 length)
{
    uint64 offset = 0;

    while (offset < length)
    {
    	switch (data[offset])
    	{
        case '[':
            if (parserSection(data, length, offset) != true)
            {
                ERROR_DUYE_LOG("file section failed");
                return false;
            }
			break;
        default:
            offset++;
            break;
        }
    }

    return true;
}

bool IniFile::getParaVal(const std::string& section, const std::string& paraName, std::string& value)
{
    AutoLock autoLock(m_mapMutex); 
    IniSectionMap::iterator iter = m_iniSectionMap.find(section);
    if (iter == m_iniSectionMap.end())
    {
    	ERROR_DUYE_LOG("section failed");
    	return false;
    }

    return iter->second->getPara(paraName, value);
}

bool IniFile::setParaVal(const std::string& section, 
    const std::string& paraName, 
    const std::string& value)
{
    AutoLock autoLock(m_mapMutex); 
    IniSectionMap::iterator iter = m_iniSectionMap.find(section);
    if (iter == m_iniSectionMap.end())
    {
    	return false;
    }

    return iter->second->setPara(paraName, value);    
}

bool IniFile::delSection(const std::string& section)
{
    AutoLock autoLock(m_mapMutex); 
    IniSectionMap::iterator iter = m_iniSectionMap.find(section);
    if (iter == m_iniSectionMap.end())
    {
    	return false;
    }

    m_iniSectionMap.erase(iter);
    return true;    
}

bool IniFile::delPara(const std::string& section, const std::string& paraName)
{
    AutoLock autoLock(m_mapMutex); 
    IniSectionMap::iterator iter = m_iniSectionMap.find(section);
    if (iter == m_iniSectionMap.end())
    {
    	return false;
    }

    return iter->second->delPara(paraName);     
}

bool IniFile::saveFile()
{
    if (m_filePath.empty())
    {
    	return false;
    }

    saveFile(m_filePath);
    return true;
}

bool IniFile::saveFile(const std::string& filePath)
{
    if (filePath.empty())
    {
    	return false;
    }

    int8 tmpBuf[INI_TMP_BUF_SIZE] = {0};
    uint64 bufPos = 0;

    AutoLock autoLock(m_mapMutex); 

    IniSectionMap::iterator iter = m_iniSectionMap.begin();
    for (; iter != m_iniSectionMap.end(); ++iter)
    {
    	bufPos += sprintf(tmpBuf + bufPos, "[%s]\n", iter->first.c_str());
    	if (bufPos >= INI_TMP_BUF_SIZE)
    	{
    	    return false;
    	}       

        IniSection* section = iter->second;
        const IniSection::KeyValueMap& keyValueMap = section->getkeyValueMap();
		IniSection::KeyValueMap::const_iterator iter = keyValueMap.begin();
		for (; iter != keyValueMap.end(); ++iter)
        {
		    bufPos += sprintf(tmpBuf + bufPos, "%s=%s\n", iter->first.c_str(), iter->second.c_str()); 
		    if (bufPos >= INI_TMP_BUF_SIZE)
		    {
		    	return false;
		    }
        }
    }

    tmpBuf[bufPos] = 0;
    File file(m_filePath.c_str());
    if (file.open(OPEN_WRITE) != true)
    {
    	return false;
    }    

    uint64 writeBytes = file.write(tmpBuf, bufPos);
    file.close();

    if (writeBytes != bufPos)
    {
    	return false;   
    }

    return true;
}

int8* IniFile::error()
{
    return m_error->error;
}

void IniFile::cleanSectionMap()
{
    AutoLock autoLock(m_mapMutex); 
    IniSectionMap::iterator iter = m_iniSectionMap.begin();
    while (iter != m_iniSectionMap.end())
    {
    	delete iter->second;
    	m_iniSectionMap.erase(iter++);   
    }
}

bool IniFile::parserSection(const int8* data, 
    const uint64 length, 
    uint64& offset)
{
    uint64 begPos = offset;
    uint64 endPos = offset;
    bool findSectionEnd = false;

    while (data[endPos] != 0)
    {
    	switch (data[endPos++])
        {
            case '\r':
            case '\n':
            case ';':
            case '=':
            case ':':
                offset = endPos;
                return false;
            case ']':
                findSectionEnd = true;
                break;
            default:
                break;
        }  

        if (findSectionEnd)
        {
            break;
        }
    }

    if (endPos - begPos <= 1)
    {
    	offset = endPos;
    	return false;    
    }

    std::string sectionName(data + begPos, endPos - begPos);
    IniSection* section = new IniSection(sectionName);
    std::string lineStr;
    while (getOneLine(data + endPos, length - offset, lineStr) == true)
    {
    	offset += lineStr.length();
    	uint32 midPos = 0;
    	if ((midPos = lineStr.find('=')) == std::string::npos)
    	{
    	    continue;       
    	}
    	
    	section->addPara(lineStr.substr(0, midPos), lineStr.substr(midPos + 1));
    }

    m_iniSectionMap.insert(std::make_pair(sectionName, section));
    offset = endPos;

    return true;
}

bool IniFile::getOneLine(const int8* data, 
    const uint64 length, 
    std::string& lineStr)
{
    if (length == 0)
    {
    	return false;
    }

    uint64 endPos = 0;
    while (endPos < length)
    {
    	if (data[endPos++] == '\n')
    	{
    	    break;
    	}
    }

    lineStr.assign(data, endPos);
    return true;
}

}

/***********************************************************************************
**  
* @copyright (c) 2010-2019, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    duye_db_tab.h
* @version     
* @brief      
* @author   duye
* @date	    2016-04-29
* @note 
*
* 1. 2016-04-29 duye Created this file
*/
#pragma once

#include <string>
#include <list>
#include <vector>
#include <map>
#include <duye_type.h>
#include <duye_db_const.h>

namespace duye {

/**
* @brief DB_FILE
*/
class FileType
{
public:
    // file size range (0MB~16384MB(16G))
    uint32      minSize;
    uint32      manSize;    
};

/**
* @brief DB_INT
*/
class IntType
{
public:
    // DB_INT range (-2^31 ~ 2^31)
    uint32      minSize;
    uint32      manSize; 
};    

/**
* @brief DB_UINT
*/
class UintType
{
public:
    // DB_UINT range (0 ~ 2^32)
    uint32      minSize;
    uint32      manSize;
};  

/**
* @brief DB_FLOAT
*/
class FloatType
{
public:
    // DB_FLOAT range (-2^31 ~ 2^31)
    uint32      minSize;
    uint32      manSize;
    // decimals range (0 ~ 1024)
    uint32      decimals; 
};

/**
* @brief DB_STR
*/
class StrType
{
public:
    // DB_STR length range(0 ~ 2^32)
    uint32      minLen;
    uint32      maxLen;
};    

/**
* @brief DB_BYTE
*/
class ByteType
{
public:
    // DB_BYTE length range(0 ~ 2^32)
    uint32      minLen;
    uint32      maxLen;    
};

/**
 * @brief table cell
 */
class TabCell
{
public:
    TabCell() : type(DB_UNKNOWN) {}
    explicit TabCell(const DBDataType& intype, const std::string& inkey, const std::string& invalue) :
        type(intype), key(inkey), value(invalue) {}
    ~TabCell() {}

    DBDataType      type;
    std::string     key;
    std::string     value;
};

// <TabCell>
typedef std::vector<TabCell> TabCellVector;

/**
 * @brief table row data
 */
class TabRowData
{
public:
    TabRowData() {}
    ~TabRowData() {}
    
    TabCellVector   cellVector;
};

/**
 * @brief db table column
 */
class TabColumnAttr
{   
public:
    TabColumnAttr() : type(DB_UNKNOWN), isKey(false) {}
    ~TabColumnAttr() {}

    // column name
    std::string name;
    // value type
    DBDataType  type;
    // whether is primary key
    bool        isKey;
    FileType    fileType;
    IntType     intType;
    UintType    uintType;
    FloatType   floatType;
    StrType     strType;
    ByteType    byteType;
};

typedef std::map<const std::string, const TabColumnAttr> TabColumnAttrMap;

/**
 * @brief db table column
 */
class TabAttr
{
public:
    TabAttr() : m_hasIncId(false), m_incIdInitVal(0), m_isIncIdKey(true) {}
    ~TabAttr() {}

    // table name
    std::string         m_name;
    // whether have setting incremental id column
    bool                m_hasIncId;
    // incremental id init base value
    uint32              m_incIdInitVal;
    // incremental id whether is primary key
    bool                m_isIncIdKey;
    // clolumn attr map
    TabColumnAttrMap    m_columnAttrMap;
};

/**
 * @brief db table
 */
class DBTable
{
public:
    DBTable() {}
    ~DBTable() {}

    /**
     * @brief set table attribute
     * @param [in] tabAttr : table attribute
     */
    void setTabAttr(const TabAttr& tabAttr) { m_tabAttr = tabAttr; }

    /**
     * @brief get table attribute
     * @return : table attribute
     */    
    const TabAttr& tabAttr() const { return m_tabAttr; }
    
private:
    TabAttr   m_tabAttr; 
};

// <table_name, DBTable>
typedef std::map<const std::string, DBTable> DBTableMap;

}

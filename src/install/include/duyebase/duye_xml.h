/***********************************************************************************
**  
* @copyright (c) 2013-2100, ChengDu Duyer Technology Co., LTD. All Right Reserved.
*
************************************************************************************/
/**
* @file	    g_xml.h
* @version     
* @brief      
* @author   duye
* @date	    2014-8-7
* @note 
*
*  1. 2014-8-7 duye Created this file
* 
*/
#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>

namespace duye {

class XmlDocument;
class XmlElement;
class XmlComment;
class XmlUnknown;
class XmlAttribute;
class XmlText;
class XmlDeclaration;
class XmlParsingData;

const int XML_MAJOR_VERSION = 2;
const int XML_MINOR_VERSION = 6;
const int XML_PATCH_VERSION = 2;

/**
 * @brief Internal structure for tracking location of items in the XML file.
 */
class XmlCursor
{
public:
    XmlCursor() 
    { 
    	clear(); 
    }
	
    void clear() 
    { 
    	m_row = m_col = -1; 
    }

    int m_row;	// 0 based.
    int m_col;	// 0 based.
};

/**
 * @brief Implements the interface to the "Visitor pattern" (see the Accept() method.)
 * If you call the Accept() method, it requires being passed a XmlVisitor
 * class to handle callbacks. For nodes that contain other nodes (Document, Element)
 * you will get called with a VisitEnter/VisitExit pair. Nodes that are always leaves
 * are simply called with Visit().
 * 
 * If you return 'true' from a Visit method, recursive parsing will continue. If you return
 * false, <b>no children of this node or its sibilings</b> will be Visited.
 * 
 * All flavors of Visit methods have a default implementation that returns 'true' (continue 
 * visiting). You need to only override methods that are interesting to you.
 * 
 * Generally Accept() is called on the GXmlDocument, although all nodes suppert Visiting.
 * 
 * You should never change the document from a callback.
 * see XmlNode::Accept()
*/
class XmlVisitor
{
public:
    virtual ~XmlVisitor() {}

    /// Visit a document.
    virtual bool visitEnter(const XmlDocument& /*doc*/) { return true; }
    /// Visit a document.
    virtual bool visitExit(const XmlDocument& /*doc*/)	{ return true; }

    /// Visit an element.
    virtual bool visitEnter(const XmlElement& /*element*/, const XmlAttribute* /*firstAttribute*/) { return true; }
    /// Visit an element.
    virtual bool visitExit(const XmlElement& /*element*/) { return true; }

    /// Visit a declaration
    virtual bool visit(const XmlDeclaration& /*declaration*/) { return true; }
    /// Visit a text node
    virtual bool visit(const XmlText& /*text*/) { return true; }
    /// Visit a comment node
    virtual bool visit(const XmlComment& /*comment*/) { return true; }
    /// Visit an unknown node
    virtual bool visit(const XmlUnknown& /*unknown*/) { return true; }
};

// Only used by Attribute::Query functions
enum 
{
    XML_SUCCESS,
    XML_NO_ATTRIBUTE,
    XML_WRONG_TYPE
};


// Used by the parsing routines.
enum XmlEncoding
{
    XML_ENCODING_UNKNOWN,
    XML_ENCODING_UTF8,
    XML_ENCODING_LEGACY
};

const XmlEncoding XML_DEFAULT_ENCODING = XML_ENCODING_UNKNOWN;

/** 
 * @brief XmlBase is a base class for every class in GnyXml.
 * It does little except to establish that GnyXml classes
 * can be printed and provide some utility functions.
 * 
 * In XML, the document and elements can contain
 * other elements and other types of nodes.
 * 
 * @verbatim
 * A Document can contain:	Element	(container or leaf)
 * Comment (leaf)
 * Unknown (leaf)
 * Declaration( leaf )
 * 
 * An Element can contain:	Element (container or leaf)
 * Text	(leaf)
 * Attributes (not on tree)
 * Comment (leaf)
 * Unknown (leaf)
 * 
 * A Decleration contains: Attributes (not on tree)
 * @endverbatim
 */
class XmlBase
{
    friend class XmlNode;
    friend class XmlElement;
    friend class XmlDocument;

public:
    XmlBase() : m_userData(0) {}
    virtual ~XmlBase() {}

    /**
     * @brief All GnyXml classes can print themselves to a filestream
     * or the string class (GXmlString in non-STL mode, std::string
     * in STL mode.) Either or both cfile and str can be null.
     * 
     * This is a formatted print, and will insert 
     * tabs and newlines.
     * 
     * (For an unformatted stream, use the << operator.)
     */
    virtual void print(FILE* cfile, int depth) const = 0;
    virtual void xmlToStr(std::string& outXml, int depth) const = 0;

    /**	
     * @brief The world does not agree on whether white space should be kept or
     * not. In order to make everyone happy, these global, static functions
     * are provided to set whether or not GnyXml will condense all white space
     * into a single space or not. The default is to condense. Note changing this
     * value is not thread safe.
     */
    static void setCondenseWhiteSpace(bool condense) { m_condenseWhiteSpace = condense; }

    /// Return the current white space setting.
    static bool isWhiteSpaceCondensed() { return m_condenseWhiteSpace; }

    /** Return the position, in the original source file, of this node or attribute.
     * The row and column are 1-based. (That is the first row and first column is
     * 1,1). If the returns values are 0 or less, then the parser does not have
     * a row and column value.
     * 
     * Generally, the row and column value will be set when the GXmlDocument::Load(),
     * GXmlDocument::LoadFile(), or any XmlNode::Parse() is called. It will NOT be set
     * when the DOM was created from operator>>.
     * 
     * The values reflect the initial load. Once the DOM is modified programmatically
     * (by adding or changing nodes and attributes) the new values will NOT update to
     * reflect changes in the document.
     * 
     * There is a minor performance cost to computing the row and column. Computation
     * can be disabled if GXmlDocument::SetTabSize() is called with 0 as the value.
     * 
     * @sa GXmlDocument::SetTabSize()
     */
    int row() const	{ return m_location.m_row + 1; }
    int column() const { return m_location.m_col + 1; }    ///< See Row()

    void setUserData(void* user) { m_userData = user; }	///< Set a pointer to arbitrary user data.
    void* getUserData() { return m_userData; }	///< Get a pointer to arbitrary user data.
    const void* getUserData() const { return m_userData; }	///< Get a pointer to arbitrary user data.

    // Table that returs, for a given lead byte, the total number of bytes
    // in the UTF-8 sequence.
    static const int m_utf8ByteTable[256];

    virtual const char* parse(const char* p, 
        XmlParsingData* data, 
        XmlEncoding encoding /*= XML_ENCODING_UNKNOWN */) = 0;

    /**
     * @brief Expands entities in a string. Note this should not contian the tag's '<', '>', etc, 
     * or they will be transformed into entities!
     */
    static void encodeString(const std::string& str, std::string* out);

    enum
    {
        XML_NO_ERROR = 0,
        XML_ERROR,
        XML_ERROR_OPENING_FILE,
        XML_ERROR_PARSING_ELEMENT,
        XML_ERROR_FAILED_TO_READ_ELEMENT_NAME,
        XML_ERROR_READING_ELEMENT_VALUE,
        XML_ERROR_READING_ATTRIBUTES,
        XML_ERROR_PARSING_EMPTY,
        XML_ERROR_READING_END_TAG,
        XML_ERROR_PARSING_UNKNOWN,
        XML_ERROR_PARSING_COMMENT,
        XML_ERROR_PARSING_DECLARAGON,
        XML_ERROR_DOCUMENT_EMPTY,
        XML_ERROR_EMBEDDED_NULL,
        XML_ERROR_PARSING_CDATA,
        XML_ERROR_DOCUMENT_TOP_ONLY,
        XML_ERROR_STRING_COUNT
    };

protected:
    static const char* skipWhiteSpace(const char*, XmlEncoding encoding);
    static bool isWhiteSpace(char c)		
    { 
    	return (isspace((unsigned char)c) || c == '\n' || c == '\r'); 
    }   
    static bool isWhiteSpace(int c)
    {
    	if (c < 256)
        {
            return isWhiteSpace((char)c);
        }
        
		return false;	// Again, only truly correct for English/Latin...but usually works.
    }
    static bool	streamWhiteSpace(std::istream* in, std::string* tag);
    static bool streamTo(std::istream* in, int character, std::string* tag);

    /**
     * @brief Reads an XML name into the string provided. Returns
     * a pointer just past the last character of the name,
     * or 0 if the function has an error.
     */
    static const char* readName(const char* p, std::string* name, XmlEncoding encoding);

    /**
     * @brief Reads text. Returns a pointer past the given end tag.
     * Wickedly complex options, but it keeps the (sensitive) code in one place.
     */
    static const char* readText(const char* in,				// where to start
        std::string* text,			// the string read
        bool ignoreWhiteSpace,		// whether to keep the white space
        const char* endTag,			// what ends this text
        bool ignoreCase,			// whether to ignore case in the end tag
        XmlEncoding encoding);	// the current encoding

    // If an entity has been found, transform it into a character.
    static const char* getEntity(const char* in, char* value, int* length, XmlEncoding encoding);

    // Get a character, while interpreting entities.
    // The length can be from 0 to 4 bytes.
    static const char* getChar(const char* p, char* value, int* length, XmlEncoding encoding)
    {
    	assert(p);
    	if (encoding == XML_ENCODING_UTF8)
    	{
    	    *length = m_utf8ByteTable[*((const unsigned char*)p)];
    	    assert(*length >= 0 && *length < 5);
    	}
    	else
    	{
    	    *length = 1;
    	}

        if (*length == 1)
        {
            if (*p == '&')
            {
            	return getEntity(p, value, length, encoding);
            }
            *value = *p;
            return p + 1;
        }
        else if (*length)
        {
            // strncpy( _value, p, *length );
            // lots of compilers don't like this function (unsafe),
	    // and the null terminator isn't needed
	    for (int i = 0; p[i] && i < *length; i++) 
            {
            	value[i] = p[i];
            }
            
            return p + (*length);
        }
        else
        {
            // Not valid text.
            return 0;
        }
    }

    // Return true if the next characters in the stream are any of the endTag sequences.
    // Ignore case only works for english, and should only be relied on when comparing
    // to English words: StringEqual( p, "version", true ) is fine.
    static bool stringEqual(const char* p,
        const char* endTag,
        bool ignoreCase,
        XmlEncoding encoding);

    static const char* m_errorString[XML_ERROR_STRING_COUNT];
    XmlCursor m_location;

    /// Field containing a generic user pointer
    void* m_userData;
	
    // None of these methods are reliable for any language except English.
    // Good for approximation, not great for accuracy.
    static int isAlpha(unsigned char anyByte, XmlEncoding encoding);
    static int isAlphaNum(unsigned char anyByte, XmlEncoding encoding);
    static int toLower(int v, XmlEncoding encoding)
    {
    	if (encoding == XML_ENCODING_UTF8)
    	{
    	    if (v < 128) 
    	    {
    	    	return tolower(v);
    	    }
    	    return v;
        }
        else
        {
            return tolower(v);
        }
    }
     
    static void convertUTF32ToUTF8(unsigned long input, char* output, int* length);

private:
    XmlBase(const XmlBase&);    // not implemented.
    void operator = (const XmlBase& base);    // not allowed.

    struct Entity
    {
        const char*     m_str;
        unsigned int    m_strLength;
        char            m_chr;
     };
    
    enum
    {
    	NUM_ENTITY = 5,
    	NUM_ENTITY_LENGTH = 6
    };
    
    static Entity    m_entity[NUM_ENTITY];
    static bool      m_condenseWhiteSpace;
};

/**
 * @brief The parent class for everything in the Document Object Model.
 * (Except for attributes).
 * Nodes have siblings, a parent, and children. A node can be
 * in a document, or stand on its own. The type of a XmlNode
 * can be queried, and it can be cast to its more defined type.
 */
class XmlNode : public XmlBase
{
    friend class XmlDocument;
    friend class XmlElement;

public:
    /**
     * @brief 
     * An input stream operator, for every class. Tolerant of newlines and
     * formatting, but doesn't expect them.
     */
    friend std::istream& operator >> (std::istream& in, XmlNode& base);

    /**
     * @brief An output stream operator, for every class. Note that this outputs
     * without any newlines or formatting, as opposed to Print(), which
     * includes tabs and new lines.
     * 
     * The operator<< and operator>> are not completely symmetric. Writing
     * a node to a stream is very well defined. You'll get a nice stream
     * of output, without any extra whitespace or newlines.
     * 
     * But reading is not as well defined. (As it always is.) If you create
     * a GXmlElement (for example) and read that from an input stream,
     * the text needs to define an element or junk will result. This is
     * true of all input streams, but it's worth keeping in mind.
     * 
     * A GXmlDocument will read nodes until it reads a root element, and
     * all the children of that root element.
     */	
    friend std::ostream& operator << (std::ostream& out, const XmlNode& base);

    /// Appends the XML node or attribute to a std::string.
    friend std::string& operator << (std::string& out, const XmlNode& base);

    /**
     * @brief The types of XML nodes supported by GnyXml. (All the
     * unsupported types are picked up by UNKNOWN.)
     */
    enum NodeType
    {
    	NYXML_DOCUMENT,
    	NYXML_ELEMENT,
    	NYXML_COMMENT,
    	NYXML_UNKNOWN,
    	NYXML_TEXT,
    	NYXML_DECLARAGON,
    	NYXML_TYPECOUNT
    };

    virtual ~XmlNode();

    /**
     * @brief The meaning of 'value' changes for the specific type of
     * XmlNode.
     * @verbatim
     * Document: filename of the xml file
     * Element:	name of the element
     * Comment:	the comment text
     * Unknown:	the tag contents
     * Text: the text string
     * @endverbatim
     * 
     * The subclasses will wrap this function.
     */
    const char* value() const { return m_value.c_str(); }

    /**
     * @brief Return Value() as a std::string. If you only use STL,
     * this is more efficient than calling Value().
     * Only available in STL mode.
     */
    const std::string& valueStr() const { return m_value; }
    const std::string& valueTStr() const { return m_value; }

    /**
     * @brief Changes the value of the node. Defined as:
     * @verbatim
     * Document:	filename of the xml file
     * Element:	name of the element
     * Comment:	the comment text
     * Unknown:	the tag contents
     * Text:		the text string
     * @endverbatim
     */
    void setValue(const char* value) { m_value = value;}

    /// STL std::string form.
    void setValue(const std::string& value) { m_value = value; }

    /// Delete all the children of this node. Does not affect 'this'.
    void clear();

    /// One step up the DOM.
    XmlNode* parent() { return m_parent; }
    const XmlNode* parent() const{ return m_parent; }

    const XmlNode* firstChild() const { return m_firstChild; }	///< The first child of this node. Will be null if there are no children.
    XmlNode* firstChild() { return m_firstChild; }
    const XmlNode* firstChild(const char* value) const;			///< The first child of this node with the matching 'value'. Will be null if none found.
    /// The first child of this node with the matching 'value'. Will be null if none found.
    XmlNode* firstChild(const char* value) 
    {
        // Call through to the const version - safe since nothing is changed. Exiting syntax: cast this to a const (always safe)
        // call the method, cast the return back to non-const.
        return const_cast<XmlNode*>((const_cast<const XmlNode*>(this))->firstChild(value));
    }
    
    const XmlNode* lastChild() const { return m_lastChild; }		/// The last child of this node. Will be null if there are no children.
    XmlNode* lastChild() { return m_lastChild; }
	
    const XmlNode* lastChild(const char* value) const;			/// The last child of this node matching 'value'. Will be null if there are no children.
    XmlNode* lastChild(const char* value) 
    {
    	return const_cast<XmlNode*>((const_cast<const XmlNode*>(this))->lastChild(value));
    }

    const XmlNode* firstChild(const std::string& value) const	
    { 
  	return firstChild(value.c_str ()); 
    }    ///< STL std::string form.
    
    XmlNode* firstChild(const std::string& value)	
    {   
    	return firstChild(value.c_str()); 
    }  ///< STL std::string form.
    
    const XmlNode* lastChild(const std::string& value) const
    { 
    	return lastChild(value.c_str ()); 
    } ///< STL std::string form.
    
    XmlNode* lastChild(const std::string& value)
    {   
    	return lastChild(value.c_str()); 
    }   ///< STL std::string form.

    /**
     * @brief An alternate way to walk the children of a node.
     * One way to iterate over nodes is:
     * @verbatim
     * for( child = parent->FirstChild(); child; child = child->NextSibling() )
     * @endverbatim
     * 
     * IterateChildren does the same thing with the syntax:
     * @verbatim
     * child = 0;
     * while( child = parent->IterateChildren( child ) )
     * @endverbatim
     * 
     * IterateChildren takes the previous child as input and finds
     * the next one. If the previous child is null, it returns the
     * first. IterateChildren will return null when done.
     */
    const XmlNode* iterateChildren(const XmlNode* previous) const;
    XmlNode* iterateChildren(const XmlNode* previous) 
    {
    	return const_cast<XmlNode*>((const_cast<const XmlNode*>(this))->iterateChildren(previous));
    }

    /// This flavor of IterateChildren searches for children with a particular 'value'
    const XmlNode* iterateChildren(const char* value, const XmlNode* previous) const;
    XmlNode* iterateChildren(const char* value, const XmlNode* previous) 
    {
    	return const_cast<XmlNode*>((const_cast<const XmlNode*>(this))->iterateChildren(value, previous));
    }

    const XmlNode* iterateChildren(const std::string& value, const XmlNode* previous) const	
    {   
    	return iterateChildren (value.c_str (), previous); 
    }   ///< STL std::string form.
    
    XmlNode* iterateChildren(const std::string& value, const XmlNode* previous) 
    {   
    	return iterateChildren(value.c_str(), previous); 
    }   ///< STL std::string form.

    /**
     * @brief Add a new node related to this. Adds a child past the LastChild.
     * Returns a pointer to the new object or NULL if an error occured.
     */
    XmlNode* insertEndChild(const XmlNode& addThis);

    /**
     * @brief Add a new node related to this. Adds a child past the LastChild.
     * 
     * NOTE: the node to be added is passed by pointer, and will be
     * henceforth owned (and deleted) by tinyXml. This method is efficient
     * and avoids an extra copy, but should be used with care as it
     * uses a different memory model than the other insert functions.
     * 
     * @sa InsertEndChild
     */
    XmlNode* linkEndChild(XmlNode* addThis);

    /**
     * @brief Add a new node related to this. Adds a child before the specified child.
     * Returns a pointer to the new object or NULL if an error occured.
     */
    XmlNode* insertBeforeChild(XmlNode* beforeThis, const XmlNode& addThis);

    /**
     * @brief Add a new node related to this. Adds a child after the specified child.
     * Returns a pointer to the new object or NULL if an error occured.
     */
    XmlNode* insertAfterChild(XmlNode* afterThis, const XmlNode& addThis);

    /**
     * @brief Replace a child of this node.
     * Returns a pointer to the new object or NULL if an error occured.
     */
    XmlNode* replaceChild(XmlNode* replaceThis, const XmlNode& withThis);

    /// Delete a child of this node.
    bool removeChild(XmlNode* removeThis);

    /// Navigate to a sibling node.
    const XmlNode* previousSibling() const { return m_prev; }
    XmlNode* previousSibling() { return m_prev; }

    /// Navigate to a sibling node.
    const XmlNode* previousSibling(const char* prev) const;
    XmlNode* previousSibling(const char* prev) 
    {
        return const_cast<XmlNode*>((const_cast<const XmlNode*>(this))->previousSibling(prev));
    }

    const XmlNode* previousSibling(const std::string& value) const	
    {   
    	return previousSibling(value.c_str());   
    }   ///< STL std::string form.
    
    XmlNode* previousSibling(const std::string& value) 
    {   
    	return previousSibling(value.c_str()); 
    }   ///< STL std::string form.
    
    const XmlNode* nextSibling(const std::string& value) const		
    {   
    	return nextSibling(value.c_str());   
    }   ///< STL std::string form.
    
    XmlNode* nextSibling(const std::string& value) 
    {   
    	return nextSibling(value.c_str());   
    }   ///< STL std::string form.

    /// Navigate to a sibling node.
    const XmlNode* nextSibling() const { return m_next; }
    XmlNode* nextSibling() { return m_next; }

    /// Navigate to a sibling node with the given 'value'.
    const XmlNode* nextSibling(const char* next) const;
    XmlNode* nextSibling(const char* next) 
    {
    	return const_cast<XmlNode*>((const_cast<const XmlNode*>(this))->nextSibling(next));
    }

    /**
     * @brief Convenience function to get through elements.
     * Calls NextSibling and ToElement. Will skip all non-Element
     * nodes. Returns 0 if there is not another element.
     */
    const XmlElement* nextSiblingElement() const;
    XmlElement* nextSiblingElement() 
    {
    	return const_cast<XmlElement*>((const_cast<const XmlNode*>(this))->nextSiblingElement());
    }

    /**
     * @brief Convenience function to get through elements.
     * Calls NextSibling and ToElement. Will skip all non-Element
     * nodes. Returns 0 if there is not another element.
     */
    const XmlElement* nextSiblingElement(const char* next) const;
    XmlElement* nextSiblingElement(const char* next) 
    {
    	return const_cast<XmlElement*>((const_cast<const XmlNode*>(this))->nextSiblingElement(next));
    }

    const XmlElement* nextSiblingElement( const std::string& value) const	
    {	
    	return nextSiblingElement(value.c_str());	
    }	///< STL std::string form.
    
    XmlElement* nextSiblingElement(const std::string& value)	
    {   
    	return nextSiblingElement(value.c_str());    
    }   ///< STL std::string form.

    /// Convenience function to get through elements.
    const XmlElement* firstChildElement()	const;
    XmlElement* firstChildElement() 
    {
    	return const_cast<XmlElement*>((const_cast<const XmlNode*>(this))->firstChildElement());
    }

    /// Convenience function to get through elements.
    const XmlElement* firstChildElement(const char* value) const;
    XmlElement* firstChildElement(const char* value) 
    {
    	return const_cast<XmlElement*>((const_cast<const XmlNode*>(this))->firstChildElement(value));
    }

    const XmlElement* firstChildElement(const std::string& value) const	
    {   
 	return firstChildElement(value.c_str()); 
    }   ///< STL std::string form.
    
    XmlElement* firstChildElement(const std::string& value)
    {   
    	return firstChildElement(value.c_str()); 
    }   ///< STL std::string form.

    /**
     * @brief Query the type (as an enumerated value, above) of this node.
     * The possible types are: NYXML_DOCUMENT, NYXML_ELEMENT, NYXML_COMMENT,
     * NYXML_UNKNOWN, NYXML_TEXT, and NYXML_DECLARAGON.
     */
    int type() const { return m_type; }

    /**
     * @brief Return a pointer to the Document this node lives in.
     * Returns null if not in a document.
     */
    const XmlDocument* getDocument() const;
    XmlDocument* getDocument() 
    {
    	return const_cast<XmlDocument*>((const_cast<const XmlNode*>(this))->getDocument());
    }

    /// Returns true if this node has no children.
    bool noChildren() const	{ return !m_firstChild; }

    virtual const XmlDocument* toDocument() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual const XmlElement* toElement() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual const XmlComment* toComment() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual const XmlUnknown* toUnknown() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual const XmlText* toText() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual const XmlDeclaration* toDeclaration() const { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

    virtual XmlDocument* toDocument() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual XmlElement* toElement() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual XmlComment* toComment() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual XmlUnknown* toUnknown() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual XmlText* toText() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.
    virtual XmlDeclaration* toDeclaration() { return 0; } ///< Cast to a more defined type. Will return null if not of the requested type.

    /**
     * @brief Create an exact duplicate of this node and return it. The memory must be deleted
     * by the caller. 
     */
    virtual XmlNode* clone() const = 0;

    /**
     * @brief Accept a hierchical visit the nodes in the GnyXML DOM. Every node in the 
     * XML tree will be conditionally visited and the host will be called back
     * via the XmlVisitor interface.
     * 
     * This is essentially a SAX interface for GnyXML. (Note however it doesn't re-parse
     * the XML for the callbacks, so the performance of GnyXML is unchanged by using this
     * interface versus any other.)
     * 
     * The interface has been based on ideas from:
     * 
     * - http://www.saxproject.org/
     * - http://c2.com/cgi/wiki?HierarchicalVisitorPattern 
     * 
     * Which are both good references for "visiting".
     * 
     * An example of using Accept():
     * @verbatim
     * GXmlPrinter printer;\
     * tinyxmlDoc.Accept( &printer );
     * const char* xmlcstr = printer.CStr();
     * @endverbatim
     */
    virtual bool accept(XmlVisitor* visitor) const = 0;

protected:
    XmlNode(NodeType type);

    // Copy to the allocated object. Shared functionality between Clone, Copy constructor,
    // and the assignment operator.
    void copyTo(XmlNode* target) const;

    // The real work of the input operator.
    virtual void streamIn(std::istream* in, std::string* tag) = 0;

    // Figure out what is at *p, and parse it. Returns null if it is not an xml node.
    XmlNode* identify(const char* start, XmlEncoding encoding);

    XmlNode*    m_parent;
    NodeType    m_type;
    XmlNode*    m_firstChild;
    XmlNode*    m_lastChild;
    std::string		 m_value;
    XmlNode*    m_prev;
    XmlNode*    m_next;

private:
    XmlNode(const XmlNode&);				// not implemented.
    void operator = (const XmlNode& base);	// not allowed.
};

/**
 * @brief An attribute is a name-value pair. Elements have an arbitrary
 * number of attributes, each with a unique name.
 * 
 * @note The attributes are not XmlNodes, since they are not
 * part of the tinyXML document object model. There are other
 * suggested ways to look at this problem.
 */
class XmlAttribute : public XmlBase
{
    friend class XmlAttributeSet;

public:
    /// Construct an empty attribute.
    XmlAttribute() : XmlBase()
    {
    	m_document = NULL;
    	m_prev = NULL;
        m_next = NULL;
    }

    /// std::string constructor.
    XmlAttribute(const std::string& name, const std::string& value)
    {
    	m_name = name;
    	m_value = value;
    	m_document = NULL;
    	m_prev = m_next = NULL;
    }

    /// Construct an attribute with a name and value.
    XmlAttribute(const char* name, const char* value)
    {
    	m_name = name;
    	m_value = value;
    	m_document = NULL;
    	m_prev = NULL;
        m_next = NULL;
    }

    const char*	name() const { return m_name.c_str(); }	   ///< Return the name of this attribute.
    const char*	value() const { return m_value.c_str(); }    ///< Return the value of this attribute.
    const std::string& valueStr() const	{ return m_value; }   ///< Return the value of this attribute.
    int	intValue() const;    ///< Return the value of this attribute, converted to an integer.
    double doubleValue() const;	   ///< Return the value of this attribute, converted to a double.

    // Get the tinyxml string representation
    const std::string& nameTStr() const { return m_name; }

    /**
     * @brief QueryIntValue examines the value string. It is an alternative to the
     * IntValue() method with richer error checking.
     * If the value is an integer, it is stored in 'value' and 
     * the call returns XML_SUCCESS. If it is not
     * an integer, it returns XML_WRONG_TYPE.
     * 
     * A specialized but useful call. Note that for success it returns 0,
     * which is the opposite of almost all other GnyXml calls.
     */
    int queryIntValue(int* value) const;
    /// QueryDoubleValue examines the value string. See QueryIntValue().
    int queryDoubleValue(double* value) const;

    ///< Set the name of this attribute.
    void setName(const char* name) { m_name = name; }	
    ///< Set the value.
    void setValue(const char* value) { m_value = value; }
    
    ///< Set the value from an integer.
    void setIntValue(int value);
    ///< Set the value from a double.
    void setDoubleValue(double value);

    /// STL std::string form.
    void setName(const std::string& name) { m_name = name; }	
    /// STL std::string form.	
    void setValue(const std::string& value) { m_value = value; }

    /// Get the next sibling attribute in the DOM. Returns null at end.
    const XmlAttribute* next() const;
    XmlAttribute* next() 
    {
    	return const_cast<XmlAttribute*>((const_cast<const XmlAttribute*>(this))->next()); 
    }

    /// Get the previous sibling attribute in the DOM. Returns null at beginning.
    const XmlAttribute* previous() const;
    XmlAttribute* previous() 
    {
    	return const_cast<XmlAttribute*>((const_cast<const XmlAttribute*>(this))->previous()); 
    }

    bool operator == (const XmlAttribute& rhs) const { return rhs.m_name == m_name; }
    bool operator < (const XmlAttribute& rhs) const { return m_name < rhs.m_name; }
    bool operator > (const XmlAttribute& rhs) const { return m_name > rhs.m_name; }

    /**
     * @brief Attribute parsing starts: first letter of the name
     * returns: the next char after the value end quote
     */
    virtual const char* parse(const char* p, XmlParsingData* data, XmlEncoding encoding);

    // Prints this Attribute to a FILE stream.
    virtual void print(FILE* cfile, int depth) const 
    {
    	print(cfile, depth, 0);
    }
    
    void print(FILE* cfile, int depth, std::string* str) const;
    void xmlToStr(std::string& outXml, int depth) const;
    
    // [internal use]
    // Set the document pointer so the attribute can report errors.
    void setDocument(XmlDocument* doc)	{ m_document = doc; }

private:
    // not implemented.
    XmlAttribute(const XmlAttribute&);		
    // not allowed.
    void operator = (const XmlAttribute& base);	

    // A pointer back to a document, for error reporting.
    XmlDocument*    m_document;	
    std::string     m_name;
    std::string     m_value;
    XmlAttribute*   m_prev;
    XmlAttribute*   m_next;
};

/**
 * @brief A class used to manage a group of attributes.
 * It is only used internally, both by the ELEMENT and the DECLARAGON.
 * 
 * The set can be changed transparent to the Element and Declaration
 * classes that use it, but NOT transparent to the Attribute
 * which has to implement a next() and previous() method. Which makes
 * it a bit problematic and prevents the use of STL.
 * 
 * This version is implemented with circular lists because:
 * - I like circular lists
 * - it demonstrates some independence from the (typical) doubly linked list.
 */
class XmlAttributeSet
{
public:
    XmlAttributeSet();
    ~XmlAttributeSet();

    void add(XmlAttribute* attribute);
    void remove(XmlAttribute* attribute);

    const XmlAttribute* first()const
    { 
    	return (m_sentinel.m_next == &m_sentinel) ? 0 : m_sentinel.m_next; 
    }
    
    XmlAttribute* first()
    { 
    	return (m_sentinel.m_next == &m_sentinel) ? 0 : m_sentinel.m_next; 
    }
    
    const XmlAttribute* last() const
    { 
    	return (m_sentinel.m_prev == &m_sentinel) ? 0 : m_sentinel.m_prev; 
    }
    
    XmlAttribute* last()
    { 
    	return (m_sentinel.m_prev == &m_sentinel) ? 0 : m_sentinel.m_prev; 
    }

    XmlAttribute* find(const char* name) const;
    XmlAttribute* findOrCreate(const char* name);

    XmlAttribute* find(const std::string& name) const;
    XmlAttribute* findOrCreate(const std::string& name);

private:
    //*ME:Because of hidden/disabled copy-construktor in GXmlAttribute (sentinel-element),
    //*ME:	this class must be also use a hidden/disabled copy-constructor !!!
    XmlAttributeSet(const XmlAttributeSet&);	// not allowed
    void operator = (const XmlAttributeSet&);	// not allowed (as GXmlAttribute)

    XmlAttribute m_sentinel;
};

/** 
 * @brief The element is a container class. It has a value, the element name,
 * and can contain other elements, text, comments, and unknowns.
 * Elements also contain an arbitrary number of attributes.
 */
class XmlElement : public XmlNode
{
public:
    /// Construct an element.
    XmlElement(const char* value);

    /// std::string constructor.
    XmlElement(const std::string& value);
    XmlElement(const XmlElement& element);
    XmlElement& operator = (const XmlElement& base);
    virtual ~XmlElement();

    /**
     * @brief Given an attribute name, Attribute() returns the value
     * for the attribute of that name, or null if none exists.
     */
    const char* attribute(const char* name) const;

    /**
     * @brief Given an attribute name, Attribute() returns the value
     * for the attribute of that name, or null if none exists.
     * If the attribute exists and can be converted to an integer,
     * the integer value will be put in the return 'i', if 'i'
     * is non-null.
     */
    const char* attribute(const char* name, int* i) const;

    /**
     * @brief Given an attribute name, Attribute() returns the value
     * for the attribute of that name, or null if none exists.
     * If the attribute exists and can be converted to an double,
     * the double value will be put in the return 'd', if 'd'
     * is non-null.
     */
    const char* attribute(const char* name, double* d) const;

    /**
     * @brief QueryIntAttribute examines the attribute - it is an alternative to the
     * Attribute() method with richer error checking.
     * If the attribute is an integer, it is stored in 'value' and 
     * the call returns XML_SUCCESS. If it is not
     * an integer, it returns XML_WRONG_TYPE. If the attribute
     * does not exist, then XML_NO_ATTRIBUTE is returned.
     */	
    int queryIntAttribute(const char* name, int* value) const;
    /// QueryUnsignedAttribute examines the attribute - see QueryIntAttribute().
    int queryUnsignedAttribute(const char* name, unsigned* value) const;
    /**
     * @brief QueryBoolAttribute examines the attribute - see QueryIntAttribute(). 
     * Note that '1', 'true', or 'yes' are considered true, while '0', 'false'
     * and 'no' are considered false.
     */
    int queryBoolAttribute(const char* name, bool* value) const;
    /// QueryDoubleAttribute examines the attribute - see QueryIntAttribute().
    int queryDoubleAttribute(const char* name, double* value) const;
    /// QueryFloatAttribute examines the attribute - see QueryIntAttribute().
    int queryFloatAttribute(const char* name, float* value) const 
    {
    	double d = 0.0;
    	int result = queryDoubleAttribute(name, &d);
    	if (result == XML_SUCCESS) 
        {
            *value = (float)d;
        }
        
	return result;
    }

    /// QueryStringAttribute examines the attribute - see QueryIntAttribute().
    int queryStringAttribute(const char* name, std::string* value) const 
    {
    	const char* cstr = attribute(name);
    	if (cstr != NULL) 
        {
            *value = std::string(cstr);
            return XML_SUCCESS;
        }
        
        return XML_NO_ATTRIBUTE;
    }

    /**
     * @brief Template form of the attribute query which will try to read the
     * attribute into the specified type. Very easy, very powerful, but
     * be careful to make sure to call this with the correct type.
     * 
     * NOTE: This method doesn't work correctly for 'string' types that contain spaces.
     * 
     * @return XML_SUCCESS, XML_WRONG_TYPE, or XML_NO_ATTRIBUTE
     */
    template<typename T> int queryValueAttribute(const std::string& name, T* outValue) const
    {
    	const XmlAttribute* node = m_attributeSet.find(name);
    	if (node == NULL)
        {
            return XML_NO_ATTRIBUTE;
        }

        std::stringstream sstream(node->valueStr());
        sstream >> *outValue;
        if (!sstream.fail())
        {
            return XML_SUCCESS;
        }
        
        return XML_WRONG_TYPE;
    }

    int queryValueAttribute(const std::string& name, std::string* outValue) const
    {
    	const XmlAttribute* node = m_attributeSet.find(name);
    	if (node == NULL)
        {
            return XML_NO_ATTRIBUTE;
        }
        
        *outValue = node->valueStr();
        return XML_SUCCESS;
    }

    /**
     * @brief Sets an attribute of name to a given value. The attribute
     * will be created if it does not exist, or changed if it does.
     */
    void setAttribute(const char* name, const char* value);
    const std::string* attribute(const std::string& name) const;
    const std::string* attribute(const std::string& name, int* i) const;
    const std::string* attribute(const std::string& name, double* d) const;
    int queryIntAttribute(const std::string& name, int* value) const;
    int queryDoubleAttribute(const std::string& name, double* value) const;

    /// STL std::string form.
    void setAttribute(const std::string& name, const std::string& value);
    ///< STL std::string form.
    void setAttribute(const std::string& name, int value);
    ///< STL std::string form.
    void setDoubleAttribute(const std::string& name, double value);

    /**
     * @brief Sets an attribute of name to a given value. The attribute
     * will be created if it does not exist, or changed if it does.
     */
    void setAttribute(const char* name, int value);

    /**
     * @brief Sets an attribute of name to a given value. The attribute
     * will be created if it does not exist, or changed if it does.
     */
    void setDoubleAttribute(const char* name, double value);

    /**
     * @brief Deletes an attribute with the given name.
    */
    void removeAttribute(const char* name);
    void removeAttribute(const std::string& name) 
    {   
    	removeAttribute(name.c_str());    
    } 

    const XmlAttribute* firstAttribute() const	
    { 
    	return m_attributeSet.first(); 
    } 
    
    XmlAttribute* firstAttribute() 
    { 
    	return m_attributeSet.first(); 
    }
    
    const XmlAttribute* lastAttribute()	const 	
    { 
    	return m_attributeSet.last(); 
    }
    
    XmlAttribute* lastAttribute()					
    { 
    	return m_attributeSet.last(); 
    }

    /**
     * @brief Convenience function for easy access to the text inside an element. Although easy
     * and concise, GetText() is limited compared to getting the XmlText child
     * and accessing it directly.
     * 
     * If the first child of 'this' is a XmlText, the GetText()
     * returns the character string of the Text node, else null is returned.
     * 
     * This is a convenient method for getting the text of simple contained text:
     * @verbatim
     * <foo>This is text</foo>
     * const char* str = fooElement->GetText();
     * @endverbatim
     * 
     * 'str' will be a pointer to "This is text". 
     * 
     * Note that this function can be misleading. If the element foo was created from
     * this XML:
     * @verbatim
     * <foo><b>This is text</b></foo> 
     * @endverbatim
     * 
     * then the value of str would be null. The first child node isn't a text node, it is
     * another element. From this XML:
     * @verbatim
     * <foo>This is <b>text</b></foo> 
     * @endverbatim
     * GetText() will return "This is ".
     * 
     * WARNING: GetText() accesses a child node - don't become confused with the 
     * similarly named GXmlHandle::Text() and XmlNode::ToText() which are 
     * safe type casts on the referenced node.
     */
    const char* getText() const;
	void setText(const char* value);

    /// Creates a new Element and returns it - the returned element is a copy.
    virtual XmlNode* clone() const;
    // Print the Element to a FILE stream.
    virtual void print(FILE* cfile, int depth) const;
    virtual void xmlToStr(std::string& outXml, int depth) const;

    /**
     * @brief Attribtue parsing starts: next char past '<'
     * returns: next char past '>'
     */
    virtual const char* parse(const char* p, XmlParsingData* data, XmlEncoding encoding);
    virtual const XmlElement* toElement() const { return this; } ///< Cast to a more defined type. Will return null not of the requested type.
    virtual XmlElement* toElement() { return this; } ///< Cast to a more defined type. Will return null not of the requested type.

    /**
     * @brief Walk the XML tree visiting this node and all of its children. 
     */
    virtual bool accept(XmlVisitor* visitor) const;

protected:
    void copyTo(XmlElement* target) const;
    void clearThis();	// like clear, but initializes 'this' object as well

    // Used to be public [internal use]
    virtual void streamIn(std::istream* in, std::string* tag);

    /**
     * @brief [internal use]
     * Reads the "value" of the element -- another element, or text.
     * This should terminate with the current end tag.
     */
    const char* readValue(const char* in, XmlParsingData* prevData, XmlEncoding encoding);

private:
    XmlAttributeSet m_attributeSet;
};

/**
 * @brief An XML comment.
 */
class XmlComment : public XmlNode
{
public:
    /// Constructs an empty comment.
    XmlComment() : XmlNode(XmlNode::NYXML_COMMENT) {}
    
    /// Construct a comment from text.
    XmlComment(const char* value) : XmlNode(XmlNode::NYXML_COMMENT) 
    {
    	setValue(value);
    }
    
    XmlComment(const XmlComment&);
    XmlComment& operator=(const XmlComment& base);

    virtual ~XmlComment() {}

    /// Returns a copy of this Comment.
    virtual XmlNode* clone() const;
    // Write this Comment to a FILE stream.
    virtual void print(FILE* cfile, int depth) const;
    void xmlToStr(std::string& outXml, int depth) const;

    /**
     * @brief Attribtue parsing starts: at the ! of the !--
     * returns: next char past '>'
     */
    virtual const char* parse(const char* p, XmlParsingData* data, XmlEncoding encoding);

    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual const XmlComment* toComment() const { return this; } 
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual XmlComment* toComment() { return this; } 

    /**
     * @brief Walk the XML tree visiting this node and all of its children. 
     */
    virtual bool accept(XmlVisitor* visitor) const;

protected:
    void copyTo(XmlComment* target) const;

    // used to be public
    virtual void streamIn(std::istream* in, std::string* tag);
};

/**
 * @brief XML text. A text node can have 2 ways to output the next. "normal" output 
 * and CDATA. It will default to the mode it was parsed from the XML file and
 * you generally want to leave it alone, but you can change the output mode with 
 * SetCDATA() and query it with CDATA().
 */
class XmlText : public XmlNode
{
    friend class XmlElement;
    
public:
    /**
     * @brief Constructor for text element. By default, it is treated as 
     * normal, encoded text. If you want it be output as a CDATA text
     * element, set the parameter _cdata to 'true'
     */
    XmlText(const char* initValue) : XmlNode(XmlNode::NYXML_TEXT)
    {
        setValue(initValue);
     	m_cdata = false;
    }
    
    virtual ~XmlText() {}

    /// Constructor.
    XmlText(const std::string& initValue) : XmlNode(XmlNode::NYXML_TEXT)
    {
    	setValue(initValue);
    	m_cdata = false;
    }

    XmlText(const XmlText& copy) : XmlNode(XmlNode::NYXML_TEXT)	
    { 
    	copy.copyTo(this); 
    }
    
    XmlText& operator = (const XmlText& base)	
    { 
    	base.copyTo(this); 
        return *this; 
    }

    // Write this text object to a FILE stream.
    virtual void print(FILE* cfile, int depth) const;
    virtual void xmlToStr(std::string& outXml, int depth) const;

    /// Queries whether this represents text using a CDATA section.
    bool cdata() const { return m_cdata; }
    /// Turns on or off a CDATA representation of text.
    void setCdata(bool cdata) { m_cdata = cdata; }

    virtual const char* parse(const char* p, XmlParsingData* data, XmlEncoding encoding);
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual const XmlText* toText() const { return this; } 
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual XmlText* toText() { return this; } 

    /**
     * @brief Walk the XML tree visiting this node and all of its children. 
     */
    virtual bool accept(XmlVisitor* content) const;

protected :
    ///  [internal use] Creates a new Element and returns it.
    virtual XmlNode* clone() const;
    void copyTo(XmlText* target) const;

    // returns true if all white space and new lines
    bool blank() const;	
    // [internal use]
    virtual void streamIn(std::istream* in, std::string* tag);

private:
    // true if this should be input and output as a CDATA style text element
    bool m_cdata;			
};

/**
 * @brief In correct XML the declaration is the first entry in the file.
 * @verbatim
 * <?xml version="1.0" standalone="yes"?>
 * @endverbatim
 * 
 * GnyXml will happily read or write files without a declaration,
 * however. There are 3 possible attributes to the declaration:
 * version, encoding, and standalone.
 * 
 * Note: In this version of the code, the attributes are
 * handled as special cases, not generic attributes, simply
 * because there can only be at most 3 and they are always the same.
 */
class XmlDeclaration : public XmlNode
{
public:
    /// Construct an empty declaration.
    XmlDeclaration() : XmlNode(XmlNode::NYXML_DECLARAGON) {}

    /// Constructor.
    XmlDeclaration(const std::string& version,
        const std::string& encoding,
        const std::string& standalone);

    /// Construct.
    XmlDeclaration(const char* version,
        const char* encoding,
        const char* standalone);

    XmlDeclaration(const XmlDeclaration& copy);
    XmlDeclaration& operator = (const XmlDeclaration& copy);

    virtual ~XmlDeclaration() {}

    /// Version. Will return an empty string if none was found.
    const char* version() const { return m_version.c_str(); }
    /// Encoding. Will return an empty string if none was found.
    const char* encoding() const { return m_encoding.c_str(); }
    /// Is this a standalone document?
    const char* standalone() const { return m_standalone.c_str(); }

    /// Creates a copy of this Declaration and returns it.
    virtual XmlNode* clone() const;
    // Print this declaration to a FILE stream.
    virtual void print(FILE* cfile, int depth, std::string* str) const;
    virtual void print(FILE* cfile, int depth) const 
    {
    	print(cfile, depth, 0);
    }
    void xmlToStr(std::string& outXml, int depth) const;

    virtual const char* parse(const char* p, XmlParsingData* data, XmlEncoding encoding);
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual const XmlDeclaration* toDeclaration() const { return this; } 
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual XmlDeclaration* toDeclaration() { return this; } 

    /**
     * @brief Walk the XML tree visiting this node and all of its children. 
     */
    virtual bool accept(XmlVisitor* visitor) const;

protected:
    void copyTo(XmlDeclaration* target) const;
    // used to be public
    virtual void streamIn(std::istream* in, std::string* tag);

private:
    std::string m_version;
    std::string m_encoding;
    std::string m_standalone;
};

/**
 * @brief Any tag that tinyXml doesn't recognize is saved as an
 * unknown. It is a tag of text, but should not be modified.
 * It will be written back to the XML, unchanged, when the file
 * is saved.
 * 
 * DTD tags get thrown into GXmlUnknowns.
 */
class XmlUnknown : public XmlNode
{
public:
    XmlUnknown() : XmlNode(XmlNode::NYXML_UNKNOWN) {}
    virtual ~XmlUnknown() {}

    XmlUnknown(const XmlUnknown& copy) : XmlNode(XmlNode::NYXML_UNKNOWN)		
    { 
    	copy.copyTo(this); 
    }
    
    XmlUnknown& operator = (const XmlUnknown& copy)										
    { 
    	copy.copyTo(this); 
        return *this; 
    }

    /// Creates a copy of this Unknown and returns it.
    virtual XmlNode* clone() const;
    // Print this Unknown to a FILE stream.
    virtual void print(FILE* cfile, int depth) const;
    virtual void xmlToStr(std::string& outXml, int depth) const;
    virtual const char* parse(const char* p, XmlParsingData* data, XmlEncoding encoding);
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual const XmlUnknown* toUnknown() const { return this; } 
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual XmlUnknown* toUnknown() { return this; } 

    /**
     * @brief Walk the XML tree visiting this node and all of its children. 
     */
    virtual bool accept(XmlVisitor* content) const;

protected:
    void copyTo(XmlUnknown* target) const;
    virtual void streamIn(std::istream* in, std::string* tag);
};

/** 
 * @brief Always the top level node. A document binds together all the
 * XML pieces. It can be saved, loaded, and printed to the screen.
 * The 'value' of a document node is the xml file name.
 */
class XmlDocument : public XmlNode
{
public:
    /// Create an empty document, that has no name.
    XmlDocument();
    /// Create a document with a name. The name of the document is also the filename of the xml.
    XmlDocument(const char* documentName);

    /// Constructor.
    XmlDocument(const std::string& documentName);
    XmlDocument(const XmlDocument& copy);
    XmlDocument& operator = (const XmlDocument& copy);

    virtual ~XmlDocument() {}

    /**
     * @brief Load a file using the current document value.
     * Returns true if successful. Will delete any existing
     * document data before loading.
     */
    bool loadFile(XmlEncoding encoding = XML_DEFAULT_ENCODING);
    /// Save a file using the current document value. Returns true if successful.
    bool saveFile() const;
    /// Load a file using the given filename. Returns true if successful.
    bool loadFile(const char* filename, XmlEncoding encoding = XML_DEFAULT_ENCODING);
    /// Save a file using the given filename. Returns true if successful.
    bool saveFile(const char* filename) const;
    /**
     * @brief Load a file using the given FILE*. Returns true if successful. Note that this method
     * doesn't stream - the entire object pointed at by the FILE*
     * will be interpreted as an XML file. GnyXML doesn't stream in XML from the current
     * file location. Streaming may be added in the future.
     */
    bool loadFile(FILE* file, XmlEncoding encoding = XML_DEFAULT_ENCODING);
	bool load(const char* content, const unsigned int length, XmlEncoding encoding = XML_DEFAULT_ENCODING);
    /// Save a file using the given FILE*. Returns true if successful.
    bool saveFile(FILE* file) const;
    ///< STL std::string version.
    bool loadFile(const std::string& filename, XmlEncoding encoding = XML_DEFAULT_ENCODING)			
    {
    	return loadFile(filename.c_str(), encoding);
    }
    
    ///< STL std::string version.
    bool saveFile(const std::string& filename) const		
    {
    	return saveFile(filename.c_str());
    }

    /**
     * @brief Parse the given null terminated block of xml data. Passing in an encoding to this
     * method (either XML_ENCODING_LEGACY or XML_ENCODING_UTF8 will force Xml
     * to use that encoding, regardless of what GnyXml might otherwise try to detect.
     */
    virtual const char* parse(const char* p, XmlParsingData* data = 0, XmlEncoding encoding = XML_DEFAULT_ENCODING);

    /**
     * @brief Get the root element -- the only top level element -- of the document.
     * In well formed XML, there should only be one. GnyXml is tolerant of
     * multiple elements at the document level.
     */
    const XmlElement* rootElement() const { return firstChildElement(); }
    XmlElement* rootElement() { return firstChildElement(); }

    /**
     * @brief If an error occurs, Error will be set to true. Also,
     * - The ErrorId() will contain the integer identifier of the error (not generally useful)
     * - The ErrorDesc() method will return the name of the error. (very useful)
     * - The ErrorRow() and ErrorCol() will return the location of the error (if known)
     */	
    bool error() const { return m_error; }

    /// Contains a textual (english) description of the error if one occurs.
    const char* errorDesc() const { return m_errorDesc.c_str(); }

    /**
     * @brief Generally, you probably want the error string ( ErrorDesc() ). But if you
     * prefer the ErrorId, this function will fetch it.
     */
    int errorId() const { return m_errorId; }

    /**
     * @brief Returns the location (if known) of the error. The first column is column 1, 
     * and the first row is row 1. A value of 0 means the row and column wasn't applicable
     * (memory errors, for example, have no row/column) or the parser lost the error. (An
     * error in the error reporting, in that case.)
     * 
     * @sa SetTabSize, Row, Column
     */
    int errorRow() const { return m_errorLocation.m_row + 1; }
    ///< The column where the error occured. See ErrorRow()
    int errorCol() const { return m_errorLocation.m_col + 1; }	

    /**
     * @brief SetTabSize() allows the error reporting functions (ErrorRow() and ErrorCol())
     * to report the correct values for row and column. It does not change the output
     * or input in any way.
     * 
     * By calling this method, with a tab size
     * greater than 0, the row and column of each node and attribute is stored
     * when the file is loaded. Very useful for tracking the DOM back in to
     * the source file.
     * 
     * The tab size is required for calculating the location of nodes. If not
     * set, the default of 4 is used. The tabsize is set per document. Setting
     * the tabsize to 0 disables row/column tracking.
     * 
     * Note that row and column tracking is not supported when using operator>>.
     * 
     * The tab size needs to be enabled before the parse or load. Correct usage:
     * @verbatim
     * GXmlDocument doc;
     * doc.SetTabSize( 8 );
     * doc.Load( "myfile.xml" );
     * @endverbatim
     * 
     * @sa Row, Column
     */
    void setTabSize(int tabsize) { m_tabsize = tabsize; }

    int tabSize() const	{ return m_tabsize; }

    /**
     * @brief If you have handled the error, it can be reset with this call. The error
     * state is automatically cleared if you Parse a new XML block.
     */
    void clearError()						
    {	
        m_error = false; 
        m_errorId = 0; 
        m_errorDesc = ""; 
        m_errorLocation.m_row = 0;
        m_errorLocation.m_col = 0; 
    }

    // Write the document to standard out using formatted printing ("pretty print").
    void print() const { print(stdout, 0); }
    // return really size
    void xmlToStr(std::string& outXml) const { xmlToStr(outXml, 0); }

    /**
     * @brief Write the document to a string using formatted printing ("pretty print"). This
     * will allocate a character array (new char[]) and return it as a pointer. The
     * calling code pust call delete[] on the return char* to avoid a memory leak.
     */
     //char* PrintToMemory() const; 

    /// Print this Document to a FILE stream.
    virtual void print(FILE* cfile, int depth = 0) const;
    void xmlToStr(std::string& outXml, int depth) const;
    
    // [internal use]
    void setError(int err, 
        const char* errorLocation, 
        XmlParsingData* prevData, 
        XmlEncoding encoding);

    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual const XmlDocument* toDocument() const { return this; } 
    ///< Cast to a more defined type. Will return null not of the requested type.
    virtual XmlDocument* toDocument() { return this; } 

    // Walk the XML tree visiting this node and all of its children. 
    virtual bool accept(XmlVisitor* content) const;

protected :
    // [internal use]
    virtual XmlNode* clone() const;
    virtual void streamIn(std::istream* in, std::string* tag);

private:
    void copyTo(XmlDocument* target) const;

    bool        m_error;
    int         m_errorId;
    std::string m_errorDesc;
    int         m_tabsize;
    XmlCursor   m_errorLocation;
    bool        m_useMicrosoftBOM;		// the UTF-8 BOM were found when read. Note this, and try to write.
};

/**
 * @brief A GXmlHandle is a class that wraps a node pointer with null checks; this is
 * an incredibly useful thing. Note that GXmlHandle is not part of the GnyXml
 * DOM structure. It is a separate utility class.
 * 
 * Take an example:
 * @verbatim
 * <Document>
 * <Element attributeA = "valueA">
 * <Child attributeB = "value1" />
 * <Child attributeB = "value2" />
 * </Element>
 * <Document>
 * @endverbatim
 * 
 * Assuming you want the value of "attributeB" in the 2nd "Child" element, it's very 
 * easy to write a *lot* of code that looks like:
 * 
 * @verbatim
 */
 /*
GXmlElement* root = document.FirstChildElement( "Document" );
if ( root )
{
GXmlElement* element = root->FirstChildElement( "Element" );
if ( element )
{
	GXmlElement* child = element->FirstChildElement( "Child" );
	if ( child )
	{
		GXmlElement* child2 = child->NextSiblingElement( "Child" );
		if ( child2 )
		{
			// Finally do something useful.
	@endverbatim

	And that doesn't even cover "else" cases. GXmlHandle addresses the verbosity
	of such code. A GXmlHandle checks for null	pointers so it is perfectly safe 
	and correct to use:

	@verbatim
	GXmlHandle docHandle( &document );
	GXmlElement* child2 = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", 1 ).ToElement();
	if ( child2 )
	{
		// do something useful
	@endverbatim

	Which is MUCH more concise and useful.

	It is also safe to copy handles - internally they are nothing more than node pointers.
	@verbatim
	GXmlHandle handleCopy = handle;
	@endverbatim

	What they should not be used for is iteration:

	@verbatim
	int i=0; 
	while ( true )
	{
		GXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).Child( "Child", i ).ToElement();
		if ( !child )
			break;
		// do something
		++i;
	}
	@endverbatim

	It seems reasonable, but it is in fact two embedded while loops. The Child method is 
	a linear walk to find the element, so this code would iterate much more than it needs 
	to. Instead, prefer:

	@verbatim
	GXmlElement* child = docHandle.FirstChild( "Document" ).FirstChild( "Element" ).FirstChild( "Child" ).ToElement();

	for( child; child; child=child->NextSiblingElement() )
	{
		// do something
	}
	@endverbatim
*/
class XmlHandle
{
public:
    /// Create a handle from any node (at any depth of the tree.) This can be a null pointer.
    XmlHandle(XmlNode* node) { m_node = node; }
    /// Copy constructor
    XmlHandle(const XmlHandle& ref) { m_node = ref.m_node; }
    XmlHandle operator=(const XmlHandle& ref) 
    { 
    	if (&ref != this) 
        {
            m_node = ref.m_node;
            return *this; 
        }
    }

    /// Return a handle to the first child node.
    XmlHandle firstChild() const;
    /// Return a handle to the first child node with the given name.
    XmlHandle firstChild(const char* value) const;
    /// Return a handle to the first child element.
    XmlHandle firstChildElement() const;
    /// Return a handle to the first child element with the given name.
    XmlHandle firstChildElement(const char* value) const;

    /**
     * @brief Return a handle to the "index" child with the given name. 
     * The first child is 0, the second 1, etc.
     */
    XmlHandle child(const char* value, int index) const;
    
    /**
     * @brief Return a handle to the "index" child. 
     * The first child is 0, the second 1, etc.
     */
    XmlHandle child(int index) const;

    /**
     * @brief Return a handle to the "index" child element with the given name. 
     * The first child element is 0, the second 1, etc. Note that only GXmlElements
     * are indexed: other types are not counted.
     */
    XmlHandle childElement(const char* value, int index) const;

    /**
     * @brief Return a handle to the "index" child element. 
     * The first child element is 0, the second 1, etc. Note that only GXmlElements
     * are indexed: other types are not counted.
     */
    XmlHandle childElement(int index) const;

    XmlHandle firstChild(const std::string& value) const 
    { 
    	return firstChild(value.c_str()); 
    }
    
    XmlHandle firstChildElement(const std::string& value) const 
    { 
    	return firstChildElement(value.c_str()); 
    }

    XmlHandle child(const std::string& value, int index) const			
    { 
    	return child(value.c_str(), index); 
    }
    
    XmlHandle childElement(const std::string& value, int index) const	
    { 
    	return childElement(value.c_str(), index); 
    }

    /**
     * @brief Return the handle as a XmlNode. This may return null
     */
    XmlNode* toNode() const { return m_node; } 

    /**
     * @brief Return the handle as a GXmlElement. This may return null.
     */
    XmlElement* toElement() const 
    { 
        return ((m_node && m_node->toElement()) ? m_node->toElement() : 0); 
    }
    
    /**
     * @brief Return the handle as a XmlText. This may return null.
     */
    XmlText* toText() const			
    { 
    	return ((m_node && m_node->toText()) ? m_node->toText() : 0); 
    }
    
    /**
     * @brief Return the handle as a GXmlUnknown. This may return null.
    */
    XmlUnknown* toUnknown() const	
    { 
    	return ((m_node && m_node->toUnknown() ) ? m_node->toUnknown() : 0); 
    }

    /**
     * @brief @deprecated use ToNode. 
     * Return the handle as a XmlNode. This may return null.
     */
    XmlNode* node() const { return toNode(); } 

    /**
     * @deprecated use ToElement. 
     * Return the handle as a GXmlElement. This may return null.
     */
    XmlElement* element() const { return toElement(); }

    /**
     * @brief 
     * @deprecated use ToText()
     * Return the handle as a XmlText. This may return null.
     */
    XmlText* text() const { return toText(); }
    
    /**
     * @deprecated use ToUnknown()
     * Return the handle as a GXmlUnknown. This may return null.
     */
    XmlUnknown* unknown() const { return toUnknown(); }

private:
    XmlNode* m_node;
};

/**
 * @brief Print to memory functionality. The GXmlPrinter is useful when you need to:
 * 
 * -# Print to memory (especially in non-STL mode)
 * -# Control formatting (line endings, etc.)
 * 
 * When constructed, the GXmlPrinter is in its default "pretty printing" mode.
 * Before calling Accept() you can call methods to control the printing
 * of the XML document. After XmlNode::Accept() is called, the printed document can
 * be accessed via the CStr(), Str(), and Size() methods.
 * 
 * GXmlPrinter uses the Visitor API.
 * @verbatim
 * GXmlPrinter printer;
 * printer.SetIndent( "\t" );
 * 
 * doc.Accept( &printer );
 * fprintf( stdout, "%s", printer.CStr() );
 * @endverbatim
 */ 
class XmlPrinter : public XmlVisitor
{
public:
    XmlPrinter() 
        : m_depth(0)
        , m_simpleTextPrint(false)
        , m_buffer()
        , m_indent("")
        , m_lineBreak("\n") {}

    virtual bool visitEnter(const XmlDocument& doc);
    virtual bool visitExit(const XmlDocument& doc);
	
    virtual bool visitEnter(const XmlElement& element, const XmlAttribute* firstAttribute);
    virtual bool visitExit(const XmlElement& element);

    virtual bool visit(const XmlDeclaration& declaration);
    virtual bool visit(const XmlText& text);
    virtual bool visit(const XmlComment& comment);
    virtual bool visit(const XmlUnknown& unknown);

    /**
     * @brief Set the indent characters for printing. By default 4 spaces
     * but tab (\t) is also useful, or null/empty string for no indentation.
     */
    void setIndent(const char* indent)	{ m_indent = indent ? indent : ""; }
    /// Query the indention string.
    const char* indent() { return m_indent.c_str(); }
    
    /**
     * @brief Set the line breaking string. By default set to newline (\n). 
     * Some operating systems prefer other characters, or can be
     * set to the null/empty string for no indenation.
     */
    void setLineBreak(const char* lineBreak) { m_lineBreak = lineBreak ? lineBreak : ""; }
    /// Query the current line breaking string.
    const char* lineBreak() { return m_lineBreak.c_str(); }

    /**
     * @brief Switch over to "stream printing" which is the most dense formatting without 
     * linebreaks. Common when the XML is needed for network transmission.
     */
    void setStreamPrinting()						
    { 
    	m_indent = "";
    	m_lineBreak = "";
    }	
    
    /// Return the result.
    const char* cStr() { return m_buffer.c_str(); }
    /// Return the length of the result string.
    size_t size() { return m_buffer.size(); }

    /// Return the result.
    const std::string& str() { return m_buffer; }

private:
    void doIndent()	
    {
        for (int i = 0; i < m_depth; i++)
        {
            m_buffer += m_indent;
        }
    }
    
    void doLineBreak() 
    {
    	m_buffer += m_lineBreak;
    }

    int	        m_depth;
    bool		m_simpleTextPrint;
    std::string m_buffer;
    std::string m_indent;
    std::string m_lineBreak;
};
}

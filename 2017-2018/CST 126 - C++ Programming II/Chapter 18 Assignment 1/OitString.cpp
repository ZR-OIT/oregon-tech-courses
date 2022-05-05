/****************************************************************************************************
* Author: Zak Rowland
* Filename: OitString.cpp
* Date Created: 2/26/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 18 Assignment 1 - Part 1
*
* Overview: Using the attached files for the OitString class, implement the methods from OitString.h
*			in yourown OitString.cpp file.
*
* Input:    Data from main.cpp
*
* Output:   Strings
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include "OitString.h"
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: OitString(void)
* Purpose: Default constructor 
*****************************************************************************************************/
OitString::OitString(void): OitString("")
{
}

/*****************************************************************************************************
* Function: OitString(const char * str)
* Purpose: Overloaded constructor
*****************************************************************************************************/
OitString::OitString(const char * str)
{
	m_length = strlen(str);
	m_str = new char[strlen(str) + 1];
	strcpy(m_str, str);

	m_delim = nullptr;
	m_tokenizedStr = nullptr;
	m_currToken = nullptr;
	m_nextToken = nullptr;
}

/*****************************************************************************************************
* Function: OitString(const OitString & os)
* Purpose: Copy constructor
*****************************************************************************************************/
OitString::OitString(const OitString & os) : OitString(os.m_str)
{
}

/*****************************************************************************************************
* Function: ~OitString(void)
* Purpose: Destructor
*****************************************************************************************************/
OitString::~OitString(void)
{
	delete[] m_str;
	m_str = nullptr;

	clearTokens();
}

/*****************************************************************************************************
* Function: OitString::set(const char * str)
* Purpose: Setter using a string
*****************************************************************************************************/
void OitString::set(const char * str)
{
	if (strcmp(str, m_str) != 0)
	{
		m_length = strlen(str);
		delete[] m_str;
		m_str = new char[strlen(str) + 1];
		strcpy(m_str, str);
	}
}

/*****************************************************************************************************
* Function: OitString::set(const OitString & os)
* Purpose: Setter using a class object
*****************************************************************************************************/
void OitString::set(const OitString & os)
{
	set(os.m_str);
}

/*****************************************************************************************************
* Function: OitString::operator=(const char * str)
* Purpose: = operator for a string
*****************************************************************************************************/
OitString & OitString::operator=(const char * str)
{
	if (str != this->m_str)
	{
		set(str);
	}
	return *this;
}

/*****************************************************************************************************
* Function: OitString::operator=(const OitString & os)
* Purpose: = opterator for a class object
*****************************************************************************************************/
OitString & OitString::operator=(const OitString & os)
{
	if (this != &os)
	{
		set(os.m_str);
	}
	return *this;
}

/*****************************************************************************************************
* Function: OitString::length(void)
* Purpose: Returns m_length
*****************************************************************************************************/
size_t OitString::length(void) const
{
	return m_length;
}

/*****************************************************************************************************
* Function: OitString::append(const char * str)
* Purpose: Appends a string
*****************************************************************************************************/
void OitString::append(const char * str)
{
	char *str_ptr;

	m_length = strlen(m_str) + strlen(str);

	str_ptr = new char[m_length + 1];

	strcpy(str_ptr, m_str);
	strcat(str_ptr, str);

	delete[] m_str;
	m_str = str_ptr;
}

/*****************************************************************************************************
* Function: OitString::append(char ch)
* Purpose: Appends a character
*****************************************************************************************************/
void OitString::append(char ch)
{
	char c[] = { ch,'\0' };
	append(c);
}

/*****************************************************************************************************
* Function: OitString::append(const OitString & os)
* Purpose: Appends data from a class object
*****************************************************************************************************/
void OitString::append(const OitString & os)
{
	append(os.m_str);
}

/*****************************************************************************************************
* Function: OitString::prepend(const char * str)
* Purpose: Preprends a string
*****************************************************************************************************/
void OitString::prepend(const char * str)
{
	char *str_ptr;

	m_length = strlen(m_str) + strlen(str);

	str_ptr = new char[m_length + 1];

	strcpy(str_ptr, str);
	strcat(str_ptr, m_str);

	delete[] m_str;
	m_str = str_ptr;
}

/*****************************************************************************************************
* Function: OitString::prepend(char ch)
* Purpose: Prepends a character
*****************************************************************************************************/
void OitString::prepend(char ch)
{
	char c[] = { ch,'\0' };
	prepend(c);
}

/*****************************************************************************************************
* Function: OitString::prepend(const OitString & os)
* Purpose: Prepends data from a class object
*****************************************************************************************************/
void OitString::prepend(const OitString & os)
{
	prepend(os.m_str);
}

/*****************************************************************************************************
* Function: OitString::c_str(void)
* Purpose: Returns m_str
*****************************************************************************************************/
char * OitString::c_str(void) const
{
	return this->m_str;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//******************************************NEW*****************************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************************************************************************
* Function: OitString::at(size_t pos)
* Purpose: Return character at the given position. If position is outside length of m_str, return '\0'
*****************************************************************************************************/
char OitString::at(size_t pos) const
{
	char c = '\0';

	if (pos >= 0 && pos < m_length)
		c = m_str[pos];

	return c;
}

/*****************************************************************************************************
* Function: OitString::at(size_t pos)
* Purpose: Return a reference to a character at a given position. This can be used as an l-value.
*****************************************************************************************************/
char & OitString::at(size_t pos)
{
	return this->m_str[pos];
}

/*****************************************************************************************************
* Function: OitString::upper(size_t pos)
* Purpose: Change the case of the given character to upper
*****************************************************************************************************/
void OitString::upper(size_t pos)
{
	m_str[pos] = toupper(at(pos));
}

/*****************************************************************************************************
* Function: OitString::lower(size_t pos)
* Purpose: Change the case of the given character to lower
*****************************************************************************************************/
void OitString::lower(size_t pos)
{
	m_str[pos] = tolower(at(pos));
}

/*****************************************************************************************************
* Function: OitString::upper(void)
* Purpose: Change the case of the entire internal cString to upper
*****************************************************************************************************/
void OitString::upper(void)
{
	for (unsigned int i = 0; i < m_length; i++)
		upper(i);
}

/*****************************************************************************************************
* Function: OitString::lower(void)
* Purpose: Change the case of the entire internal cString to lower
*****************************************************************************************************/
void OitString::lower(void)
{
	for (unsigned int i = 0; i < m_length; i++)
		lower(i);
}

/*****************************************************************************************************
* Function: OitString::reverse(void)
* Purpose: Reverse the internal cString
*****************************************************************************************************/
void OitString::reverse(void)
{
	_strrev(m_str);
}

/*****************************************************************************************************
* Function: OitString::compare(const char * str)
* Purpose: Behave like the strcmp() function using a string
*****************************************************************************************************/
int OitString::compare(const char * str) const
{
	return strcmp(m_str, str);
}

/*****************************************************************************************************
* Function: OitString::compare(const OitString & os)
* Purpose: Behave like the strcmp() fucntion using a class object
*****************************************************************************************************/
int OitString::compare(const OitString & os) const
{
	return compare(os.m_str);
}

/*****************************************************************************************************
* Function: OitString::isEmpty(void)
* Purpose: Return true if the length of the internal cString == 0
*****************************************************************************************************/
bool OitString::isEmpty(void) const
{
	bool empty = false;

	if (strlen(m_str) == 0)
		empty = true;

	return empty;
}

/*****************************************************************************************************
* Function: OitString::find(const char ch)
* Purpose: Locate the character within the cString internal structure
*****************************************************************************************************/
char * OitString::find(const char ch) const
{
	return strchr(m_str, ch);
}

/*****************************************************************************************************
* Function: OitString::find(const char * str)
* Purpose: Locate the cString within the cString internal structure
*****************************************************************************************************/
char * OitString::find(const char * str) const
{
	return strstr(m_str, str);
}

/*****************************************************************************************************
* Function: OitString::swap(OitString & os)
* Purpose: Exchange the internal cStrings m_str's between the 2 objects
*****************************************************************************************************/
void OitString::swap(OitString & os)
{
	char *ptr;
	char *ptr2;

	ptr = m_str;
	ptr2 = os.m_str;

	m_str = ptr2;
	os.m_str = ptr;

	ptr = nullptr;
	ptr2 = nullptr;

}

/*****************************************************************************************************
* Function: OitString::tokenize(const char * delim)
* Purpose: Loop through the pieces of the internal cString
*****************************************************************************************************/
void OitString::tokenize(const char * delim)
{
	m_delim = new char[strlen(delim) + 1];
	strcpy(m_delim, delim);

	m_tokenizedStr = new char[m_length + 1];
	strcpy(m_tokenizedStr, m_str);

	m_currToken = strtok_s(m_tokenizedStr, m_delim, &m_nextToken);
}

/*****************************************************************************************************
* Function: OitString::nextToken(void)
* Purpose: Get the next token in the string
*****************************************************************************************************/
char * OitString::nextToken(void)
{	
	char *temp = nullptr;

	if (m_tokenizedStr == nullptr)
	{
		tokenize();
	}

	temp = m_currToken;
	m_currToken = strtok_s(nullptr, m_delim, &m_nextToken);

	return temp;
}

/*****************************************************************************************************
* Function: OitString::clearTokens(void)
* Purpose: Cleanup tokens
*****************************************************************************************************/
void OitString::clearTokens(void)
{
	delete[] m_delim;
	delete[] m_tokenizedStr;

	m_delim = nullptr;
	m_tokenizedStr = nullptr;
	m_currToken = nullptr;
	m_nextToken = nullptr;
}

/****************************************************************************************************
* Author: Zak Rowland
* Filename: OitString.cpp
* Date Created: 4/4/2018
* Modifications:
*****************************************************************************************************
* Assignment: Linked List Lab 1
*
* Overview:  Develop your own string class, the OitString class. Using the attached files for the 
*			 OitString class, implement the methods from OitString.h in your own OitString.cpp file. 
*
* Input: From main.cpp
*
* Output: Tests from main.cpp
*
*****************************************************************************************************/

#include "OitString.h"

/*****************************************************************************************************
* Function: OitString(void)
* Purpose: Default constructor
*****************************************************************************************************/
OitString::OitString(void): OitString("")
{
}

/*****************************************************************************************************
* Function: OitString(const char ch)
* Purpose: Overloaded constructor with char
*****************************************************************************************************/
OitString::OitString(const char ch)
{
	char c[] = { ch,'\0' };
	OitString("");
	set(c);
}

/*****************************************************************************************************
* Function: OitString(const char * str)
* Purpose: Overloaded constructor with a string
*****************************************************************************************************/
OitString::OitString(const char * str)
{
	m_length = strlen(str);
	m_str = new char[m_length + 1];
	strcpy(m_str, str);
}

/*****************************************************************************************************
* Function: OitString(const OitString & os)
* Purpose: Copy constructor
*****************************************************************************************************/
OitString::OitString(const OitString & os): OitString(os.m_str)
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
	m_length = 0;
}

/*****************************************************************************************************
* Function: set(const char * str)
* Purpose: Setter using a string
*****************************************************************************************************/
void OitString::set(const char * str)
{
	if (m_str == nullptr || strcmp(str, m_str) != 0)
	{
		m_length = strlen(str);
		delete[] m_str;
		m_str = new char[strlen(str) + 1];
		strcpy(m_str, str);
	}
}

/*****************************************************************************************************
* Function: set(const OitString & os)
* Purpose: Setter using a class object
*****************************************************************************************************/
void OitString::set(const OitString & os)
{
	set(os.m_str);
}

/*****************************************************************************************************
* Function: set(const char ch)
* Purpose: Setter using a char
*****************************************************************************************************/
void OitString::set(const char ch)
{
	char c[] = { ch, '\0' };
	set(c);
}

/*****************************************************************************************************
* Function: operator=(const OitString & os)
* Purpose: Assignment operator for a class object
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
* Function: operator=(const char ch)
* Purpose: Assignment operator for a char
*****************************************************************************************************/
OitString & OitString::operator=(const char ch)
{
	char c[] = { ch,'\0' };

	if (strcmp(m_str, c) != 0)
	{
		set(c);
	}
	return *this;
}

/*****************************************************************************************************
* Function: operator=(const char * str)
* Purpose: Assignment operator for a string
*****************************************************************************************************/
OitString & OitString::operator=(const char * str)
{
	if (strcmp(m_str, str) != 0)
	{
		set(str);
	}
	return *this;
}

/*****************************************************************************************************
* Function: length(void) const
* Purpose: Returns m_length
*****************************************************************************************************/
size_t OitString::length(void) const
{
	return m_length;
}

/*****************************************************************************************************
* Function: append(const char * str)
* Purpose: Appends a string
*****************************************************************************************************/
void OitString::append(const char * str)
{
	m_length = m_length + strlen(str);
	char * temp = new char[m_length + 1];
	strcpy(temp, m_str);
	strcat(temp, str);
	delete[] m_str;
	m_str = temp;
}

/*****************************************************************************************************
* Function: append(char ch)
* Purpose: Appends a char
*****************************************************************************************************/
void OitString::append(char ch)
{
	char c[] = { ch,'\0' };
	append(c);
}

/*****************************************************************************************************
* Function: append(const OitString & os)
* Purpose: Appends data from a class object
*****************************************************************************************************/
void OitString::append(const OitString & os)
{
	append(os.m_str);
}

/*****************************************************************************************************
* Function: prepend(const char * str)
* Purpose: Prepends a string
*****************************************************************************************************/
void OitString::prepend(const char * str)
{
	m_length = m_length + strlen(str);
	char * temp = new char[m_length + 1];
	strcpy(temp, str);
	strcat(temp, m_str);
	delete[] m_str;
	m_str = temp;
}

/*****************************************************************************************************
* Function: prepend(char ch)
* Purpose: Prepends a char
*****************************************************************************************************/
void OitString::prepend(char ch)
{
	char c[] = { ch,'\0' };
	prepend(c);
}

/*****************************************************************************************************
* Function: prepend(const OitString & os)
* Purpose: Prepends data from a class object
*****************************************************************************************************/
void OitString::prepend(const OitString & os)
{
	prepend(os.m_str);
}

/*****************************************************************************************************
* Function: c_str(void) const
* Purpose: Returns m_str
*****************************************************************************************************/
char * OitString::c_str(void) const
{
	return m_str;
}

/*****************************************************************************************************
* Function: at(size_t pos) const
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
* Function: at(size_t pos)
* Purpose: Return a reference to a character at a given position. This can be used as an l-value.
*****************************************************************************************************/
char & OitString::at(size_t pos)
{
	return m_str[pos];
}

/*****************************************************************************************************
* Function: upper(size_t pos)
* Purpose: Change the case of the given character to upper
*****************************************************************************************************/
void OitString::upper(size_t pos)
{
	m_str[pos] = toupper(at(pos));
}

/*****************************************************************************************************
* Function: lower(size_t pos)
* Purpose: Change the case of the given character to lower
*****************************************************************************************************/
void OitString::lower(size_t pos)
{
	m_str[pos] = tolower(at(pos));
}

/*****************************************************************************************************
* Function: upper(void)
* Purpose: Change the case of the entire internal cString to upper
*****************************************************************************************************/
void OitString::upper(void)
{
	for (unsigned int i = 0; i < m_length; i++)
	{
		upper(i);
	}
}

/*****************************************************************************************************
* Function: lower(void)
* Purpose: Change the case of the entire internal cString to lower
*****************************************************************************************************/
void OitString::lower(void)
{
	for (unsigned int i = 0; i < m_length; i++)
	{
		lower(i);
	}
}

/*****************************************************************************************************
* Function: reverse(void)
* Purpose: Reverse the internal cString
*****************************************************************************************************/
void OitString::reverse(void)
{
	_strrev(m_str);
}

/*****************************************************************************************************
* Function: compare(const char * str) const
* Purpose: Behave like the strcmp() function using a string
*****************************************************************************************************/
int OitString::compare(const char * str) const
{
	return strcmp(m_str, str);
}

/*****************************************************************************************************
* Function: compare(const OitString & os) const
* Purpose: Behave like the strcmp() fucntion using a class object
*****************************************************************************************************/
int OitString::compare(const OitString & os) const
{
	return compare(os.m_str);
}

/*****************************************************************************************************
* Function: isEmpty(void) const
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
* Function: find(const char ch) const
* Purpose: Locate a character within the internal cString
*****************************************************************************************************/
char * OitString::find(const char ch) const
{
	return strchr(m_str, ch);
}

/*****************************************************************************************************
* Function: find(const char * str) const
* Purpose: Locate a string within the internal cString
*****************************************************************************************************/
char * OitString::find(const char * str) const
{
	return strstr(m_str, str);
}

/*****************************************************************************************************
* Function: findR(const char ch) const
* Purpose: Find a character, from the end of the string
*****************************************************************************************************/
char * OitString::findR(const char ch) const
{
	return strchr(_strrev(m_str), ch);
}

/*****************************************************************************************************
* Function: swap(OitString & os)
* Purpose: Exchange the internal cStrings m_str's between the 2 objects
*****************************************************************************************************/
void OitString::swap(OitString & os)
{
	char *ptr;
	char *ptr2;
	int temp = os.m_length;

	ptr = m_str;
	ptr2 = os.m_str;

	m_str = ptr2;
	os.m_str = ptr;

	ptr = nullptr;
	ptr2 = nullptr;

	os.m_length = m_length;
	m_length = temp;
}

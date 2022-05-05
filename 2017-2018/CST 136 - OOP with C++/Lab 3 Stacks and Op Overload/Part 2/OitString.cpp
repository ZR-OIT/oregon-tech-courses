/****************************************************************************************************
* Author: Zak Rowland
* Filename: OitString.cpp
* Date Created: 4/17/2018
* Modifications:
*****************************************************************************************************
* Assignment: Stacks and Op Overload Lab 3 - Part 2
*
* Overview: OitString operator overload
*
* Input: Tests from OitString_main.cpp
*
* Output: Results of tests from OitString_main.cpp
*
*****************************************************************************************************/

#include "OitString.h"

/*****************************************************************************************************
* Function: OitString(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: An empty OitString object
*****************************************************************************************************/
OitString::OitString(void): OitString("")
{
}

/*****************************************************************************************************
* Function: OitString(const char ch)
* Purpose: Overloaded constructor with char
* Preconditon: No class object
* Postcondition: An OitString object made with a char
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
* Preconditon: No class object
* Postcondition: An OitString object made with a string
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
* Preconditon: No class object and an object to be copied
* Postcondition: An OitString object copied from an existing object
*****************************************************************************************************/
OitString::OitString(const OitString & os): OitString(os.m_str)
{
}

/*****************************************************************************************************
* Function: ~OitString(void)
* Purpose: Destructor
* Preconditon: A class object
* Postcondition: Memory freed and class object deleted
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
* Preconditon: A class object
* Postcondition: Current object set to passed string
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
* Preconditon: A class object
* Postcondition: Current object set to passed object's string
*****************************************************************************************************/
void OitString::set(const OitString & os)
{
	set(os.m_str);
}

/*****************************************************************************************************
* Function: set(const char ch)
* Purpose: Setter using a char
* Preconditon: A class object
* Postcondition: Current object set to passed char
*****************************************************************************************************/
void OitString::set(const char ch)
{
	char c[] = { ch, '\0' };
	set(c);
}

/*****************************************************************************************************
* Function: operator=(const OitString & os)
* Purpose: Assignment operator for a class object
* Preconditon: A class object
* Postcondition: Current object set equal to passed object
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
* Preconditon: A class object
* Postcondition: Current object set equal to passed char
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
* Preconditon: A class object
* Postcondition: Current object set equal to passed string
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
* Function: operator+=(const char * str)
* Purpose: Concatenation operator for a string
* Preconditon: A class object
* Postcondition: Current object concatenated with passed string
*****************************************************************************************************/
OitString & OitString::operator+=(const char * str)
{
	this->append(str);
	return *this;
}

/*****************************************************************************************************
* Function: operator+=(const char ch)
* Purpose: Concatenation operator for a char
* Preconditon: A class object
* Postcondition: Current object concatenated with passed char
*****************************************************************************************************/
OitString & OitString::operator+=(const char ch)
{
	char temp[2] = { ch, '\0' };
	this->append(temp);
	return *this;
}

/*****************************************************************************************************
* Function: operator+=(const OitString & ot)
* Purpose: Concatenation operator for an object
* Preconditon: A class object
* Postcondition: Current object concatenated with passed object's string
*****************************************************************************************************/
OitString & OitString::operator+=(const OitString & ot)
{
	this->append(ot.m_str);
	return *this;
}

/*****************************************************************************************************
* Function: operator[](const int pos) const
* Purpose: Subscript operator
* Preconditon: A class object
* Postcondition: A char at passed position in current object's string
*****************************************************************************************************/
char OitString::operator[](const int pos) const
{
	return this->m_str[pos];
}

/*****************************************************************************************************
* Function: operator[](const int pos)
* Purpose: Subscript operator
* Preconditon: A class object
* Postcondition: A char at passed position in current object's string
*****************************************************************************************************/
char & OitString::operator[](const int pos)
{
	return this->m_str[pos];
}

/*****************************************************************************************************
* Function: length(void) const
* Purpose: Returns m_length
* Preconditon: No access to private data members
* Postcondition: Length of current string
*****************************************************************************************************/
size_t OitString::length(void) const
{
	return m_length;
}

/*****************************************************************************************************
* Function: append(const char * str)
* Purpose: Appends a string
* Preconditon: A class object
* Postcondition: Passed string appended to current string
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
* Preconditon: A class object
* Postcondition: Passed char appended to current string
*****************************************************************************************************/
void OitString::append(char ch)
{
	char c[] = { ch,'\0' };
	append(c);
}

/*****************************************************************************************************
* Function: append(const OitString & os)
* Purpose: Appends data from a class object
* Preconditon: A class object
* Postcondition: Passed object's string appended to current string
*****************************************************************************************************/
void OitString::append(const OitString & os)
{
	append(os.m_str);
}

/*****************************************************************************************************
* Function: prepend(const char * str)
* Purpose: Prepends a string
* Preconditon: A class object
* Postcondition: Passed string prepended to current string
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
* Preconditon: A class object
* Postcondition: Passed char prepended to current string
*****************************************************************************************************/
void OitString::prepend(char ch)
{
	char c[] = { ch,'\0' };
	prepend(c);
}

/*****************************************************************************************************
* Function: prepend(const OitString & os)
* Purpose: Prepends data from a class object
* Preconditon: A class object
* Postcondition: Passed object's string prepended to current string
*****************************************************************************************************/
void OitString::prepend(const OitString & os)
{
	prepend(os.m_str);
}

/*****************************************************************************************************
* Function: c_str(void) const
* Purpose: Returns m_str
* Preconditon: No access to private data members
* Postcondition: Returns current string
*****************************************************************************************************/
char * OitString::c_str(void) const
{
	return m_str;
}

/*****************************************************************************************************
* Function: at(size_t pos) const
* Purpose: Return character at the given position. If position is outside length of m_str, return '\0'
* Preconditon: A class object
* Postcondition: A char at passed position in current object's string
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
* Preconditon: A class object
* Postcondition: A char at passed position in current object's string
*****************************************************************************************************/
char & OitString::at(size_t pos)
{
	return m_str[pos];
}

/*****************************************************************************************************
* Function: upper(size_t pos)
* Purpose: Change the case of the given character to upper
* Preconditon: A class object
* Postcondition: A char at passed position in current object's string is converted to uppercase
*****************************************************************************************************/
void OitString::upper(size_t pos)
{
	m_str[pos] = toupper(at(pos));
}

/*****************************************************************************************************
* Function: lower(size_t pos)
* Purpose: Change the case of the given character to lower
* Preconditon: A class object
* Postcondition: A char at passed position in current object's string is converted to lowercase
*****************************************************************************************************/
void OitString::lower(size_t pos)
{
	m_str[pos] = tolower(at(pos));
}

/*****************************************************************************************************
* Function: upper(void)
* Purpose: Change the case of the entire internal cString to upper
* Preconditon: A class object
* Postcondition: Entire current string converted to uppercase
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
* Preconditon: A class object
* Postcondition: Entire current string converted to lowercase
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
* Preconditon: A class object
* Postcondition: Entire current string reversed
*****************************************************************************************************/
void OitString::reverse(void)
{
	_strrev(m_str);
}

/*****************************************************************************************************
* Function: compare(const char * str) const
* Purpose: Behave like the strcmp() function using a string
* Preconditon: A class object
* Postcondition: A comparison between the current string and the passed string
*****************************************************************************************************/
int OitString::compare(const char * str) const
{
	return strcmp(m_str, str);
}

/*****************************************************************************************************
* Function: compare(const OitString & os) const
* Purpose: Behave like the strcmp() fucntion using a class object
* Preconditon: A class object
* Postcondition: A comparison between the current string and the passed object's string
*****************************************************************************************************/
int OitString::compare(const OitString & os) const
{
	return compare(os.m_str);
}

/*****************************************************************************************************
* Function: isEmpty(void) const
* Purpose: Return true if the length of the internal cString == 0
* Preconditon: A class object
* Postcondition: 
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
* Preconditon: A class object
* Postcondition: A pointer to a char in the current string searched for with passed char
*****************************************************************************************************/
char * OitString::find(const char ch) const
{
	return strchr(m_str, ch);
}

/*****************************************************************************************************
* Function: find(const char * str) const
* Purpose: Locate a string within the internal cString
* Preconditon: A class object
* Postcondition: A pointer to a string in the current string searched for with passed string
*****************************************************************************************************/
char * OitString::find(const char * str) const
{
	return strstr(m_str, str);
}

/*****************************************************************************************************
* Function: findR(const char ch) const
* Purpose: Find a character, from the end of the string
* Preconditon: A class object
* Postcondition: A pointer to a char in the current string searched for with passed char in reverse
*****************************************************************************************************/
char * OitString::findR(const char ch) const
{
	return strchr(_strrev(m_str), ch);
}

/*****************************************************************************************************
* Function: swap(OitString & os)
* Purpose: Exchange the internal cStrings m_str's between the 2 objects
* Preconditon: A class object
* Postcondition: Current string and passed object's string are swapped
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

/*****************************************************************************************************
* Function: operator+(const OitString & lot, const OitString & rot)
* Purpose: Concatenation operator
* Preconditon: Two class objects
* Postcondition: Second passed object's string appended to first passed object's string
*****************************************************************************************************/
OitString operator+(const OitString & lot, const OitString & rot)
{
	OitString string = OitString(lot.m_str);
	string.append(rot.m_str);
	return string;
}

/*****************************************************************************************************
* Function: operator+(const char * str, const OitString & rot)
* Purpose: Concatenation operator
* Preconditon: A class object
* Postcondition: Passed object's string appended to passed string
*****************************************************************************************************/
OitString operator+(const char * str, const OitString & rot)
{
	OitString string = OitString(str);
	string.append(rot.m_str);
	return string;
}

/*****************************************************************************************************
* Function: operator+(const OitString & lot, const char * str)
* Purpose: Concatenation operator
* Preconditon: A class object
* Postcondition: Passed string appended to passed object's string
*****************************************************************************************************/
OitString operator+(const OitString & lot, const char * str)
{
	OitString string = OitString(lot.m_str);
	string.append(str);
	return string;
}

/*****************************************************************************************************
* Function: operator+(const char ch, const OitString & rot)
* Purpose: Concatenation operator
* Preconditon: A class object
* Postcondition: Passed object's string appended to passed char
*****************************************************************************************************/
OitString operator+(const char ch, const OitString & rot)
{
	char temp[2] = { ch, '\0' };
	OitString string = OitString(temp);
	string.append(rot.m_str);
	return string;
}

/*****************************************************************************************************
* Function: operator+(const OitString & lot, const char ch)
* Purpose: Concatenation operator
* Preconditon: A class object
* Postcondition: Passed char appended to passed object's string
*****************************************************************************************************/
OitString operator+(const OitString & lot, const char ch)
{
	char temp[2] = { ch, '\0' };
	OitString string = OitString(lot.m_str);
	string.append(temp);
	return string;
}

/*****************************************************************************************************
* Function: operator==(const OitString & lot, const OitString & rot)
* Purpose: Relational operator
* Preconditon: Two class objects
* Postcondition: Checks if the two passed object's strings are equal
*****************************************************************************************************/
bool operator==(const OitString & lot, const OitString & rot)
{
	bool equal = false;
	if (lot.compare(rot) == 0)
		equal = true;
	return equal;
}

/*****************************************************************************************************
* Function: operator==(const OitString & lot, const char * str)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is equal to the passed string
*****************************************************************************************************/
bool operator==(const OitString & lot, const char * str)
{
	bool equal = false;
	if (lot.compare(str) == 0)
		equal = true;
	return equal;
}

/*****************************************************************************************************
* Function: operator==(const char * str, const OitString & rot)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is equal to the passed string
*****************************************************************************************************/
bool operator==(const char * str, const OitString & rot)
{
	bool equal = false;
	if (rot.compare(str) == 0)
		equal = true;
	return equal;
}

/*****************************************************************************************************
* Function: operator!=(const OitString & lot, const OitString & rot)
* Purpose: Relational operator
* Preconditon: Two class objects
* Postcondition: Checks if the two passed object's strings are not equal
*****************************************************************************************************/
bool operator!=(const OitString & lot, const OitString & rot)
{
	bool notEqual = false;

	if (strcmp(lot.m_str, rot.m_str) != 0)
		notEqual = true;

	return notEqual;
}

/*****************************************************************************************************
* Function: operator!=(const OitString & lot, const char * str)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is not equal to the passed string
*****************************************************************************************************/
bool operator!=(const OitString & lot, const char * str)
{
	bool notEqual = false;

	if (strcmp(lot.m_str, str) != 0)
		notEqual = true;

	return notEqual;
}

/*****************************************************************************************************
* Function: operator!=(const char * str, const OitString & rot)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is not equal to the passed string
*****************************************************************************************************/
bool operator!=(const char * str, const OitString & rot)
{
	bool notEqual = false;

	if (strcmp(str, rot.m_str) != 0)
		notEqual = true;

	return notEqual;
}

/*****************************************************************************************************
* Function: operator<(const OitString & lot, const OitString & rot)
* Purpose: Relational operator
* Preconditon: Two class objects
* Postcondition: Checks if the first passed object's string is less than the second passed object's string
*****************************************************************************************************/
bool operator<(const OitString & lot, const OitString & rot)
{
	bool less = false;

	if (strcmp(lot.m_str, rot.m_str) < 0)
		less = true;

	return less;
}

/*****************************************************************************************************
* Function: operator<(const OitString & lot, const char * str)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is less than the passed string
*****************************************************************************************************/
bool operator<(const OitString & lot, const char * str)
{
	bool less = false;

	if (strcmp(lot.m_str, str) < 0)
		less = true;

	return less;
}

/*****************************************************************************************************
* Function: operator<(const char * str, const OitString & rot)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed string is less than the passed object's string
*****************************************************************************************************/
bool operator<(const char * str, const OitString & rot)
{
	bool less = false;

	if (strcmp(str, rot.m_str) < 0)
		less = true;

	return less;
}

/*****************************************************************************************************
* Function: operator>(const OitString & lot, const OitString & rot)
* Purpose: Relational operator
* Preconditon: Two class objects
* Postcondition: Checks if the first passed object's string is greater than the second passed object's string
*****************************************************************************************************/
bool operator>(const OitString & lot, const OitString & rot)
{
	bool greater = false;

	if (strcmp(lot.m_str, rot.m_str) > 0)
		greater = true;

	return greater;
}

/*****************************************************************************************************
* Function: operator>(const OitString & lot, const char * str)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is greater than the passed string
*****************************************************************************************************/
bool operator>(const OitString & lot, const char * str)
{
	bool greater = false;

	if (strcmp(lot.m_str, str) > 0)
		greater = true;

	return greater;
}

/*****************************************************************************************************
* Function: operator>(const char * str, const OitString & rot)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed string is greater than the passed object's string
*****************************************************************************************************/
bool operator>(const char * str, const OitString & rot)
{
	bool greater = false;

	if (strcmp(str, rot.m_str) > 0)
		greater = true;

	return greater;
}

/*****************************************************************************************************
* Function: operator<=(const OitString & lot, const OitString & rot)
* Purpose: Relational operator
* Preconditon: Two class objects
* Postcondition: Checks if the first passed object's string is less or equal to than the second passed object's string
*****************************************************************************************************/
bool operator<=(const OitString & lot, const OitString & rot)
{
	bool lessEqual = false;

	if (strcmp(lot.m_str, rot.m_str) < 0 || strcmp(lot.m_str, rot.m_str) == 0)
		lessEqual = true;

	return lessEqual;
}

/*****************************************************************************************************
* Function: operator<=(const OitString & lot, const char * str)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is less than or equal to the passed string
*****************************************************************************************************/
bool operator<=(const OitString & lot, const char * str)
{
	bool lessEqual = false;

	if (strcmp(lot.m_str, str) < 0 || strcmp(lot.m_str, str) == 0)
		lessEqual = true;

	return lessEqual;
}

/*****************************************************************************************************
* Function: operator<=(const char * str, const OitString & rot)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed string is less than or equal to the passed object's string
*****************************************************************************************************/
bool operator<=(const char * str, const OitString & rot)
{
	bool lessEqual = false;

	if (strcmp(str, rot.m_str) < 0 || strcmp(str, rot.m_str) == 0)
		lessEqual = true;

	return lessEqual;
}

/*****************************************************************************************************
* Function: operator>=(const OitString & lot, const OitString & rot)
* Purpose: Relational operator
* Preconditon: Two class objects
* Postcondition: Checks if the first passed object's string is greater than or equal to the second passed object's string
*****************************************************************************************************/
bool operator>=(const OitString & lot, const OitString & rot)
{
	bool greaterEqual = false;

	if (strcmp(lot.m_str, rot.m_str) > 0 || strcmp(lot.m_str, rot.m_str) == 0)
		greaterEqual = true;

	return greaterEqual;
}

/*****************************************************************************************************
* Function: operator>=(const OitString & lot, const char * str)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed object's string is greater than or equal to the passed string
*****************************************************************************************************/
bool operator>=(const OitString & lot, const char * str)
{
	bool greaterEqual = false;

	if (strcmp(lot.m_str, str) > 0 || strcmp(lot.m_str, str) == 0)
		greaterEqual = true;

	return greaterEqual;
}

/*****************************************************************************************************
* Function: operator>=(const char * str, const OitString & rot)
* Purpose: Relational operator
* Preconditon: A class object
* Postcondition: Checks if the passed string is greater than or equal to the passed object's string
*****************************************************************************************************/
bool operator>=(const char * str, const OitString & rot)
{
	bool greaterEqual = false;

	if (strcmp(str, rot.m_str) > 0 || strcmp(str, rot.m_str) == 0)
		greaterEqual = true;

	return greaterEqual;
}

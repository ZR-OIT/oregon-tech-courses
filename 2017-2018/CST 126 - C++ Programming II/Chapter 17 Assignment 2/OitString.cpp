/****************************************************************************************************
* Author: Zak Rowland
* Filename: OitString.cpp
* Date Created: 2/21/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 17 Assignment 2 - Part 2
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

#include <crtdbg.h>
#include "OitString.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/

OitString::OitString(void): OitString("")
{
}

OitString::OitString(const char * str)
{
	m_length = strlen(str);
	m_str = new char[strlen(str) + 1];
	strcpy(m_str, str);
}

OitString::OitString(const OitString & os): OitString(os.m_str)
{
}

OitString::~OitString(void)
{
	delete[] m_str;
	m_str = nullptr;
}

void OitString::set(const char * str)
{
	m_length = strlen(str);
	delete[] m_str;
	m_str = new char[strlen(str) + 1];
	strcpy(m_str, str);
}

void OitString::set(const OitString & os)
{
	set(os.m_str);
}

OitString & OitString::operator=(const char * str)
{
	if (str != this->m_str)
	{
		set(str);
	}
	return *this;
}

OitString & OitString::operator=(const OitString & os)
{
	if (this != &os)
	{
		set(os.m_str);
	}
	return *this;
}

size_t OitString::length(void) const
{
	return m_length;
}

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

void OitString::append(char ch)
{
	char c[] = { ch,'\0' };
	append(c);
}

void OitString::append(const OitString & os)
{
	append(os.m_str);
}

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

void OitString::prepend(char ch)
{
	char c[] = { ch,'\0' };
	prepend(c);
}

void OitString::prepend(const OitString & os)
{
	prepend(os.m_str);
}

char * OitString::c_str(void) const
{
	return this->m_str;
}

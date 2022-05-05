/****************************************************************************************************
* Author: Zak Rowland
* Filename: TLListException.h
* Date Created: 5/31/2018
* Modifications:
*****************************************************************************************************
* Assignment: In Lab Quiz
*
* Overview: Implement a bounded linked list template class.
*
* Input: Tests from main.cpp
*
* Output: Test results
*
*****************************************************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>

using std::exception;
using std::cout;
using std::ostream;
using std::endl;

# ifndef TLLISTEXCEPTION_H
# define TLLISTEXCEPTION_H

class TLListException : public exception
{
public:
	TLListException(const char * message);

	friend ostream& operator << (ostream& os, const TLListException &e);
};

#endif //TLLISTEXCEPTION_H
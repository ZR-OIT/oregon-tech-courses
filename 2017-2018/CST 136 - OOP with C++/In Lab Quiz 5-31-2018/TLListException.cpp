/****************************************************************************************************
* Author: Zak Rowland
* Filename: TLListException.cpp
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
#include "TLListException.h"

TLListException::TLListException(const char * message) : exception(message)
{
	//empty
}

ostream & operator<<(ostream & os, const TLListException & e)
{
	os << e.what();
	return os;
}

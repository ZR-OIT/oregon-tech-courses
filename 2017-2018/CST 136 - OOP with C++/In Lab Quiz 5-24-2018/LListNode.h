/****************************************************************************************************
* Author: Zak Rowland
* Filename: LListNode.h
* Date Created: 5/24/2018
* Modifications:
*****************************************************************************************************
* Assignment: In Lab Quiz
*
* Overview: Implement classes and methods from class diagram
*
* Input: Tests from dbl_list_main.cpp
*
* Output: Test results
*
*****************************************************************************************************/
#pragma once

#ifndef LLISTNODE_H
# define LLISTNODE_H
# include "Book.h"

namespace LinkList
{
	class LListNode
	{
	public:
		friend class DblLList;
		LListNode(const char * title, const char * author, const char * isbn);
		~LListNode(void);
		void Display(ostream &os = cout) const;
		friend ostream & operator << (ostream & os, const LListNode& node);
		Book * GetBook(void) const;
		LListNode * GetNext(void) const;
		LListNode * GetPrev(void) const;
		void SetNext(LListNode *node);
		void SetPrev(LListNode *node);
	private:
		Book * m_book;
		LListNode * m_next;
		LListNode * m_prev;
	};
}

#endif //LLISTNODE_H
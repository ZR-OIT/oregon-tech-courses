/****************************************************************************************************
* Author: Zak Rowland
* Filename: DblLList.h
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

#ifndef DBLLLIST_H
# define DBLLLIST_H
# include "LListNode.h"
namespace LinkList
{
	class DblLList
	{
	public:
		DblLList(size_t size = DEFAULT_LINKED_LIST_MAX);
		DblLList(DblLList &list);
		~DblLList(void);
		void Append(const char * title, const char * author, const char * isbn);
		void Prepend(const char * title, const char * author, const char * isbn);
		void Display(ostream &os = cout) const;
		void Clear(void);
		bool IsFull(void) const;
		size_t Length(void) const;
		size_t MaxLength(void) const;
		friend ostream & operator << (ostream & os, const DblLList& list);
	protected:
		static const int DEFAULT_LINKED_LIST_MAX = 0;
		LListNode * m_head;
		LListNode * m_tail;
		size_t m_length;
		size_t m_maxLength;
	};
}

#endif //DBLLLIST_H
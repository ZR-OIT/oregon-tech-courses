/****************************************************************************************************
* Author: Zak Rowland
* Filename: LListNode.cpp
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
#include "LListNode.h"

/*****************************************************************************************************
* Function: LListNode(const char * title, const char * author, const char * isbn)
* Purpose: Constructor
* Preconditon: No class object
* Postcondition: A new LListNode object
*****************************************************************************************************/
LinkList::LListNode::LListNode(const char * title, const char * author, const char * isbn) : m_book(new Book(title, author, isbn)), m_next(nullptr), m_prev(nullptr)
{
}

/*****************************************************************************************************
* Function: ~LListNode(void)
* Purpose: Destructor
* Preconditon: A LListNode object
* Postcondition: Class object deleted and memory freed
*****************************************************************************************************/
LinkList::LListNode::~LListNode(void)
{
	delete m_book;
	m_next = nullptr;
	m_prev = nullptr;
}

/*****************************************************************************************************
* Function: Display(ostream & os) const
* Purpose: Prints information from the LListNode object
* Preconditon: A LListNode object
* Postcondition: Data output
*****************************************************************************************************/
void LinkList::LListNode::Display(ostream & os) const
{
	os << *m_book;
}

/*****************************************************************************************************
* Function: operator<<(ostream & os, const LListNode & node)
* Purpose: Prints information from the LListNode object
* Preconditon: A LListNode object
* Postcondition: Data output
*****************************************************************************************************/
ostream & LinkList::operator<<(ostream & os, const LListNode & node)
{
	os << *node.m_book;
	return os;
}

/*****************************************************************************************************
* Function: GetBook(void) const
* Purpose: Returns the LListNode object's book
* Preconditon: No access to private data members
* Postcondition: Access to private data member
*****************************************************************************************************/
LinkList::Book * LinkList::LListNode::GetBook(void) const
{
	return m_book;
}

/*****************************************************************************************************
* Function: GetNext(void) const
* Purpose: Returns the LListNode object's next node
* Preconditon: No access to private data members
* Postcondition: Access to private data member
*****************************************************************************************************/
LinkList::LListNode * LinkList::LListNode::GetNext(void) const
{
	return m_next;
}

/*****************************************************************************************************
* Function: GetPrev(void) const
* Purpose: Returns the LListNode object's previous node
* Preconditon: No access to private data members
* Postcondition: Access to private data member
*****************************************************************************************************/
LinkList::LListNode * LinkList::LListNode::GetPrev(void) const
{
	return m_prev;
}

/*****************************************************************************************************
* Function: SetNext(LListNode * node)
* Purpose: Sets the LListNode object's next node
* Preconditon: No access to private data members
* Postcondition: Access to private data member
*****************************************************************************************************/
void LinkList::LListNode::SetNext(LListNode * node)
{
	m_next = node;
}

/*****************************************************************************************************
* Function: SetPrev(LListNode * node)
* Purpose: Sets the LListNode object's previous node
* Preconditon: No access to private data members
* Postcondition: Access to private data member
*****************************************************************************************************/
void LinkList::LListNode::SetPrev(LListNode * node)
{
	m_prev = node;
}

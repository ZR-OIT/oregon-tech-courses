/****************************************************************************************************
* Author: Zak Rowland
* Filename: Node.cpp
* Date Created: 3/8/2018
* Modifications:
*****************************************************************************************************
* Assignment: Doubly Linked List
*
* Overview: Read file containing names and addresses. Create a linked list of the names and addresses.
*			The linked list must be a doubly linked list, there must be m_next and m_prev pointers.
*			The linked list must be stored ordered by last name and first name.
*			Be able to display the list in both forward and reverse directions.
*
* Input: "AddressBook.csv"
*
* Output: Address list
*
*****************************************************************************************************/

#include "Node.h"

/*****************************************************************************************************
* Function: Node(const char * fname, const char * lname, const char * email, const char * street, 
*					const char * city, const char * state, const char * zip)
* Purpose: Constructor
*****************************************************************************************************/
Node::Node(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip) 
	: m_next(nullptr), m_prev(nullptr), m_person(new Person(fname, lname, email, street, city, state, zip))
{
}

/*****************************************************************************************************
* Function: Node(void)
* Purpose: Destructor
*****************************************************************************************************/
Node::~Node(void)
{
	clear();
}

/*****************************************************************************************************
* Function: Node(const Node & node)
* Purpose: Copy constructor 
*****************************************************************************************************/
Node::Node(const Node & node)
{
	*this = node;
}

/*****************************************************************************************************
* Function: operator=(const Node & node)
* Purpose: Assignment operator
*****************************************************************************************************/
Node & Node::operator=(const Node & node)
{
	if (this != &node)
	{
		m_person = node.m_person;
		m_next = node.m_next;
		m_prev = node.m_prev;
	}
	return *this;
}

/*****************************************************************************************************
* Function: Display(void) const
* Purpose: Displays nodes
*****************************************************************************************************/
void Node::Display(void) const
{
	m_person->Display();
}

/*****************************************************************************************************
* Function: SetNext(Node * next)
* Purpose: Sets next pointer
*****************************************************************************************************/
void Node::SetNext(Node * next)
{
	this->m_next = next;
}

/*****************************************************************************************************
* Function: SetPrev(Node * prev)
* Purpose: Sets previous pointer
*****************************************************************************************************/
void Node::SetPrev(Node * prev)
{
	this->m_prev = prev;
}

/*****************************************************************************************************
* Function: GetNext(void) const
* Purpose: Gets next pointer
*****************************************************************************************************/
Node * Node::GetNext(void) const
{
	return this->m_next;
}

/*****************************************************************************************************
* Function: GetPrev(void) const
* Purpose: Gets previous pointer
*****************************************************************************************************/
Node * Node::GetPrev(void) const
{
	return this->m_prev;
}

/*****************************************************************************************************
* Function: GetPerson(void)
* Purpose: Gets a person
*****************************************************************************************************/
Person * Node::GetPerson(void)
{
	return this->m_person;
}

/*****************************************************************************************************
* Function: Compare(const char * fname, const char * lname) const
* Purpose: Compares names
*****************************************************************************************************/
int Node::Compare(const char * fname, const char * lname) const
{
	return m_person->Compare(fname, lname);
}

/*****************************************************************************************************
* Function: clear(void)
* Purpose: Deallocates used memory
*****************************************************************************************************/
void Node::clear(void)
{
	delete m_person;
	m_person = nullptr;
	m_next = nullptr;
	m_prev = nullptr;
}

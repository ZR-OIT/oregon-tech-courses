/****************************************************************************************************
* Author: Zak Rowland
* Filename: Node.cpp
* Date Created: 4/7/2018
* Modifications: 
*****************************************************************************************************
* Assignment: Lab 2 - Address List
*
* Overview: Create a doubly linked list of the names and addresses, based on the provided files
*			and sample data.
*
* Input:	Tests from main.cpp and data from CSV files.
*
* Output:	Results of tests from main.cpp.
*
*****************************************************************************************************/

#include <iostream>
#include "Node.h"

using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: Node(const char * fname, const char * lname, const char * email, const ...)
* Purpose: Overloaded constructor
* Preconditon: Data for a Person without a node.
* Postcondition: A new node allocated with data from Person. 
*****************************************************************************************************/
Node::Node(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
	: m_next(nullptr), m_prev(nullptr), m_person(new Person(fname, lname, email, street, city, state, zip))
{
	//empty
}

/*****************************************************************************************************
* Function: ~Node(void)
* Purpose: Destructor
* Preconditon: Class object with properly allocated memory.
* Postcondition: Class object memory returned to heap and pointers set to null.
*****************************************************************************************************/
Node::~Node(void)
{
	clear();
}

/*****************************************************************************************************
* Function: Node(const Node & node)
* Purpose: Copy consructor
* Preconditon: A Node class object to be copied.
* Postcondition: A copy of the passed class object.
*****************************************************************************************************/
Node::Node(const Node & node)
{
	*this = node;
}

/*****************************************************************************************************
* Function: operator=(const Node & node)
* Purpose: Assignment operator
* Preconditon: A Node class object to be assigned to the current class object.
* Postcondition: If the current object is equal to the passed object, make no change.
*				 Otherwise, allocate and copy the passed object into the current object.
*****************************************************************************************************/
Node & Node::operator=(const Node & node)
{
	if (this != &node)
	{
		Person *data = node.m_person;

		this->clear();

		m_person = new Person(data->GetFName(), data->GetLName(), data->GetEMail(), data->GetStreet(),
			data->GetCity(), data->GetState(), data->GetZip());
	}
	return *this;
}

/*****************************************************************************************************
* Function: Display(void) const
* Purpose: Display the information in the current node.
* Preconditon: 
* Postcondition:
*****************************************************************************************************/
void Node::Display(void) const
{
	m_person->Display();
}

/*****************************************************************************************************
* Function: SetNext(Node * next)
* Purpose: Change the m_next node pointer.
* Preconditon: A pointer to null or another node.
* Postcondition: An updated pointer to either another node or null.
*****************************************************************************************************/
void Node::SetNext(Node * next)
{
	this->m_next = next;
}

/*****************************************************************************************************
* Function: SetPrev(Node * prev)
* Purpose: Change the m_prev node pointer.
* Preconditon: A pointer to null or another node.
* Postcondition: An updated pointer to either another node or null.
*****************************************************************************************************/
void Node::SetPrev(Node * prev)
{
	this->m_prev = prev;
}

/*****************************************************************************************************
* Function: GetNext(void) const
* Purpose: Returns a pointer to the m_next data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
Node * Node::GetNext(void) const
{
	return this->m_next;
}

/*****************************************************************************************************
* Function: GetPrev(void) const
* Purpose: Returns a pointer to the m_prev data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
Node * Node::GetPrev(void) const
{
	return this->m_prev;
}

/*****************************************************************************************************
* Function: GetPerson(void)
* Purpose: Returns a pointer to the m_person data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
Person * Node::GetPerson(void)
{
	return this->m_person;
}

/*****************************************************************************************************
* Function: Compare(const char * fname, const char * lname) const
* Purpose: Compares last and first names.
* Preconditon:
* Postcondition: If the current last name equals the passed last name, compare first names and return value.
*				 Otherwise, return the value obtained by comparing last names.
*****************************************************************************************************/
int Node::Compare(const char * fname, const char * lname) const
{
	return m_person->Compare(fname, lname);
}

/*****************************************************************************************************
* Function: clear(void)
* Purpose: Frees all memory for the instance.
* Preconditon: A class object that has allocated memory.
* Postcondition: All memory returned to heap and pointers assigned to null.
*****************************************************************************************************/
void Node::clear(void)
{
	delete m_person;
	m_person = nullptr;
	m_prev = nullptr;
	m_next = nullptr;
}

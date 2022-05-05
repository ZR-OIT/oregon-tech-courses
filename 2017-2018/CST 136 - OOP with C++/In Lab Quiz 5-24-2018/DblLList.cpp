/****************************************************************************************************
* Author: Zak Rowland
* Filename: DblLList.cpp
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
#include "DblLList.h"
#include "LinkListException.h"

namespace LinkList {
	/*****************************************************************************************************
	* Function: DblLList(size_t size)
	* Purpose: Constructor
	* Preconditon: No class object
	* Postcondition: A new DblLList object
	*****************************************************************************************************/
	DblLList::DblLList(size_t size) : m_head(nullptr), m_tail(nullptr), m_length(0), m_maxLength(size)
	{
		//empty
	}

	/*****************************************************************************************************
	* Function: DblLList(DblLList & list)
	* Purpose: Copy constructor
	* Preconditon: No class object
	* Postcondition: A new DblLList object copied from the passed object
	*****************************************************************************************************/
	DblLList::DblLList(DblLList & list) : m_head(nullptr), m_tail(nullptr), m_length(0), m_maxLength(list.m_maxLength)
	{
		LListNode *travel = list.m_head;
		Book * temp = nullptr;
		while (travel != nullptr)
		{
			temp = travel->m_book;
			Append(temp->GetTitle(), temp->GetAuthor(), temp->GetIsbn());
			travel = travel->m_next;
		}
	}

	/*****************************************************************************************************
	* Function: ~DblLList(void)
	* Purpose: Destructor
	* Preconditon: A DblLList object
	* Postcondition: Class object deleted and memory freed
	*****************************************************************************************************/
	DblLList::~DblLList(void)
	{
		Clear();
	}

	/*****************************************************************************************************
	* Function: Append(const char * title, const char * author, const char * isbn)
	* Purpose: Inserts a new node at the end of the list
	* Preconditon: A DblLList object
	* Postcondition: The object with another node added on
	*****************************************************************************************************/
	void DblLList::Append(const char * title, const char * author, const char * isbn)
	{
		if (IsFull())
		{
			throw LinkListException();
		}
		else
		{
			if (m_length == 0)
			{
				LListNode * temp = new LListNode(title, author, isbn);
				m_head = temp;
			}
			else if (m_length == 1)
			{
				LListNode * temp = new LListNode(title, author, isbn);
				m_tail = temp;
				m_head->m_next = m_tail;
				m_tail->m_prev = m_head;
			}
			else
			{
				LListNode * temp = new LListNode(title, author, isbn);
				if (m_tail != nullptr)
				{
					m_tail->m_next = temp;
					temp->m_prev = m_tail;
				}
				m_tail = temp;
			}
			m_length++;
		}
	}

	/*****************************************************************************************************
	* Function: Prepend(const char * title, const char * author, const char * isbn)
	* Purpose: Inserts a new node at the beginning of the list
	* Preconditon: A DblLList object
	* Postcondition: The object with another node added on
	*****************************************************************************************************/
	void DblLList::Prepend(const char * title, const char * author, const char * isbn)
	{
		if (IsFull())
		{
			throw LinkListException();
		}
		else
		{
			if (m_length == 0)
			{
				LListNode *newNode = new LListNode(title, author, isbn);
				m_head = newNode;
			}
			else if (m_length == 1)
			{
				LListNode *newNode = new LListNode(title, author, isbn);
				m_head->m_prev = newNode;
				newNode->m_next = m_head;
				m_head = newNode;
			}
			else
			{
				LListNode *newNode = new LListNode(title, author, isbn);
				m_head->m_prev = newNode;
				newNode->m_next = m_head;
				m_head = newNode;
			}
			m_length++;
		}
	}

	/*****************************************************************************************************
	* Function: Display(ostream & os) const
	* Purpose: Prints information from the DblLList object
	* Preconditon: A DblLList object
	* Postcondition: Data output
	*****************************************************************************************************/
	void DblLList::Display(ostream & os) const
	{
		LListNode * travel = m_head;
		while (travel != nullptr)
		{
			travel->Display();
			travel = travel->m_next;
			cout << std::endl;
		}
	}

	/*****************************************************************************************************
	* Function: Clear(void)
	* Purpose: Deletes all nodes in the DblLList object
	* Preconditon: A DblLList object
	* Postcondition: Memory freed and object deleted
	*****************************************************************************************************/
	void DblLList::Clear(void)
	{
		LListNode *travel = m_head;

		while (travel != nullptr)
		{
			LListNode *next = travel->m_next;
			delete travel;
			travel = next;
		}

		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}

	/*****************************************************************************************************
	* Function: IsFull(void) const
	* Purpose: Determines if the DblLList object is full
	* Preconditon: A DblLList object
	* Postcondition: A comparison between the current length and max length
	*****************************************************************************************************/
	bool DblLList::IsFull(void) const
	{
		//bool full = false;
		//
		//if (m_maxLength == 0)
		//{
		//	full = false;
		//}
		//else if (m_length >= m_maxLength)
		//{
		//	full = true;
		//}
		//
		//return full;

		return (m_maxLength == 0 || m_length < m_maxLength ? false : true);
	}

	/*****************************************************************************************************
	* Function: Length(void) const
	* Purpose: Returns the DblLList object's length
	* Preconditon: No access to private data members
	* Postcondition: Access to private data member
	*****************************************************************************************************/
	size_t DblLList::Length(void) const
	{
		return m_length;
	}

	/*****************************************************************************************************
	* Function: MaxLength(void) const
	* Purpose: Returns the DblLList object's max length
	* Preconditon: No access to private data members
	* Postcondition: Access to private data member
	*****************************************************************************************************/
	size_t DblLList::MaxLength(void) const
	{
		return m_maxLength;
	}

	/*****************************************************************************************************
	* Function: operator<<(ostream & os, const DblLList & list)
	* Purpose: Prints information from the DblLList object
	* Preconditon: A DblLList object
	* Postcondition: Data output
	*****************************************************************************************************/
	ostream & operator<<(ostream & os, const DblLList & list)
	{
		list.Display(os);
		return os;
	}
}

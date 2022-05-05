/****************************************************************************************************
* Author: Zak Rowland
* Filename: TLList.h
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
#include "TLListException.h"
#include "LListNode.h"

using std::cout;
using std::ostream;
using std::endl;

namespace TLinkedList
{

	template <class T>
	class TLList
	{
	public:
		TLList(int size = DEFAULT_LINKED_LIST_MAX);
		TLList(const TLList<T> &list);
		TLList<T> & operator=(const TLList &list);
		~TLList(void);

		void Append(const T & item);
		void Prepend(const T & item);

		bool IsFull(void) const;
		size_t Length(void) const;
		size_t MaxLength(void) const;

		void Clear(void);

		friend ostream & operator << (ostream & os, const TLList<T> &list)
		{
			list.Display(os);
			return os;
		}
	private:
		static const int DEFAULT_LINKED_LIST_MAX = 0;
		
		LListNode<T> * m_head;
		LListNode<T> * m_tail;

		size_t m_length;
		size_t m_maxLength;

		void Display(ostream &os) const;
	};
}

namespace TLinkedList
{
	// Constructor
	template<typename T>
	inline TLList<T>::TLList(int size) : m_length(0), m_maxLength(size), m_head(nullptr), m_tail(nullptr)
	{
		if (size < 0)
		{
			throw TLListException("List length must be a positive number.");
		}
	}
	// Copy constructor
	template<class T>
	inline TLList<T>::TLList(const TLList<T>& list) : m_length(0), m_maxLength(list.m_maxLength), m_head(nullptr), m_tail(nullptr)
	{
		if (list.m_maxLength < 0)
		{
			throw TLListException("List length must be a positive number.");
		}
		else
		{
			LListNode<T> * travel = list.m_head;
			while (travel != nullptr)
			{
				Append(travel->m_data);
				travel = travel->m_next;
			}
		}
	}
	// Assignment operator
	template<class T>
	inline TLList<T> & TLList<T>::operator=(const TLList<T> &list)
	{
		if (this != &list)
		{
			if (list.m_maxLength < 0)
			{
				throw TLListException("List length must be a positive number.");
			}

			this->Clear();

			/*TLList * temp(&list);
			this = temp;*/

			LListNode<T> * travel = list.m_head;
			while (travel != nullptr)
			{
				this->Append(travel->m_data);
				travel = travel->m_next;
			}
		}
		return *this;
	}
	// Destructor
	template<typename T>
	inline TLList<T>::~TLList(void)
	{
		Clear();
	}
	// Append
	template<typename T>
	inline void TLList<T>::Append(const T & item)
	{
		if (IsFull())
		{
			throw TLListException("List is full.");
		}
		else
		{
			if (m_length == 0)
			{
				LListNode<T> * temp = new LListNode<T>(item);
				m_head = m_tail = temp;
			}
			else
			{
				LListNode<T> * temp = new LListNode<T>(item);
				m_tail->m_next = temp;
				temp->m_prev = m_tail;
				m_tail = temp;
			}
			m_length++;
		}
	}
	// Prepend
	template<typename T>
	inline void TLList<T>::Prepend(const T & item)
	{
		if (IsFull())
		{
			throw TLListException("List is full.");
		}
		else
		{
			if (m_length == 0)
			{
				LListNode<T> *newNode = new LListNode<T>(item);
				m_head = m_tail = newNode;
			}
			else
			{
				LListNode<T> *newNode = new LListNode<T>(item);
				m_head->m_prev = newNode;
				newNode->m_next = m_head;
				m_head = newNode;
			}
			m_length++;
		}
	}
	// Full
	template<typename T>
	inline bool TLList<T>::IsFull(void) const
	{
		bool full = false;

		if (m_maxLength == 0)
		{
			full = false;
		}
		else if (m_length >= m_maxLength)
		{
			full = true;
		}

		return full;
	}
	// Length
	template<typename T>
	inline size_t TLList<T>::Length(void) const
	{
		return m_length;
	}
	// Max length
	template<typename T>
	inline size_t TLList<T>::MaxLength(void) const
	{
		return m_maxLength;
	}
	// Clear
	template<class T>
	inline void TLList<T>::Clear(void)
	{
		LListNode<T> *travel = m_head;

		while (travel != nullptr)
		{
			LListNode<T> *next = travel->m_next;
			delete travel;
			travel = next;
		}

		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}
	// Display
	template<class T>
	inline void TLList<T>::Display(ostream & os) const
	{
		LListNode<T> * travel = m_head;
		while (travel != nullptr)
		{
			travel->Display();
			travel = travel->m_next;
			cout << endl;
		}
	}
}
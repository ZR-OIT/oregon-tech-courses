/****************************************************************************************************
* Author: Zak Rowland
* Filename: LListNode.h
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
# include <iostream>

using std::cout;
using std::ostream;
using std::endl;

namespace TLinkedList
{
	template <class N>
	class LListNode
	{
	public:
		template <class T> friend class TLList;
		LListNode(N data);
		~LListNode(void);
		friend ostream & operator << (ostream & os, const LListNode& node)
		{
			node.Display(os);
			return os;
		}
	private:
		N m_data;

		LListNode * m_next;
		LListNode * m_prev;

		void Display(ostream &os = cout) const;
	};
}
// Constructor
template<class N>
inline TLinkedList::LListNode<N>::LListNode(N data) : m_data(data), m_next(nullptr), m_prev(nullptr)
{
}
// Destructor
template<class N>
inline TLinkedList::LListNode<N>::~LListNode(void)
{
	m_next = nullptr;
	m_prev = nullptr;
}
// Display
template<class N>
inline void TLinkedList::LListNode<N>::Display(ostream & os) const
{
	cout << "Node: \n- Data: " << m_data; //<< "\n- Next: " << m_next->m_data << "\n- Prev: " << m_prev->m_data << endl;
}
/****************************************************************************************************
* Author: Zak Rowland
* Filename: List.cpp
* Date Created: 3/1/2018
* Modifications:
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include "List.h"
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

List::List(void) : m_head(nullptr), m_length(0)
{
}

List::~List(void)
{
	Purge();
}

void List::Append(const char * symbol, const char * name, double price)
{
	if (m_head == nullptr)
	{
		Prepend(symbol, name, price);
	}
	else
	{
		Node *newNode = new Node(symbol, name, price);
		Node *travel = m_head;

		while (travel->hasNext())
		{
			travel = travel->getNext();
		}
		travel->setNext(newNode);
		m_length++;
	}
}

void List::Prepend(const char * symbol, const char * name, double price)
{
	Node *newNode = new Node(symbol, name, price);

	newNode->setNext(m_head);
	m_head = newNode;
	m_length++;
}

void List::Purge(void)
{
	Node *travel = m_head;

	while (travel != nullptr)
	{
		Node *next = travel->getNext();
		delete travel;
		travel = next;
	}
	
	m_head = nullptr;
	m_length = 0;
}

void List::Display(void)
{
	Node *travel = m_head;

	while (travel != nullptr)
	{
		Node *next = travel->getNext();
		travel->Display();
		travel = next;
	}
}

Stock * List::FindStock(const char * symbol)
{
	Node *travel = m_head;
	Stock *ptr = nullptr;

	while ((travel != nullptr) && (ptr == nullptr))
	{
		ptr = travel->getStock(symbol);
		travel = travel->getNext();
	}
	return ptr;
}

size_t List::Length(void)
{
	return m_length;
}

void List::Delete(const char *key)
{
	Node *travel = m_head;
	Node *trail;

	if (travel->Compare(key) == 0)
	{
		trail = m_head;
		m_head = travel->getNext();
		delete trail;

		m_length--;
	}
	else
	{
		travel = m_head;

		while (travel != nullptr && (travel->Compare(key) != 0))
		{
			trail = travel;
			travel = travel->getNext();
		}

		if (travel == nullptr)
			cout << "Error" << endl;
		else
		{
			trail->setNext(travel->getNext());
			delete travel;
		}
		m_length--;
	}
}

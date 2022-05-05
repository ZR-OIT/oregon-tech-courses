/****************************************************************************************************
* Author: Zak Rowland
* Filename: Node.cpp
* Date Created: 3/1/2018
* Modifications:
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include "Node.h"
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Node::Node(const char * symbol, const char * name, double price)
	: m_next(nullptr), m_stock(new Stock(symbol, name, price))
{
}

Node::~Node(void)
{
	delete m_stock;
	m_stock = nullptr;
	m_next = nullptr;
}

bool Node::hasNext(void)
{
	return (m_next != nullptr);
}

Node * Node::getNext(void)
{
	return m_next;
}

void Node::setNext(Node * next)
{
	m_next = next;
}

void Node::Display(void)
{
	m_stock->Display();
}

int Node::Compare(const char * symbol)
{
	return m_stock->Compare(symbol);
}

Stock & Node::getStock(void)
{
	return *m_stock;
}

Stock * Node::getStock(const char * symbol)
{
	return ((Compare(symbol) == 0) ? m_stock : nullptr);
}

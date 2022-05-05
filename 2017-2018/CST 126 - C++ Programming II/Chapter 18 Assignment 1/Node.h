#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Stock.h"

#ifndef NODE_H
# define NODE_H

class Node
{
public:
	Node(const char *symbol, const char *name, double price);
	~Node(void);

	bool hasNext(void);
	Node *getNext(void);
	void setNext(Node *next);
	void Display(void);

	int Compare(const char *symbol);
	Stock & getStock(void);
	Stock * getStock(const char *symbol);

private:
	Node(void);
	Stock *m_stock;
	Node *m_next;
};

#endif // NODE_H

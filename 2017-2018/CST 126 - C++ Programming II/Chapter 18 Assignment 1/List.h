#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Stock.h"
#include "Node.h"

#ifndef LIST_H
# define LIST_H

class List
{
public:
	List(void);
	~List(void);

	void Append(const char *symbol, const char *name, double price);
	void Prepend(const char *symbol, const char *name, double price);
	void Purge(void);
	void Display(void);
	void Delete(const char *key);

	Stock * FindStock(const char *symbol);
	size_t Length(void);

private:
	Node * m_head;
	size_t m_length;
};

#endif // NODE_H
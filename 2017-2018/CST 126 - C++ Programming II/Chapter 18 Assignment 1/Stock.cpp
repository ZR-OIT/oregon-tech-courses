/****************************************************************************************************
* Author: Zak Rowland
* Filename: Stock.cpp
* Date Created: 3/1/2018
* Modifications:
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include "Stock.h"
#include <crtdbg.h>
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::setw;
using std::right;
using std::fixed;
using std::setprecision;

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
Stock::Stock(const char * symbol, const char * name, double price)
{
	m_symbol = new char[strlen(symbol) + 1];
	strcpy(m_symbol, symbol);
	
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);

	m_price = price;
}

/*****************************************************************************************************
* Function: 
* Purpose:
*****************************************************************************************************/
Stock::~Stock(void)
{
	delete[] m_symbol;
	delete[] m_name;
	m_price = -1;

	m_symbol = nullptr;
	m_name = nullptr;
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
void Stock::Display(void)
{
	cout << left << setw(6) << m_symbol << left << setw(32) << m_name << right << setw(10) << fixed << setprecision(2) << m_price << endl;
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
int Stock::Compare(const char * symbol)
{
	return strcmpi(m_symbol, symbol);
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
const char * Stock::getSymbol(void) const
{
	return this->m_symbol;
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
const char * Stock::getName(void) const
{
	return this->m_name;
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
double Stock::getPrice(void) const
{
	return this->m_price;
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
void Stock::setSymbol(const char * symbol)
{
	if (strcmp(symbol, m_symbol) != 0)
	{
		delete[] m_symbol;
		m_symbol = new char[strlen(symbol) + 1];
		strcpy(m_symbol, symbol);
	}
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
void Stock::setName(const char * name)
{
	if (strcmp(name, m_name) != 0)
	{
		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
}

/*****************************************************************************************************
* Function:
* Purpose:
*****************************************************************************************************/
void Stock::setPrice(const double price)
{
	m_price = price;
}

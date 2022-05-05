#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef STOCK_H
# define STOCK_H

class Stock
{
public:
	Stock(const char *symbol, const char *name, double price);
	~Stock(void);
	void Display(void);

	int Compare(const char *symbol);

	const char * getSymbol(void) const;
	const char * getName(void) const;
	double getPrice(void) const;

	void setSymbol(const char *symbol);
	void setName(const char *name);
	void setPrice(const double price);

private:
	Stock(void);
	char *m_symbol;
	char *m_name;
	double m_price;
};

#endif // STOCK_H
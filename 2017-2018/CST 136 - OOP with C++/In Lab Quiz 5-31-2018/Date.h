#pragma once

#ifndef DATE_H
# define DATE_H
# include <iostream>

using std::ostream;
using std::cout;
using std::endl;

class Date
{
public:
	Date(void);
	// if the year is less than 1950, add 1900 to it.
	Date(const unsigned short year, const unsigned short month, const unsigned short day);
	Date(const Date &date);

	~Date(void);

	Date &operator=(const Date &date);

	// if the year is less than 1950, add 1900 to it.
	void SetDate(const unsigned short year, const unsigned short month, const unsigned short day);
	void SetDate(const Date &date);
	unsigned short GetYear(void) const;
	unsigned short GetMonth(void) const;
	unsigned short GetDay(void) const;

	friend ostream & operator << (ostream &os, const Date &date);

	bool operator==(const Date &date);
	bool operator!=(const Date &date);
	bool operator <(const Date &date);
	bool operator >(const Date &date);
	bool operator<=(const Date &date);
	bool operator>=(const Date &date);

private:
	unsigned short m_year;
	unsigned short m_month;
	unsigned short m_day;
};

#endif // DATE_H

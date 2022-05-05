#include <iomanip>
#include "Date.h"

//using std::cout;
//using std::endl;
using std::setw;
//using std::left;
//using std::right;

Date::Date(void) : m_year(0), m_month(0), m_day(0)
{
	// empty
}

Date::Date(const unsigned short year, const unsigned short month, const unsigned short day)
	: m_year(year), m_month(month), m_day(day)
{
	if (m_year < 1950)
	{
		m_year += 1900;
	}
}

Date::Date(const Date & date) : Date(date.m_year, date.m_month, date.m_day)
{
	// empty
}

Date::~Date(void)
{
	// nothing to do in here
}

Date & Date::operator=(const Date & date)
{
	if (this != &date)
	{
		m_year = date.m_year;
		m_month = date.m_month;
		m_day = date.m_day;
	}
	return *this;
}

void Date::SetDate(const unsigned short year, const unsigned short month, const unsigned short day)
{
	m_year = year;
	m_month = month;
	m_day =day;
}

void Date::SetDate(const Date & date)
{
	SetDate(date.m_year, date.m_month, date.m_day);
}

unsigned short Date::GetYear(void) const
{
	return m_year;
}

unsigned short Date::GetMonth(void) const
{
	return m_month;
}

unsigned short Date::GetDay(void) const
{
	return m_day;
}

bool Date::operator==(const Date & date)
{
	bool result = false;

	result = (m_year == date.m_year && m_month == date.m_month && m_day == date.m_day ? true : false);

	return result;
}

bool Date::operator!=(const Date & date)
{
	return !(*this == date);
}

bool Date::operator<(const Date & date)
{
	bool result = false;

	if (m_year < date.m_year)
	{
		result = true;
	}
	else if (m_year > date.m_year)
	{
		result = false;
	}
	else if (m_month < date.m_month)
	{
		result = true;
	}
	else if (m_month > date.m_month)
	{
		result = false;
	}
	else if (m_day < date.m_day)
	{
		result = true;
	}

	return result;
}

bool Date::operator>(const Date & date)
{
	bool result = false;

	if (m_year > date.m_year)
	{
		result = true;
	}
	else if (m_year < date.m_year)
	{
		result = false;
	}
	else if (m_month > date.m_month)
	{
		result = true;
	}
	else if (m_month < date.m_month)
	{
		result = false;
	}
	else if (m_day > date.m_day)
	{
		result = true;
	}

	return result;
}

bool Date::operator<=(const Date & date)
{
	return (*this == date) || (*this < date);
}

bool Date::operator>=(const Date & date)
{
	return (*this == date) || (*this > date);
}

ostream & operator<<(ostream & os, const Date & date)
{
	os << setw(4) << date.m_year 
		<< "-" << (date.m_month < 10 ? "0" : "") << date.m_month
		<< "-" << (date.m_day < 10 ? "0" : "") << date.m_day;

	return os;
}

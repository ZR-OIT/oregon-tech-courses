#pragma once

#ifndef PERSON_H
# define PERSON_H
# define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout;
using std::endl;
using std::setw;
using std::left;

class Person
{
public:
	Person(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);
	~Person(void);
	// Copy constructor
	Person(const Person &person);
	// Assignment operator.
	Person &operator=(const Person &person);

	void Display(void) const;

	int Compare(const char *fname, const char *lname) const;
	char *GetFName(void) const;
	char *GetLName(void) const;
	char *GetEMail(void) const;
	char *GetStreet(void) const;
	char *GetCity(void) const;
	char *GetState(void) const;
	char *GetZip(void) const;

private:
	// We don't want a Person without an identity.
	Person(void);

	// frees all memory for the instance.
	void clear(void);

	char *m_fname;
	char *m_lname;
	char *m_email;
	char *m_street;
	char *m_city;
	char *m_state;
	char *m_zip;
};

#endif // PERSON_H

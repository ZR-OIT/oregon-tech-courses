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
	// basic ctor
	Person(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	// the dtor
	~Person(void);

	// Copy constructor
	Person(const Person &person);

	// Assignment operator.
	Person &operator=(const Person &person);

	// so we can all have the same looking output.
	void Display(void) const
	{
		cout << left << setw(12) << m_fname << "  "
			<< left << setw(12) << m_lname << "  "
			<< left << setw(30) << m_email << "  "
			<< left << setw(22) << m_street << "  "
			<< left << setw(15) << m_city << "  "
			<< left << setw(15) << m_state << "  "
			<< left << setw(10) << m_zip << endl;
	};

	// compare the given names with the instance.
	// compare the last names and then first names, only when last names compare
	// the same.
	int Compare(const char *fname, const char *lname) const;

	// return a pointer to the private data.
	char *GetFName(void) const;
	char *GetLName(void) const;
	char *GetEMail(void) const;
	char *GetStreet(void) const;
	char *GetCity(void) const;
	char *GetState(void) const;
	char *GetZip(void) const;

	void SetFName(const char *str);
	void SetLName(const char *str);
	void SetEMail(const char *str);
	void SetStreet(const char *str);
	void SetCity(const char *str);
	void SetState(const char *str);
	void SetZip(const char *str);

	// set all the member variables in one swell foop.
	void Set(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

private:
	// We don't want a Person without an identity.
	// This prevents the default Person ctor from being called from outside
	// the class.s
	Person(void);

	// frees all memory for the instance.
	// the dtor should call this method and not duplicate code.
	void clear(void);

	// since you do the allocate and strcpy functions in a couple different
	// places (copy ctor, assignment op, ...), put all that in here so you
	// reuse code, not copy code.
	void allocate(const char *fname, const char *lname, const char *email,
		const char *street, const char *city, const char *state, const char *zip);

	char *m_fname;
	char *m_lname;
	char *m_email;
	char *m_street;
	char *m_city;
	char *m_state;
	char *m_zip;
};

#endif // PERSON_H

/****************************************************************************************************
* Author: Zak Rowland
* Filename: Person.cpp
* Date Created: 3/8/2018
* Modifications:
*****************************************************************************************************
* Assignment: Doubly Linked List
*
* Overview: Read file containing names and addresses. Create a linked list of the names and addresses.
*			The linked list must be a doubly linked list, there must be m_next and m_prev pointers.
*			The linked list must be stored ordered by last name and first name.
*			Be able to display the list in both forward and reverse directions.
*
* Input: "AddressBook.csv"
*
* Output: Address list
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Person.h"
#include <crtdbg.h>
#include <iomanip>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::setw;

/*****************************************************************************************************
* Function: Person(const char * fname, const char * lname, const char * email, const char * street,
*					const char * city, const char * state, const char * zip)
* Purpose: Constructor
*****************************************************************************************************/
Person::Person(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	m_fname = new char[strlen(fname) + 1];
	strcpy(m_fname, fname);

	m_lname = new char[strlen(lname) + 1];
	strcpy(m_lname, lname);

	m_email = new char[strlen(email) + 1];
	strcpy(m_email, email);

	m_street = new char[strlen(street) + 1];
	strcpy(m_street, street);

	m_city = new char[strlen(city) + 1];
	strcpy(m_city, city);

	m_state = new char[strlen(state) + 1];
	strcpy(m_state, state);

	m_zip = new char[strlen(zip) + 1];
	strcpy(m_zip, zip);
}

/*****************************************************************************************************
* Function: ~Person(void)
* Purpose: Destructor
*****************************************************************************************************/
Person::~Person(void)
{
	clear();
}

/*****************************************************************************************************
* Function: Person(const Person & person)
* Purpose: Copy constructor
*****************************************************************************************************/
Person::Person(const Person & person)
{
	Person(person.m_fname, person.m_lname, person.m_email, person.m_street, person.m_city, person.m_state, person.m_zip);
}

/*****************************************************************************************************
* Function: operator=(const Person & person)
* Purpose: Assignment operator
*****************************************************************************************************/
Person & Person::operator=(const Person & person)
{
	if (Compare(person.m_fname, person.m_lname) != 0)
	{
		delete[] m_fname;
		m_fname = new char[strlen(person.m_fname) + 1];
		strcpy(m_fname, person.m_fname);

		delete[] m_lname;
		m_lname = new char[strlen(person.m_lname) + 1];
		strcpy(m_lname, person.m_lname);

		delete[] m_email;
		m_email = new char[strlen(person.m_email) + 1];
		strcpy(m_email, person.m_email);

		delete[] m_street;
		m_street = new char[strlen(person.m_street) + 1];
		strcpy(m_street, person.m_street);

		delete[] m_city;
		m_city = new char[strlen(person.m_city) + 1];
		strcpy(m_city, person.m_city);

		delete[] m_state;
		m_state = new char[strlen(person.m_state) + 1];
		strcpy(m_state, person.m_state);

		delete[] m_zip;
		m_zip = new char[strlen(person.m_zip) + 1];
		strcpy(m_zip, person.m_zip);
	}

	return *this;
}

/*****************************************************************************************************
* Function: Display(void) const
* Purpose: Displays person
*****************************************************************************************************/
void Person::Display(void) const
{
	cout << left << setw(16) << m_fname << setw(16) << m_lname << setw(32) << m_email << setw(32)
			<< m_street << setw(16) << m_city << setw(4) << m_state << setw(10) << m_zip << endl;
}

/*****************************************************************************************************
* Function: Compare(const char * fname, const char * lname) const
* Purpose: Compares names
*****************************************************************************************************/
int Person::Compare(const char * fname, const char * lname) const
{
	int compare = 0;

	if (_strcmpi(m_lname, lname) == 0)
	{
		compare = _strcmpi(m_fname, fname);
	}
	else
	{
		compare = _strcmpi(m_lname, lname);
	}

	return compare;
}

/*****************************************************************************************************
* Function: GetFName(void) const
* Purpose: Gets first name
*****************************************************************************************************/
char * Person::GetFName(void) const
{
	return this->m_fname;
}

/*****************************************************************************************************
* Function: GetLName(void) const
* Purpose: Gets last name
*****************************************************************************************************/
char * Person::GetLName(void) const
{
	return this->m_lname;
}

/*****************************************************************************************************
* Function: GetEMail(void) const
* Purpose: Gets email
*****************************************************************************************************/
char * Person::GetEMail(void) const
{
	return this->m_email;
}

/*****************************************************************************************************
* Function: GetStreet(void) const
* Purpose: Gets street
*****************************************************************************************************/
char * Person::GetStreet(void) const
{
	return this->m_street;
}

/*****************************************************************************************************
* Function: GetCity(void) const
* Purpose: Gets city
*****************************************************************************************************/
char * Person::GetCity(void) const
{
	return this->m_city;
}

/*****************************************************************************************************
* Function: GetState(void) const
* Purpose: Gets state
*****************************************************************************************************/
char * Person::GetState(void) const
{
	return this->m_state;
}

/*****************************************************************************************************
* Function: GetZip(void) const
* Purpose: Gets zip code
*****************************************************************************************************/
char * Person::GetZip(void) const
{
	return this->m_zip;
}

/*****************************************************************************************************
* Function: clear(void)
* Purpose: Deallocates used memory
*****************************************************************************************************/
void Person::clear(void)
{
	delete[] m_fname;
	delete[] m_lname;
	delete[] m_email;
	delete[] m_street;
	delete[] m_city;
	delete[] m_state;
	delete[] m_zip;

	m_fname = nullptr;
	m_lname = nullptr;
	m_email = nullptr;
	m_street = nullptr;
	m_city = nullptr;
	m_state = nullptr;
	m_zip = nullptr;
}

/****************************************************************************************************
* Author: Zak Rowland
* Filename: Person.cpp
* Date Created: 4/7/2018
* Modifications:
*****************************************************************************************************
* Assignment: Lab 2 - Address List
*
* Overview: Create a doubly linked list of the names and addresses, based on the provided files
*			and sample data.
*
* Input:	Tests from main.cpp and data from CSV files.
*
* Output:	Results of tests from main.cpp.
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Person.h"

using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: Person(const char * fname, const char * lname, const char * email, const ... )
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: Class object with properly allocated memory.
*****************************************************************************************************/
Person::Person(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	allocate(fname, lname, email, street, city, state, zip);
}

/*****************************************************************************************************
* Function: ~Person(void)
* Purpose: Destructor
* Preconditon: Class object with properly allocated memory.
* Postcondition: Class object memory returned to heap and pointers set to null.
*****************************************************************************************************/
Person::~Person(void)
{
	clear();
}

/*****************************************************************************************************
* Function: Person(const Person & person)
* Purpose: Copy constructor
* Preconditon: A Person class object to be copied.
* Postcondition: A copy of the passed class object.
*****************************************************************************************************/
Person::Person(const Person & person): Person(person.m_fname, person.m_lname, person.m_email, person.m_street,
												person.m_city, person.m_state, person.m_zip)
{
	//empty
}

/*****************************************************************************************************
* Function: Person::operator=(const Person & person)
* Purpose: Assignment operator
* Preconditon: A Person class object to be assigned to the current class object.
* Postcondition: If the current object is equal to the passed object, make no change.
*				 Otherwise, allocate and copy the passed object into the current object.
*****************************************************************************************************/
Person & Person::operator=(const Person & person)
{
	//if (Compare(person.m_fname, person.m_lname) != 0)
	if (this != &person)
	{
		clear();
		allocate(person.m_fname, person.m_lname, person.m_email, person.m_street,
					person.m_city, person.m_state, person.m_zip);
	}
	return *this;
}

/*****************************************************************************************************
* Function: Compare(const char * fname, const char * lname) const
* Purpose: Compares last and first names.
* Preconditon: 
* Postcondition: If the current last name equals the passed last name, compare first names and return value.
				 Otherwise, return the value obtained by comparing last names.
*****************************************************************************************************/
int Person::Compare(const char * fname, const char * lname) const
{
	int test = strcmp(lname, m_lname);
	
	if (test == 0)
		test = strcmp(fname, m_fname);

	return test;
}

/****************************************************************************************************
* Function:GetFName(void) const
* Purpose: Returns a pointer to the m_fname data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetFName(void) const
{
	return m_fname;
}

/*****************************************************************************************************
* Function:GetLName(void) const
* Purpose: Returns a pointer to the m_lname data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetLName(void) const
{
	return m_lname;
}

/*****************************************************************************************************
* Function:GetEMail(void) const
* Purpose: Returns a pointer to the m_email data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetEMail(void) const
{
	return m_email;
}

/*****************************************************************************************************
* Function:GetStreet(void) const
* Purpose: Returns a pointer to the m_street data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetStreet(void) const
{
	return m_street;
}

/*****************************************************************************************************
* Function:GetCity(void) const
* Purpose: Returns a pointer to the m_city data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetCity(void) const
{
	return m_city;
}

/*****************************************************************************************************
* Function:GetState(void) const
* Purpose: Returns a pointer to the m_state data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetState(void) const
{
	return m_state;
}

/*****************************************************************************************************
* Function:GetZip(void) const
* Purpose: Returns a pointer to the m_zip data member.
* Preconditon: No access to private data members.
* Postcondition: A pointer to a private data member.
*****************************************************************************************************/
char * Person::GetZip(void) const
{
	return m_zip;
}

/*****************************************************************************************************
* Function:SetFName(void) const
* Purpose: Changes the value of the m_fname data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetFName(const char * str)
{
	if (m_fname != nullptr)
		delete[] m_fname;
	m_fname = new char[strlen(str) + 1];
	strcpy(m_fname, str);
}

/*****************************************************************************************************
* Function:SetLName(void) const
* Purpose: Changes the value of the m_lname data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetLName(const char * str)
{
	if (m_lname != nullptr)
		delete[] m_lname;
	m_lname = new char[strlen(str) + 1];
	strcpy(m_lname, str);
}

/*****************************************************************************************************
* Function:SetEMail(void) const
* Purpose: Changes the value of the m_email data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetEMail(const char * str)
{
	if (m_email != nullptr)
		delete[] m_email;
	m_email = new char[strlen(str) + 1];
	strcpy(m_email, str);
}

/*****************************************************************************************************
* Function:SetStreet(void) const
* Purpose: Changes the value of the m_street data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetStreet(const char * str)
{
	if (m_street != nullptr)
		delete[] m_street;
	m_street = new char[strlen(str) + 1];
	strcpy(m_street, str);
}

/*****************************************************************************************************
* Function:SetCity(void) const
* Purpose: Changes the value of the m_city data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetCity(const char * str)
{
	if (m_city != nullptr)
		delete[] m_city;
	m_city = new char[strlen(str) + 1];
	strcpy(m_city, str);
}

/*****************************************************************************************************
* Function:SetState(void) const
* Purpose: Changes the value of the m_state data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetState(const char * str)
{
	if (m_state != nullptr)
		delete[] m_state;
	m_state = new char[strlen(str) + 1];
	strcpy(m_state, str);
}

/*****************************************************************************************************
* Function:SetZip(void) const
* Purpose: Changes the value of the m_zip data member.
* Preconditon: No access to private data members.
* Postcondition: A changed private data member.
*****************************************************************************************************/
void Person::SetZip(const char * str)
{
	if (m_zip != nullptr)
		delete[] m_zip;
	m_zip = new char[strlen(str) + 1];
	strcpy(m_zip, str);
}

/*****************************************************************************************************
* Function: Set(const char * fname, const char * lname, const char * email, const ...)
* Purpose: Changes the value of all data members at once.
* Preconditon: A class object.
* Postcondition: A class object with new allocated data that was passed. 
*****************************************************************************************************/
void Person::Set(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	clear();
	allocate(fname, lname, email, street, city, state, zip);
}

/*****************************************************************************************************
* Function: clear(void)
* Purpose: Frees all memory for the instance.
* Preconditon: A class object that has allocated memory.
* Postcondition: All memory returned to heap and pointers assigned to null.
*****************************************************************************************************/
void Person::clear(void)
{
	delete[] m_fname;
	m_fname = nullptr;

	delete[] m_lname;
	m_lname = nullptr;

	delete[] m_email;
	m_email = nullptr;

	delete[] m_street;
	m_street = nullptr;

	delete[] m_city;
	m_city = nullptr;

	delete[] m_state;
	m_state = nullptr;

	delete[] m_zip;
	m_zip = nullptr;
}

/*****************************************************************************************************
* Function: allocate(const char * fname, const char * lname, const char * email, const ...)
* Purpose: Allocates the necessary space from the heap for all character pointers.
* Preconditon: Data with no memory to be stored into.
* Postcondition: Allocated memory with data copied in.
*****************************************************************************************************/
void Person::allocate(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
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

/****************************************************************************************************
* Author: Zak Rowland
* Filename: Person.cpp
* Date Created: 5/3/2018
* Modifications: Original code by Jesse Chaney
*****************************************************************************************************
* Assignment: Inheritance Lab 5
*
* Overview: Take the files we used in class forthe inheritance demo from Monday(Person, Student, Teacher)
*			and add a few things.
*
* Input: Tests from main.cpp
*
* Output: Results of test from main.cpp
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include "Person.h"
using std::cout;
using std::endl;

Person::Person(void) : m_age(0), m_protected_person(-1)
{
	cout << "** in Person defalt ctor" << endl;
	m_fname = new char[1];
	m_lname = new char[1];
	m_fname[0] = '\0';
	m_lname[0] = '\0';
}

Person::Person(const int age, const char * fname, const char * lname)
	: m_age(age), m_protected_person(-2)
{
	cout << "** in Person 3 arg ctor" << endl;
	m_fname = new char[strlen(fname) + 1];
	m_lname = new char[strlen(lname) + 1];
	strcpy(m_fname, fname);
	strcpy(m_lname, lname);
}

Person::Person(const Person & person)
	: Person(person.m_age, person.m_fname, person.m_lname)
{
	cout << "** in Person copy ctor" << endl;
}

Person & Person::operator=(const Person & person)
{
	cout << "** in Person assignment op" << endl;
	if (this != &person)
	{
		delete[] m_fname;
		delete[] m_lname;
		m_fname = new char[strlen(person.m_fname) + 1];
		m_lname = new char[strlen(person.m_lname) + 1];
		strcpy(m_fname, person.m_fname);
		strcpy(m_lname, person.m_lname);
		m_age = person.m_age;
	}
	return *this;
}

int Person::GetAge(void)
{
	return m_age;
}

void Person::SetAge(const int age)
{
	m_age = age;
}

Person::~Person(void)
{
	cout << "** in Person dtor" << endl;

	delete[] m_fname;
	delete[] m_lname;
	m_fname = m_lname = nullptr;
	m_age = 0;
	m_protected_person = 0;
}

ostream & operator<<(ostream & os, const Person & person)
{
	os << "Person: fname: " << person.m_fname
		<< "  lname: " << person.m_lname
		<< "  age: " << person.m_age
		<< endl;
	return os;
}

void Person::Display(void) const
{
	cout << "*Person Display: fname, lname, age: " << m_fname << ", "
		<< m_lname << ", " << m_age << endl;
}


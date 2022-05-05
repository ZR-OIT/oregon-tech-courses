/****************************************************************************************************
* Author: Zak Rowland
* Filename: Teacher.cpp
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

#include <cstdlib>
#include "Teacher.h"
using std::cout;
using std::endl;

int Teacher::m_next_id = 1;

Teacher::Teacher(void)
	: Person(), m_years(0), m_id(m_next_id++)
{
	cout << "*** Teacher default ctor" << endl;
}

Teacher::Teacher(const int age, const char * fname, const char * lname, const int years, const char *title)
	: Person(age, fname, lname), m_years(years), m_id(m_next_id++)
{
	cout << "*** Teacher 5 arg ctor" << endl;
	m_title = new char[strlen(title) + 1];
	strcpy(m_title, title);
}

Teacher::Teacher(const Teacher & teacher)
	: Person(teacher), m_years(teacher.m_years), m_id(m_next_id++)
{
	cout << "*** Teacher copy ctor" << endl;
}

Teacher & Teacher::operator=(const Teacher & teacher)
{
	if (this != &teacher)
	{
		Person::operator=(teacher);

		m_id = m_next_id++;
		m_years = teacher.m_years;
	}
	return *this;
}

void Teacher::Display(void) const
{
	Person::Display();
	cout << "**Teacher Display: id, years: " << m_id << ", " << m_years << "  title: " << m_title << endl;
}

/*****************************************************************************************************
* Function: Show(void) const
* Purpose: Calls the Display function
* Preconditon: A Teacher object
* Postcondition: Data printed from Teacher object
*****************************************************************************************************/
void Teacher::Show(void) const
{
	Display();
}

void Teacher::Promote(const char * title)
{
	cout << "\tTeacher Promote: " << title << endl;
	delete[] m_title;
	m_title = new char[strlen(title) + 1];
	strcpy(m_title, title);
}

Teacher::~Teacher()
{
	cout << "*** in Teacher dtor" << endl;

	delete[] m_title;
	m_title = nullptr;
}

ostream & operator<<(ostream & os, const Teacher & teacher)
{
	os << static_cast<const Person &>(teacher);

	os << "\tTeacher: id: " << teacher.m_id << "  years:" << teacher.m_years << "  title: " << teacher.m_title << endl;

	return os;
}

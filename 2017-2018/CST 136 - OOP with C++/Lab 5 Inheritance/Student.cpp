/****************************************************************************************************
* Author: Zak Rowland
* Filename: Student.cpp
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

#include "Student.h"

using std::cout;
using std::endl;

int Student::m_next_id = 1;

Student::Student(void)
	: Person(), m_protected_student(-3), m_gpa(4.0), m_id(m_next_id++)
{
	cout << "*** in Student defalt ctor" << endl;
	m_major = new char[1];
	*m_major = '\0';

	m_protected_person = 17;
}

Student::Student(const int age, const char * fname, const char * lname, const float gpa, const char *major)
	: Person(age, fname, lname), m_gpa(gpa), m_protected_student(-4), m_id(m_next_id++)
{
	cout << "*** Student 4 arg ctor" << endl;
	m_major = new char[strlen(major) + 1];
	strcpy(m_major, major);

	m_protected_person = 23;
}

Student::Student(const Student & student)
	: Person(student)
	, m_gpa(student.m_gpa), m_id(m_next_id++)
{
	cout << "*** Student copy ctor" << endl;

	m_major = new char[strlen(student.m_major) + 1];
	strcpy(m_major, student.m_major);
}

Student & Student::operator=(const Student & student)
{
	if (this != &student)
	{
		Person::operator=(student);

		m_id = m_next_id++;
		m_gpa = student.m_gpa;

		delete[] m_major;
		m_major = new char[strlen(student.m_major) + 1];
		strcpy(m_major, student.m_major);
	}
	return *this;
}

Student::~Student(void)
{
	cout << "*** in Student dtor" << endl;
	delete[] m_major;
	m_major = nullptr;
}

ostream & operator<<(ostream & os, const Student & student)
{
	os << static_cast<const Person &>(student);

	os << "\tStudent: protected person member: " << student.m_protected_person << endl;
	os << "\tStudent: id: " << student.m_id << "   gpa: " << student.m_gpa << endl;

	return os;
}

void Student::Display(void) const
{
	cout << "Student Display: protected person member: " << m_protected_person << endl;
	Person::Display();
	cout << "**Student Display: id, gpa, major: " << m_id << ", " << m_gpa
		<< ", " << m_major << endl;
}

/*****************************************************************************************************
* Function: Show(void) const
* Purpose: Calls the Display function
* Preconditon: A Student object
* Postcondition: Data printed from Student object
*****************************************************************************************************/
void Student::Show(void) const
{
	Display();
}

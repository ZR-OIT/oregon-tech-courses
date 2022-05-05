/****************************************************************************************************
* Author: Zak Rowland
* Filename: CSETTa.cpp
* Date Created: 5/3/2018
* Modifications:
*****************************************************************************************************
* Assignment: Inheritance Lab 5
*
* Overview: Take the files we used in class forthe inheritance demo from Monday (Person, Student,
*			Teacher) and add a few things.
*
* Input: Tests from main.cpp
*
* Output: Results of test from main.cpp
*
*****************************************************************************************************/
#include "CSETTa.h"
#include <iostream>

using std::cout;
using std::endl;

/*****************************************************************************************************
* Function: CSETTa(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: A new CSETTa object
*****************************************************************************************************/
CSETTa::CSETTa(void) : CSETStudent(), Teacher(), m_hoursPerWeek(0)
{
	m_class = new char[1];
	*m_class = '\0';
}

/*****************************************************************************************************
* Function: CSETTa(const int age, const char * fname, const char * lname, ... )
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new CSETTa object
*****************************************************************************************************/
CSETTa::CSETTa(const int age, const char * fname, const char * lname, const float gpa,
		const char *major, const int energyDrinks, const char *favGame,
		const char *advisor, const int years, const char *title, const char *taClass, const unsigned hours) 
	: Person(age, fname, lname), CSETStudent(age, fname, lname, gpa, major, energyDrinks, favGame, advisor), 
		Teacher(age, fname, lname, years, title), m_hoursPerWeek(hours)
{
	m_class = new char[strlen(taClass) + 1];
	strcpy(m_class, taClass);
}

/*****************************************************************************************************
* Function: CSETTa(const CSETTa & csetTa)
* Purpose: Copy constructor
* Preconditon: No class object
* Postcondition: A new CSETTa object
*****************************************************************************************************/
CSETTa::CSETTa(const CSETTa & csetTa)
	: CSETStudent(csetTa), Teacher(csetTa), m_hoursPerWeek(csetTa.m_hoursPerWeek)
{
	m_class = new char[strlen(csetTa.m_class) + 1];
	strcpy(m_class, csetTa.m_class);
}

/*****************************************************************************************************
* Function: operator=(const CSETTa & csetTa)
* Purpose: Assignment operator
* Preconditon: Two CSETTa class objects
* Postcondition: Current class object set equal to passed class object
*****************************************************************************************************/
CSETTa & CSETTa::operator=(const CSETTa & csetTa)
{
	if (this != &csetTa)
	{
		Person::operator=(csetTa);
		CSETStudent::operator=(csetTa);
		Teacher::operator=(csetTa);

		m_hoursPerWeek = csetTa.m_hoursPerWeek;

		m_class = new char[strlen(csetTa.m_class) + 1];
		strcpy(m_class, csetTa.m_class);
	}

	return *this;
}

/*****************************************************************************************************
* Function: ~CSETTa()
* Purpose: Destructor
* Preconditon: A CSETTa class object
* Postcondition: Object deleted and memory freed
*****************************************************************************************************/
CSETTa::~CSETTa()
{
	delete[] m_class;
	m_class = nullptr;
}

/*****************************************************************************************************
* Function: Display(void) const
* Purpose: Displays a CSETTa object
* Preconditon: A CSETTa object
* Postcondition: Data printed from CSETTa object
*****************************************************************************************************/
void CSETTa::Display(void) const
{
	CSETStudent::Display();
	Teacher::Display();
	cout << "**CSETTa Display: class: " << m_class << ", " << "hours: " << m_hoursPerWeek << endl;
}

/*****************************************************************************************************
* Function: Show(void) const
* Purpose: Calls the Display function
* Preconditon: A CSETTa object
* Postcondition: Data printed from CSETTa object
*****************************************************************************************************/
void CSETTa::Show(void) const
{
	Display();
}

/*****************************************************************************************************
* Function: operator<<(ostream & os, const CSETTa & csetTa)
* Purpose: Insertion operator
* Preconditon: A CSETTa class object
* Postcondition: Sends data from the class object to the output stream
*****************************************************************************************************/
ostream & operator<<(ostream & os, const CSETTa & csetTa)
{
	os << static_cast<const CSETStudent &>(csetTa);
	os << static_cast<const Teacher &>(csetTa);

	os << "\t CSETTa: class: " << csetTa.m_class << ", " << "hours: " << csetTa.m_hoursPerWeek << endl;

	return os;
}

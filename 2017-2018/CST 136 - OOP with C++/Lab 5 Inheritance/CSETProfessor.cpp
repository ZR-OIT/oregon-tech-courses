/****************************************************************************************************
* Author: Zak Rowland
* Filename: CSETProfessor.cpp
* Date Created: 5/3/2018
* Modifications:
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
#include "CSETProfessor.h"
#include <iostream>

using std::cout;
using std::endl;

/*****************************************************************************************************
* Function: CSETProfessor(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: A new CSETProfessor object
*****************************************************************************************************/
CSETProfessor::CSETProfessor(void) : Teacher(), m_hasBeard(false)
{
	m_office = new char[1];
	*m_office = '\0';
}

/*****************************************************************************************************
* Function: CSETProfessor(const int age, const char * fname, ... )
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new CSETProfessor object
*****************************************************************************************************/
CSETProfessor::CSETProfessor(const int age, const char * fname, const char * lname, const int years,
	const char *title, const char * office, const bool beard) : Person(age, fname, lname), 
	Teacher(age, fname, lname, years, title), m_hasBeard(beard)
{
	m_office = new char[strlen(office) + 1];
	strcpy(m_office, office);
}

/*****************************************************************************************************
* Function: CSETProfessor(const CSETProfessor & csetProf)
* Purpose: Copy constructor
* Preconditon: No class object
* Postcondition: A new CSETProfessor object
*****************************************************************************************************/
CSETProfessor::CSETProfessor(const CSETProfessor & csetProf)
	: Teacher(csetProf), m_hasBeard(csetProf.m_hasBeard)
{
	m_office = new char[strlen(csetProf.m_office) + 1];
	strcpy(m_office, csetProf.m_office);
}

/*****************************************************************************************************
* Function: operator=(const CSETProfessor & csetProf)
* Purpose: Assignment operator
* Preconditon: Two CSETProfessor class objects
* Postcondition: Current class object set equal to passed class object
*****************************************************************************************************/
CSETProfessor & CSETProfessor::operator=(const CSETProfessor & csetProf)
{
	if (this != &csetProf)
	{
		Person::operator=(csetProf);
		Teacher::operator=(csetProf);

		m_hasBeard = csetProf.m_hasBeard;

		m_office = new char[strlen(csetProf.m_office) + 1];
		strcpy(m_office, csetProf.m_office);
	}

	return *this;
}

/*****************************************************************************************************
* Function: ~CSETProfessor()
* Purpose: Destructor
* Preconditon: A CSETProfessor class object
* Postcondition: Object deleted and memory freed
*****************************************************************************************************/
CSETProfessor::~CSETProfessor()
{
	delete[] m_office;
	m_office = nullptr;
}

/*****************************************************************************************************
* Function: Display(void) const
* Purpose: Displays a CSETProfessor object
* Preconditon: A CSETProfessor object
* Postcondition: Data printed from CSETProfessor object
*****************************************************************************************************/
void CSETProfessor::Display(void) const
{
	Teacher::Display();
	cout << "**CSETProfessor Display: office: " << m_office << ", " << "has beard: " << m_hasBeard << endl;
}

/*****************************************************************************************************
* Function: Show(void) const
* Purpose: Calls the Display function
* Preconditon: A CSETProfessor object
* Postcondition: Data printed from CSETProfessor object
*****************************************************************************************************/
void CSETProfessor::Show(void) const
{
	Display();
}

/*****************************************************************************************************
* Function: operator<<(ostream & os, const CSETProfessor & csetProf)
* Purpose: Insertion operator
* Preconditon: A CSETProfessor class object
* Postcondition: Sends data from the class object to the output stream
*****************************************************************************************************/
ostream & operator<<(ostream & os, const CSETProfessor & csetProf)
{
	os << static_cast<const Teacher &>(csetProf);
	os << "\t CSETProfessor: office: " << csetProf.m_office << ", " << "has beard: " << csetProf.m_hasBeard << endl;

	return os;
}

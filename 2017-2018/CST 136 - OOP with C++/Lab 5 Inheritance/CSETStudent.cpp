/****************************************************************************************************
* Author: Zak Rowland
* Filename: CSETStudent.cpp
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
#include "CSETStudent.h"
#include <iostream>

using std::cout;
using std::endl;

/*****************************************************************************************************
* Function: CSETStudent(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: A new CSETStudent object
*****************************************************************************************************/
CSETStudent::CSETStudent(void) : Student(), m_energyDrinks(0)
{
	m_favGame = new char[1];
	*m_favGame = '\0';

	m_advisor = new char[1];
	*m_advisor = '\0';
}

/*****************************************************************************************************
* Function: CSETStudent(const int age, const char * fname, ... )
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new CSETStudent object
*****************************************************************************************************/
CSETStudent::CSETStudent(const int age, const char * fname, const char * lname, const float gpa,
	const char *major, const int energyDrinks, const char * favGame, const char * advisor)
	: Person(age, fname, lname), Student(age, fname, lname, gpa, major), m_energyDrinks(energyDrinks)
{
	m_favGame = new char[strlen(favGame) + 1];
	strcpy(m_favGame, favGame);

	m_advisor = new char[strlen(advisor) + 1];
	strcpy(m_advisor, advisor);
}

/*****************************************************************************************************
* Function: CSETStudent(const CSETStudent & csetStud)
* Purpose: Copy constructor
* Preconditon: No class object
* Postcondition: A new CSETStudent object
*****************************************************************************************************/
CSETStudent::CSETStudent(const CSETStudent & csetStud)
	: Student(csetStud), m_energyDrinks(csetStud.m_energyDrinks)
{
	m_favGame = new char[strlen(csetStud.m_favGame) + 1];
	strcpy(m_favGame, csetStud.m_favGame);

	m_advisor = new char[strlen(csetStud.m_advisor) + 1];
	strcpy(m_advisor, csetStud.m_advisor);
}

/*****************************************************************************************************
* Function: operator=(const CSETStudent & csetStud)
* Purpose: Assignment operator
* Preconditon: Two CSETStudent class objects
* Postcondition: Current class object set equal to passed class object
*****************************************************************************************************/
CSETStudent & CSETStudent::operator=(const CSETStudent & csetStud)
{
	if (this != &csetStud)
	{
		Person::operator=(csetStud);
		Student::operator=(csetStud);

		m_energyDrinks = csetStud.m_energyDrinks;

		delete[] m_favGame;
		m_favGame = new char[strlen(csetStud.m_favGame) + 1];
		strcpy(m_favGame, csetStud.m_favGame);

		delete[] m_advisor;
		m_advisor = new char[strlen(csetStud.m_advisor) + 1];
		strcpy(m_advisor, csetStud.m_advisor);
	}
	return *this;
}

/*****************************************************************************************************
* Function: ~CSETStudent()
* Purpose: Destructor
* Preconditon: A CSETStudent class object
* Postcondition: Object deleted and memory freed
*****************************************************************************************************/
CSETStudent::~CSETStudent()
{
	delete[] m_favGame;
	delete[] m_advisor;

	m_favGame = nullptr;
	m_advisor = nullptr;
}

/*****************************************************************************************************
* Function: Display(void) const
* Purpose: Displays a CSETStudent object
* Preconditon: A CSETStudent object
* Postcondition: Data printed from CSETStudent object
*****************************************************************************************************/
void CSETStudent::Display(void) const
{
	Student::Display();
	cout << "**CSETStudent Display: energy drinks: " << m_energyDrinks << ", " << "favorite game: "
		<< m_favGame << ", " << "advisor: " << m_advisor << endl;
}

/*****************************************************************************************************
* Function: Show(void) const
* Purpose: Calls the Display function
* Preconditon: A CSETStudent object
* Postcondition: Data printed from CSETStudent object
*****************************************************************************************************/
void CSETStudent::Show(void) const
{
	Display();
}

/*****************************************************************************************************
* Function: operator<<(ostream & os, const CSETStudent & csetStud)
* Purpose: Insertion operator
* Preconditon: A CSETStudent class object
* Postcondition: Sends data from the class object to the output stream
*****************************************************************************************************/
ostream & operator<<(ostream & os, const CSETStudent & csetStud)
{
	os << static_cast<const Student &>(csetStud);
	os << "\t CSETStudent: energy drinks : " << csetStud.m_energyDrinks << ", " << "favorite game : "
		<< csetStud.m_favGame << ", " << "advisor: " << csetStud.m_advisor << endl;

	return os;
}

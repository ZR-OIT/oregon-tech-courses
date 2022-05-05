/****************************************************************************************************
* Author: Zak Rowland
* Filename: main.cpp
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
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <crtdbg.h>
#include "CSETTa.h"

using std::cout;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Creates an array of pointers to different class objects and displays them
* Preconditon: No class objects
* Postcondition: Data printed from the array of class objects
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Student *student = new Student(19, "Billy", "Bob", 3.5f, "CET");
	Teacher *teacher = new Teacher(51, "Joe", "Jones", 10, "Professor");
	CSETStudent *cstud = new CSETStudent(20, "Cody", "Wrighter", 4.0f, "SET", 5, "Minesweeper", "Jesse Chaney");
	CSETProfessor *cprof = new CSETProfessor(1, "Jesse", "Chaney", 25, "Software Professor", "PV 167", true);
	CSETTa *cta = new CSETTa(25, "John", "Doe", 4.5f, "EMBEDDED", 10, "Operation", "Troy Scevers", 2, "Embedded TA", "Embedded C", 2);

	Person *ptr[] = { student, teacher, cstud, cprof, cta };

	cout << "\n" << endl;

	// Show() tests
	for (int i = 0; i < 5; i++)
	{
		ptr[i]->Show();
		cout << endl;
	}

	for (int j = 0; j < 5; j++)
	{
		delete ptr[j];
		ptr[j] = nullptr;
	}
	// End Show() tests

	return 0;
}
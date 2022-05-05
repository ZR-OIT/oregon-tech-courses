#pragma once
#ifndef CSETSTUDENT_H
# define CSETSTUDENT_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Student.h"

class CSETStudent : public Student
{
public:
	CSETStudent(void);
	CSETStudent(const int age, const char * fname, const char * lname, const float gpa, 
		const char *major, const int energyDrinks, const char *favGame, const char *advisor);
	CSETStudent(const CSETStudent &csetStud);
	CSETStudent &operator=(const CSETStudent &csetStud);
	~CSETStudent();

	void Display(void) const;
	void Show(void) const;

	friend ostream & operator << (ostream &os, const CSETStudent &csetStud);

private:
	int m_energyDrinks;
	char *m_favGame;
	char *m_advisor;
};

#endif // CSETSTUDENT_H
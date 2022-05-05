#pragma once
#ifndef CSETTA_H
# define CSETTA_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "CSETStudent.h"
#include "CSETProfessor.h"

class CSETTa : public CSETStudent, public Teacher
{
public:
	CSETTa(void);
	CSETTa(const int age, const char * fname, const char * lname, const float gpa,
		const char *major, const int energyDrinks, const char *favGame,
		const char *advisor, const int years, const char *title, const char *taClass, const unsigned hours);
	CSETTa(const CSETTa &csetTa);
	CSETTa &operator=(const CSETTa &csetTa);
	virtual ~CSETTa();

	void Display(void) const;
	void Show(void) const;

	friend ostream & operator << (ostream &os, const CSETTa &csetTa);

private:
	char *m_class;
	unsigned m_hoursPerWeek;
};

#endif // CSETTA_H

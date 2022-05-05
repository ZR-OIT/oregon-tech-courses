#pragma once
#ifndef CSETPROFESSOR_H
# define CSETPROFESSOR_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Teacher.h"

class CSETProfessor : public Teacher
{
public:
	CSETProfessor(void);
	CSETProfessor(const int age, const char * fname, const char * lname, const int years,
		const char *title, const char * office, const bool beard);
	CSETProfessor(const CSETProfessor &csetProf);
	CSETProfessor &operator=(const CSETProfessor &csetProf);
	virtual ~CSETProfessor();

	void Display(void) const;
	void Show(void) const;

	friend ostream & operator << (ostream &os, const CSETProfessor &csetProf);

private:
	char *m_office;
	bool m_hasBeard;
};

#endif // CSETPROFESSOR_H

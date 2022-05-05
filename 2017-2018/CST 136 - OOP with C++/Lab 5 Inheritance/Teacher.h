#pragma once
#ifndef TEACHER_H
# define TEACHER_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Person.h"

class Teacher : virtual public Person
{
public:
	Teacher(void);
	Teacher(const int age, const char * fname, const char * lname, const int years, const char *title);
	Teacher(const Teacher &teacher);

	Teacher &operator=(const Teacher &teacher);

	void Display(void) const;
	virtual void Show(void) const;

	void Promote(const char *title);

	~Teacher();

	friend ostream & operator << (ostream &os, const Teacher &teacher);

protected: // derived class can access directly
	int m_protected_teacher;

private:
	int m_years;
	int m_id;
	char *m_title;

	static int m_next_id;
};

#endif // TEACHER_H

#pragma once

#ifndef STUDENT_H
# define STUDENT_H

# define _CRT_SECURE_NO_WARNINGS
# include <iostream>

# include "Person.h"

class Student : virtual public Person
{
public:
	Student(void);
	Student(const int age, const char * fname, const char * lname, const float gpa, const char *major);
	Student(const Student &student);

	Student &operator=(const Student &student);
	~Student(void);
	friend ostream & operator << (ostream &os, const Student &student);

	//virtual 
	void Display(void) const;
	virtual void Show(void) const;

protected: // derived class can access
	int m_protected_student;

private:
	int m_id;
	float m_gpa;
	char *m_major;

	static int m_next_id;
};

#endif // STUDENT_H

#pragma once

#ifndef PERSON_H
# define PERSON_H
# define _CRT_SECURE_NO_WARNINGS

# include <iostream>
using std::ostream;

class Person
{
public:
	Person(void);
	Person(const int age, const char * fname, const char * lname);
	Person(const Person &person);

	Person &operator=(const Person &person);

	virtual 
		~Person(void);

	int GetAge(void);
	void SetAge(const int age);

	friend ostream & operator << (ostream &os, const Person &person);

	void Display(void) const;

	virtual void Show(void) const =0;
	
protected: // derived class can access directly
	int m_protected_person;

private: // derived class cannot access directly
	int m_age;
	char *m_fname;
	char *m_lname;
};

#endif // PERSON_H
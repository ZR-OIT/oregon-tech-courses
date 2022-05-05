#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

#ifndef PERSON_H
# define PERSON_H

class Person
{
public:
	Person();
	Person(const char * name);
	Person(const Person& person);
	Person& operator=(const Person& person);
	void Display() const;
	const char * GetName() const;
	~Person();

	friend ostream& operator << (ostream& os, const Person &person);

private:
	char m_name[10];
};

#endif // PERSON_H

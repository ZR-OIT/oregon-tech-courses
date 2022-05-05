#include "Person.h"

Person::Person()
{
	m_name[0] = '\0';
}

Person::Person(const char * name)
{
	strcpy(m_name, name);
}

Person::Person(const Person & person)
{
	if (person.m_name == nullptr)
	{
		m_name[0] = '\0';
	}
	else
	{
		strcpy(m_name, person.m_name);
	}
}

Person & Person::operator=(const Person & person)
{
	if (this != &person)
	{
		strcpy(m_name, person.m_name);
	}
	return *this;
}

void Person::Display() const
{
	cout << "The Person's name is: " << m_name << endl;
}

const char * Person::GetName() const
{
	return m_name;
}

Person::~Person()
{
}

ostream & operator<<(ostream & os, const Person &person)
{
	os << person.GetName();
	return os;
}

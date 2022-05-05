#include "Cube.h"

Cube::Cube(void) : m_side(0)
{
	cout << "In Cube no arg ctor" << endl;
}

Cube::Cube(int side) : m_side(side)
{
	cout << "in Cube 1 arg ctor" << endl;
}

Cube::Cube(const Cube & c) : m_side(c.m_side)
{
	cout << "In Cube copy ctor" << endl;
}

Cube & Cube::operator=(const Cube & c)
{
	cout << "In Cube op=" << endl;
	if (this != &c)
	{
		m_side = c.m_side;
	}
	return *this;
}

void Cube::Display(void)
{
	cout << "** Cube: The size of the side is: " << m_side << endl;
}

int Cube::GetSide(void)
{
	return m_side;
}

void Cube::SetSide(int new_side)
{
	m_side = new_side;
}

Cube::~Cube(void)
{
	cout << "in Cube dtor: " << m_side << endl;
}

ostream & operator<<(ostream & os, const Cube &cube)
{
	os << cube.m_side;
	return os;
}

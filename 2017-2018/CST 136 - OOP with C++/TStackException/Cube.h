#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

#ifndef CUBE_H
# define CUBE_H

class Cube
{
public:
	Cube(void);
	Cube(int side);
	Cube(const Cube & c);
	Cube& operator=(const Cube & c);

	void Display(void);
	int GetSide(void);
	void SetSide(int new_side);

	~Cube(void);

	friend ostream& operator << (ostream& os, const Cube &cube);

private:
	int m_side;
};

#endif // CUBE_H

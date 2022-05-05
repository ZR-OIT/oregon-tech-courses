/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise12-5-1.cpp
* Date Created: 1/11/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 Exercise 12.5.1
*
* Overview: Convert the program shown in Example 9.6.1 so that only passing by value and passing by pointer is used.
*
* Input: Data given by the textbook.
*
* Output: Either an address or a value of an element in an array.
*
*****************************************************************************************************/

// Chapter 9 - Section 9.6
// Filename:	Example9_6_1
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

int Fun1(int & a, int & b);
void Fun2(int & a, int & b);
void Fun3(int * c, int * d);
void PrintOutput(int * a, int * b);

int main()
{
	int a = 2, b = 10;

	PrintOutput(&a, &b);

	a = Fun1(a, b);

	cout << a << "\t" << b << endl;

	Fun2(a, b);
	PrintOutput(&a, &b);

	return 0;
}

// PrintOutput
void PrintOutput(int * a, int * b)
{
	cout << *a << "\t" << *b << endl;
}

// Fun1
int Fun1(int & a, int & b)
{
	int c;

	c = a + b;
	a++;
	--b;

	cout << a << "\t" << b << "\t" << c << endl;

	return c;
}

// Fun2
void Fun2(int & a, int & b)
{
	a += 5;
	double temp = pow(static_cast<double>(a), 2);
	b = static_cast<int>(temp);

	PrintOutput(&a, &b);
	Fun3(&a, &b);
	PrintOutput(&a, &b);
}

// Fun3
void Fun3(int * c, int * d)
{
	*c = 25;
	*d = 10;

	PrintOutput(c, d);
}
// Output
//2       10
//3       9       12
//12      10
//17      289
//25      10
//25      10
//25      10
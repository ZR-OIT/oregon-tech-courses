/****************************************************************************************************
* Author: Zak Rowland
* Filename: Recursion.cpp
* Date Created: 2/8/2018
* Modifications:
*****************************************************************************************************
* Assignment: Recursive functions
*
* Overview: (1) Write 2 functions powR(m, n) and powI(m, n) functions as C++ that compute the
*				value of m^n.
*			(2) Implement a recursive function in C++ to perform the cString function for strlen().
*			(3) Write a recursive function called FibonacciR() that takes a single parameter and
*				returns the value Fn, where Fn is defined from the definition of the Fibonacci. 
*				In addition, write an iterative function that also calculates the give Fibonacci value,
*				but it uses loops (while or for) to calculate the value. You should call it FibonacciI().
*
* Input: 
*
* Output:
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

unsigned long PowR(int m, int n);
unsigned long PowI(int m, int n);
size_t StrlenR(char *str);
unsigned long FibonacciR(unsigned long n);
unsigned long FibonacciI(unsigned long n);

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{
	int base = 5;
	int exponent = 2;
	char string[20] = "RECURSION-CEPTION!";
	char string2[40] = "There are 39 characters in this string!";
	unsigned long fib = 40;

	cout << base << " to the power of " << exponent << " using recursion = " << PowR(base, exponent) << endl;
	cout << base << " to the power of " << exponent << " using iteration = " << PowI(base, exponent) << endl;

	cout << "\nThe length of \"" << string << "\" using recursion = " << StrlenR(string) << endl;
	cout << "The length of \"" << string2 << "\" using recursion = " << StrlenR(string2) << endl;

	cout << "\nFibonacci of " << fib << " using recursion = " << FibonacciR(fib) << endl;
	cout << "Fibonacci of " << fib << " using iteration = " << FibonacciI(fib) << "\n" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: PowR
* Purpose: Calculates m to the power of n using recursion
*****************************************************************************************************/
unsigned long PowR(int m, int n)
{
	if (n == 0)
		return 1;
	else
		return (m * PowR(m, n - 1));
}
/*****************************************************************************************************
* Function: PowI
* Purpose: Calculates m to the power of n using iteration
*****************************************************************************************************/
unsigned long PowI(int m, int n)
{
	unsigned long product = 1;

	for (int i = 1; i <= n; i++)
		product = product * m;
	return product;
}
/*****************************************************************************************************
* Function: StrlenR
* Purpose: Calculates the length of a string using recursion
*****************************************************************************************************/
size_t StrlenR(char *str)
{
	size_t counter = 0;

	if (*str == '\0')
		return 0;
	else
	{
		str++;
		return (StrlenR(str) + 1);
	}
}
/*****************************************************************************************************
* Function: FibonacciR
* Purpose: Calculates Fibonacci number using recursion
*****************************************************************************************************/
unsigned long FibonacciR(unsigned long n)
{
	if (n <= 1)
		return n;
	return FibonacciR(n - 1) + FibonacciR(n - 2);
}
/*****************************************************************************************************
* Function: FibonacciI
* Purpose: Calculates 
*****************************************************************************************************/
unsigned long FibonacciI(unsigned long n)
{
	int total = 0;
	int start1 = 0;
	int start2 = 1;

	for (int i = 1; i < static_cast<int>(n); i++)
	{
		total = start1 + start2;
		start1 = start2;
		start2 = total;
	}

	return total;
}
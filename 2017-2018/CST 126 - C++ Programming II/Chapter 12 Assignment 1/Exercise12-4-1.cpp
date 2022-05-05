/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise12-4-1.cpp
* Date Created: 1/11/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 Exercise 12.4.1 
*
* Overview: Use pointers to access different elements in the array.
*
* Input: Array given by the textbook.
*
* Output: Either the address or the value of an element in an array.
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Contains a list of solutions (statements) for the problems givin in 12.4.
*****************************************************************************************************/
int main()
{
	int numbers[5] = { 99, 34, 1, 88, 100};
	int * int_ptr = numbers;
	int ** int_ptr_ptr = &int_ptr;

	//a.
	cout << "a: " << &numbers << endl;
	//b.
	cout << "b: " << int_ptr << endl;
	//c.
	cout << "c: " << *int_ptr_ptr << endl;
	//d.
	cout << "d: " << &int_ptr << endl;
	//e.
	cout << "e: " << int_ptr_ptr << endl;
	//f.
	cout << "f: " << *int_ptr << endl;
	//g.
	cout << "g: " << **int_ptr_ptr << endl;
	//h.
	int_ptr++;
	//i.
	cout << "i: " << *int_ptr << endl;
	//j.
	cout << "j: " << **int_ptr_ptr << endl;
	//k.
	*int_ptr = 101;
	cout << "k: " << *int_ptr << endl;
	//l.
	**int_ptr_ptr = 102;
	cout << "l: " << **int_ptr_ptr << endl;
	//m.
	(*int_ptr_ptr)++;
	cout << "m: " << **int_ptr_ptr << endl;
	//n.
	*int_ptr = -1;
	cout << "n: " << *int_ptr << endl;
	//o.
	**int_ptr_ptr = -2;
	cout << "o: " << **int_ptr_ptr << endl;
	//p.
	cout << "\np: ";
	
	for (int ii = 0; ii < 5; ii++)
	{
		cout << numbers[ii] << ' ';
	}
	
	cout << "\n" << endl;

	return 0;
}

/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/29/2017
* Assignment: Section 12.4 check off
*****************************************************************************************************
* Input: n/a
*
* Processing: n/a
*
* Output: n/a
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Prints and/or manipulates multiple pointer statements
*****************************************************************************************************/
int main()
{
	int numbers[5] = { 99,34,1,88,100 };
	int * int_ptr = numbers;
	int ** int_ptr_ptr = &int_ptr;

	//A. Write the statement that prints the address of the array using the array name.
	cout << "The address of the array using array name is: " << &numbers << endl;

	//B. Write the statement that prints the address of the array using int_ptr.
	cout << "The address of the array using int_ptr is: " << int_ptr << endl;

	//C. Write the statement that prints the address of the array using int_ptr_ptr.
	cout << "The address of the array using int_ptr_ptr is: " << *int_ptr_ptr << endl;

	//D. Write the statement that prints the address of the int_ptr using int_ptr.
	cout << "\nThe address of int_ptr using int_ptr is: " << &int_ptr << endl;

	//E. Write the statement that prints the address of the int_ptr using int_ptr_ptr.
	cout << "The address of int_ptr using int_ptr_ptr is: " << int_ptr_ptr << endl;

	//E. Write the statement that prints the address of the int_ptr using int_ptr_ptr.
	cout << "The address of int_ptr using int_ptr_ptr is: " << int_ptr_ptr << endl;

	//F. Write the statement that prints the first element of the array using int_ptr.
	cout << "\nThe first element of the array using int_ptr is: " << *int_ptr << endl;

	//G. Write the statement that prints the first element of the array using int_ptr_ptr.
	cout << "The first element of the array using int_ptr_ptr is: " << **int_ptr_ptr << endl;

	//H. Write the statement that changes int_ptr to point to the second element of the array.
	*int_ptr++;

	//I. Write the statement that prints the second element of the array using int_ptr.
	cout << "\nThe second element of the array using int_ptr is: " << *int_ptr << endl;

	//J. Write the statement that prints the second element of the array using int_ptr_ptr.
	cout << "The second element of the array using int_ptr_ptr is: " << **int_ptr_ptr << endl;

	//K. Write the statement that changes the second element of the array to 101 using int_ptr.
	*int_ptr = 101;

	//L. Write the statement that changes the second element of the array to 102 using int_ptr_ptr.
	**int_ptr_ptr = 102;

	//M. Change the address in int_ptr so that it points to the third element of the array using int_ptr_ptr.
	(*int_ptr_ptr)++; 

	//N. Write the statement that changes the third element of the array to -1 using int_ptr.
	*int_ptr = -1;

	//O. Write the statement that changes the third element of the array to -2 using int_ptr_ptr.
	**int_ptr_ptr = -2;

	//P. Print the contents of the array to the screen to verify the contents of the array were changed.
	cout << "\nThe changed array is: ";
	for (int ii = 0; ii < 5; ii++)
	{
		cout << numbers[ii] << " ";
	}
	cout << "\n" << endl;
	return 0;
}

/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise12-6-1.cpp
* Date Created: 1/11/2018
* Modifications:
*****************************************************************************************************
* Assignment: Chapter 12 Exercise 12.6.1
*
* Overview: Display the contents of the array using a pointer.
*
* Input: A 2D array of integers with four rows and five columns.
*
* Output: A list on numbers from the 2D array.
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Contains a 2D array and prints the contents using a pointer.
*****************************************************************************************************/
int main()
{
	int numbers[4][5] = { {1,2,3,4,5},
						  {6,7,8,9,10},
						  {11,12,13,14,15},
						  {16,17,18,19,20} };
	
	int * num_ptr = *numbers;

	for (int ii = 0; ii < 20; ii++)
	{
		cout << *num_ptr << " ";
		num_ptr++;
	}
	 
	cout << "\n" << endl;

	return 0;
}
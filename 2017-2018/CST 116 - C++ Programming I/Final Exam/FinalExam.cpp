/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 12/4/2017
* Assignment: Final Exam
*****************************************************************************************************
* Input: An array of integers.
*
* Processing: Compare all integers to find the largest.
*
* Output: The largest integer.
*
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int ReturnLargest(int data[], int &largestNumber, int MAX_SIZE);
void ArrayValues(int data[], int MAX_SIZE);

/*****************************************************************************************************
* Function: main
* Purpose: Declare and initialize an array, call the ReturnLargest function, print the result.
*****************************************************************************************************/
int main()
{
	const int MAX_SIZE = 10;
	int data[MAX_SIZE];
	
	ArrayValues(data, MAX_SIZE);
	
	int largestNumber = ReturnLargest(data, largestNumber, MAX_SIZE);
	
	cout << "\nZachery Rowland says: \n" << "The largest number is: " << largestNumber << "\n" << endl;

	return 0;
}

/*****************************************************************************************************
* Function: ReturnLargest
* Purpose: Compares all values of an array to see which one is largest.
*****************************************************************************************************/
int ReturnLargest(int data[], int &largestNumber, int MAX_SIZE)
{
	for (int ii = 0; ii < MAX_SIZE; ii++) 
	{
		if (data[ii] > data[ii + 1] && data[ii] > largestNumber) //compares values of the array
		{
			largestNumber = data[ii];
		}
	}
	return largestNumber;
}

/*****************************************************************************************************
* Function: ArrayValues
* Purpose: Takes user input values and stores them into an array.
*****************************************************************************************************/

void ArrayValues(int data[], int MAX_SIZE)
{
	int count = 0;

	cout << "Fill in the array with values: \n" << endl;

	while (count < MAX_SIZE)
	{
		cout << "Enter an integer: ";
		cin >> data[count];
		count++;
	}
}
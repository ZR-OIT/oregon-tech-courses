/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/3/2017
* Assignment: Midterm Exam
*****************************************************************************************************
* Input: Two integer values
*
*
* Processing: if a > b: print b, then add 2 to b and print until it the value of b reaches a 
*             if b > a: print a, then add 2 to a and print until it the value of a reaches b 
*
* Output: a a+2 a+2 ...
*         or
*         b b+2 b+2 ...
*****************************************************************************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void ValueIterations(int a, int b);
void IntegerInput(int &a, int &b);

/*****************************************************************************************************
* Function: main
* Purpose: Calls the IntegerInput function and uses those values in the ValueIterations function
*****************************************************************************************************/
int main()
{
	int a = 0;
	int b = 0;

	IntegerInput(a, b);
	ValueIterations(a, b);
	
	IntegerInput(a, b); // Added this pair to allow the program to be tested more than once at a time.
	ValueIterations(a, b);
	
	return 0;
}

/*****************************************************************************************************
* Function: ValueIterations
* Purpose: Prints a number incremented by two while it is less than or equal to the bigger number.
*****************************************************************************************************/
void ValueIterations(int valueOne, int valueTwo)
{
	if (valueTwo < valueOne)
		while (valueTwo <= valueOne)
		{
			cout << valueTwo << " ";
			valueTwo = valueTwo + 2;
		}
	else if (valueOne < valueTwo)
		while (valueOne <= valueTwo)
		{
			cout << valueOne << " ";
			valueOne = valueOne + 2;
		}
}

/*****************************************************************************************************
* Function: IntegerInput
* Purpose: Reads integer values from the user and passes them back to main().
*****************************************************************************************************/
void IntegerInput(int &a, int &b)
{
	cout << "\n----------------------------------------------------\n";
	cout << "\nPlease enter two integer values: \n\n" << "First value: ";
	cin >> a;
	cout << "\nSecond value: ";
	cin >> b;
	cout << "\n----------------------------------------------------\n";
}

/**********************************************************************
* This is the code for my original main function in the medium problem, 
* the hard problem was been completed above.
*
* cout << "Please enter two integer values: \n\n" << "First value: ";
* cin >> a;
* cout << "\nSecond value: ";
* cin >> b;
* cout << "\n----------------------------------------------------\n";
*
* ValueIterations(a, b);
* cout << "\n----------------------------------------------------\n\n";
*
* cout << "Please enter two integer values: \n\n" << "First value: ";
* cin >> a;
* cout << "\nSecond value: ";
* cin >> b;
* cout << "\n----------------------------------------------------\n";
* ValueIterations(a, b);
* cout << "\n----------------------------------------------------\n\n";
************************************************************************/
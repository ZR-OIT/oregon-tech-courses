/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 10/23/2017
* Assignment: Intro to Functions
*****************************************************************************************************
* Do this all in the same file:
*
* (1) A function that returns the largest of three doubles
* (2) A function that returns the value obtained by multiplying the two integer parameters together
* (3) A main() that calls your two functions in ways to demonstrate that they work
*
* Process:
*
* What should the return type be ?
* What should the name be ?
* How many parameters ?
* What type should the parameters be ?
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: largest_Value
* Purpose: Returns the largest of three user inputted values
*****************************************************************************************************/
double largest_Value(double x, double y, double z)
{
	if ((x > y && x > z) || (x == y && x > z) || (x == z && x > y))
		return x;
	else if ((y > x && y > z) || (y == x && y > z) || (y == z && y > x))
		return y;
	else if ((z > x && z > y) || (z == x && z > y) || (z == y && z > x))
		return z;
	else
		return x;
}
/*****************************************************************************************************
* Function: pair_Product
* Purpose: Returns the product of two user inputted values
*****************************************************************************************************/
int pair_Product(int productValue1,int productValue2)
{
	int product = productValue1*productValue2;
	return product;
}
/*****************************************************************************************************
* Function: main
* Purpose: Prints a menu, reads three values from the user, and returns the value of the menu choice
			by calling other functions.
*****************************************************************************************************/
int main()
{
	int menuChoice;
	double valueOne, valueTwo, valueThree;

	cout << "Menu:\n"
		<< "(1) Find the largest of three values.\n"
		<< "(2) Find the product of Value 1 and Value 2.\n"
		<< "(3) Find the product of Value 2 and Value 3.\n"
		<< "(4) Find the product of Value 1 and Value 3.\n\n";

	cout << "Please enter three values: \n\nValue 1: ";
	cin >> valueOne;
	cout << "\nValue 2: ";
	cin >> valueTwo;
	cout << "\nValue 3: ";
	cin >> valueThree;
	cout << "\n";

	double largestValue = largest_Value(valueOne, valueTwo, valueThree);
	int pairProduct1 = (pair_Product(valueOne, valueTwo));
	int pairProduct2 = (pair_Product(valueTwo, valueThree));
	int pairProduct3 = pair_Product(valueOne, valueThree);

	cout << "Please enter a menu choice: ";
	cin >> menuChoice;
	cout << "\n";

	switch (menuChoice)
	{
	case 1:
		cout << "The largest value is: " << largestValue << endl;
		break;
	case 2:
		cout << "The product is: " << pairProduct1 << endl;
		break;
	case 3:
		cout << "The product is: " << pairProduct2 << endl;
		break;
	case 4:
		cout << "The product is: " << pairProduct3 << endl;
		break;
	default:
		cout << "Please select a valid menu choice." << endl;
	}
	return 0;
}
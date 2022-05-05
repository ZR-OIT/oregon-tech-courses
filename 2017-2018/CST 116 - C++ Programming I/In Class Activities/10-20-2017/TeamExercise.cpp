/*************************************************************
* Author:		 Zak Rowland
* Filename:	     Team Exercise 8.11.sln
* Date Created:	 10/20/17
* Modifications: N/A
***************************************************************
*
* Lab/Assignment: Team Exercise 8.11 on page 231
*
* Design:
*
* Menu choice one (number is odd, even, or zero)
* Input: Number from user (integer)
* Processing: If the number / 2 leaves a remainder, print odd
*             If the number / 2 leaves no remainder, print even
*             If the number = 0, print zero
* Output: Odd, even, or zero
*
* Menu choice two (number is positive, negative, or zero)
* Input: Number from user (integer)
* Processing: If the number is > 0, print positive
*             If the number is < 0, print negative
*             If the number = 0, print 0
* Output: Postive, negative, or zero
*
* Menu choice three (square root of number)
* Input: Number from user (integer)
* Processing: If the number > 0, print square root of number
*             If the number < 0, print "That's an imaginary number!"
*             If the number = 0, print 0.
* Output: Square root, "Imaginary!", zero.
* 
* Menu choice four (amount of digits in number)
* Input: Number from user (integer)
* Processing: Divide number by 10 keeping track of number of divisions
* Output: Number of divisions
*
* Menu choice five (digit at specific position in number)
* Input: Number from user (integer)
*        Which digit in the number (integer)
* Processing: Divide number by 10 (number of times based on which digit user wants)  
* Output: Digit at specific position in number
*
* Menu choice six (addition table for all numbers 0-12)
* Input: None
* Processing: None
* Output: Table
*
* Menu choice seven (multiplication table for all numbers 0-12)
* Input: None
* Processing: None
* Output: None
*
* Menu choice eight (exit program)
* Input: None
* Processing: None
* Output: The program will close
*
* Includes a loop which allows multiple menu options to be chosen for the users entered number (until the user chooses to exit.)
*
************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::right;

int main()
{
	int menu_choice;
	int number;

	cout << "\n1) Is the number odd or even?\n"
		<< "2) Is the number positive or negative?\n"
		<< "3) What is the square root of the number?\n"
		<< "4) How many digits are in the number?\n"
		<< "5) What is the digit at a specific position in the number?\n"
		<< "6) Display an addition table for all numbers 0-12.\n"
		<< "7) Display a multiplication table for all numbers 0-12.\n"
		<< "8) Exit the program.\n\n";

	cout << "Enter number: ";
	cin >> number;

	cout << "Enter a menu choice: ";
	cin >> menu_choice;
	cout << "\n";

	while (menu_choice != 8)
	{
		switch (menu_choice)
		{
		case 1:
			if (number % 2 != 0)
				cout << "\nThat number is odd.\n" << endl;
			else if (number % 2 == 0)
				cout << "\nThat number is even.\n" << endl;
			else
				cout << "\nZero is neither even nor odd.\n" << endl;
			break;
		case 2:
			if (number > 0)
				cout << "\nThat number is positive.\n" << endl;
			else if (number < 0)
				cout << "\nThat number is negative.\n" << endl;
			else
				cout << "\nZero is neither positive nor negative.\n" << endl;
			break;
		case 3:
			if (number > 0)
				cout << "\nThe square root of " << number << " is " << sqrt(number) << "\n" << endl;
			else if (number < 0)
				cout << "\nSquare roots of negative numbers are imaginary!\n" << endl;
			else
				cout << "\nThe square root of zero is zero.\n" << endl;
			break;
		case 4: // number of digits
			if (number == 0)
				cout << "The amount of digits in your number is: 1" << "\n\n" << endl;
			else if (number > 0)
			{
				int digits = 0;
				while (number != 0)
				{
					number /= 10;
					digits++;
				}
				cout << "The amount of digits in your number is: " << digits << "\n\n" << endl;
				break;
			}
			else
			{
				number *= -1;
				int digits = 0;
				while (number != 0)
				{
					number /= 10;
					digits++;
				}
				cout << "The amount of digits in your number is: " << digits << "\n\n" << endl;
			}
				break; 
		case 5: // digit at position ???????????
			if (number == 0)
				cout << "The digit will always be 0." << "\n \n" << endl;
			else if (number > 0)
			{
				int digit;

				cout << "Which position would you like to know value of?\n"
					<< "Example: In the number 943,019, 3 is in the (4)th place.\n"
					<< "Position: ";

				cin >> digit;

				if (digit == 1)
				{
					int result = number % 10;
					cout << "The digit is: " << result << "\n\n" << endl;
					break;
				}

				for (digit; digit > 1; digit--)
				{
					number = number / 10;
				}
				int result = number % 10;
				
				cout << "The digit is: " << result << "\n\n" << endl;
				break;
			}
			else
			{
				number *= -1;
				int digit;

				cout << "Which position would you like to know value of?\n"
					<< "Example: In the number 943,019, 3 is in the (4)th place.\n"
					<< "Position: ";

				cin >> digit;

				if (digit == 1)
				{
					int result = number % 10;
					cout << "The digit is: " << result << "\n\n" << endl;
					break;
				}

				for (digit; digit > 1; digit--)
				{
					number = number / 10;
				}
				int result = number % 10;

				cout << "The digit is: " << result << "\n\n" << endl;
				break;
			}
		case 6: // 0-12 addition table
			for (int addRow = 0; addRow <= 12; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 1; addRow <= 13; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 2; addRow <= 14; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 3; addRow <= 15; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 4; addRow <= 16; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 5; addRow <= 17; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 6; addRow <= 18; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 7; addRow <= 19; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 8; addRow <= 20; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 9; addRow <= 21; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 10; addRow <= 22; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 11; addRow <= 23; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n";
			for (int addRow = 12; addRow <= 24; addRow = addRow + 1)
				cout << setw(2) << right << addRow << " ";
			cout << "\n" << endl;
			break;
		case 7: // 0-12 multiplication table
			for (int row = 0; row < 13; row++)
			{
				for (int col = 0; col < 13; col++)
				{
					cout << row*col;
				}
				cout << endl;

			}
			for (int proRow = 0; proRow <= 12; proRow = proRow + 1)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "1" << " ";
			for (int proRow = 1; proRow <= 12; proRow = proRow + 1)
				cout << setw(3) << right << proRow << " ";
			
			cout << "\n\n" << setw(3) << right << "2" << " ";
			for (int proRow = 2; proRow <= 24; proRow = proRow + 2)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "3" << " ";
			for (int proRow = 3; proRow <= 36; proRow = proRow + 3)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "4" << " ";
			for (int proRow = 4; proRow <= 48; proRow = proRow + 4)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "5" << " ";
			for (int proRow = 5; proRow <= 60; proRow = proRow + 5)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "6" << " ";
			for (int proRow = 6; proRow <= 72; proRow = proRow + 6)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "7" << " ";
			for (int proRow = 7; proRow <= 84; proRow = proRow + 7)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "8" << " ";
			for (int proRow = 8; proRow <= 96; proRow = proRow + 8)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "9" << " ";
			for (int proRow = 9; proRow <= 108; proRow = proRow + 9)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "10" << " ";
			for (int proRow = 10; proRow <= 120; proRow = proRow + 10)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "11" << " ";
			for (int proRow = 11; proRow <= 132; proRow = proRow + 11)
				cout << setw(3) << right << proRow << " ";
			cout << "\n\n" << setw(3) << right << "12" << " ";
			for (int proRow = 12; proRow <= 144; proRow = proRow + 12)
				cout << setw(3) << right << proRow << " ";
			cout << "\n" << endl;
			break;
		default:
			cout << "\nPlease enter a valid menu selection!\n\n" << endl;
			break;
		}
		cout << "Enter number: ";
		cin >> number;
		cout << "Enter a menu choice: ";
		cin >> menu_choice;
		cout << "\n";
	}
	return 0;
}
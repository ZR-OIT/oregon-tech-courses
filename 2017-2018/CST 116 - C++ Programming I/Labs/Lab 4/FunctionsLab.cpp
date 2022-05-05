/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 10/30/2017
* Assignment: Lab 4 (Functions)
*****************************************************************************************************
* Input: An integer age, birth month, and birth day from the user.
*
* Processing: Continutes to loop until user inputs acceptable values. 
*             Calculates the date of a 21st birthday by subtracting age from 2017.
*
* Output: A 21st birthday date.
*
*****************************************************************************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void InfoFromUser(int &age, int &birthMonth,int &birthDay);
void LegalAge(int age, int birthMonth, int birthDay);

/*****************************************************************************************************
* Function: main
* Purpose: Calls the InfoFromUser and LegalAge functions.
*****************************************************************************************************/
int main()
{
	int age;
	int birthMonth;
	int birthDay;

	InfoFromUser(age,birthMonth,birthDay);
	LegalAge(age,birthMonth,birthDay);

	return 0;
}

/*****************************************************************************************************
* Function: PromptForInteger
* Purpose: Reads input from user for values age, birthMonth, and birthDay. Continues to loop until user
*			inputs acceptable values.
*****************************************************************************************************/

int PromptForInteger(const char *prompt, int lowerLimit, int upperLimit)
{
	int age, birthMonth, birthDay;

	if (upperLimit == 100)
	{
		cout << prompt;
		cin >> age;
		while ((age < lowerLimit) || (age > upperLimit))
		{
			cout << "Please enter an age between 0 and 100: ";
			cin >> age;
		}
		return age;
	}
	if (upperLimit == 12)
	{
		cout << prompt;
		cin >> birthMonth;
		while ((birthMonth < lowerLimit) || (birthMonth > upperLimit))
		{
			cout << "Please enter a birth month between 1 and 12: ";
			cin >> birthMonth;
		}
		return birthMonth;
	}
	if (upperLimit == 31)
	{
		cout << prompt;
		cin >> birthDay;
		while ((birthDay < lowerLimit) || (birthDay > upperLimit))
		{
			cout << "Please enter a birth day between 1 and 31: ";
			cin >> birthDay;
		}
		return birthDay;
	}
	return 0;
}

/*****************************************************************************************************
* Function: InfoFromUser
* Purpose: Calls the PromptForInteger function and stores the values.
*****************************************************************************************************/

void InfoFromUser(int &age, int &birthMonth, int &birthDay)
{
	age = PromptForInteger("Enter age (between 0 and 100): ", 0, 100);
	birthMonth = PromptForInteger("Enter birth month: ", 1, 12);
	birthDay = PromptForInteger("Enter birth day: ", 1, 31);
}

/*****************************************************************************************************
* Function: LegalAge
* Purpose: Uses values from the InfoFromUser function to calculate the date of a 21st birthday.
*****************************************************************************************************/

void LegalAge(int age ,int birthMonth ,int birthDay)
{
	int newYear = ((2017 - age) + 21);
	cout << "Your 21st birthday is on " << birthMonth << "/" << birthDay << "/" << newYear << ".\n\n";
}

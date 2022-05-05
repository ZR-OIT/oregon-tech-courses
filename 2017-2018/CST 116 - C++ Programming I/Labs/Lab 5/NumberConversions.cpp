/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/8/2017
* Assignment: Number Conversions Lab (P. 352)
*****************************************************************************************************
* Input: Reads 3 numbers from the user: originalNumber, originalBase (2 - 36), and resultBase (2-36)
*
* Processing: - If user enters a base outside of range, display an error message and ask for another input.
*			  - If the number doesn't match the base typed in, display an error message and ask for all inputs again.
*             - Convert originalNumber to base 10 first, then to the desired base.
*
* Output: - Prints originalNumber(originalBase) = resultNumber(resultBase)
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <cctype>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

void FromBase(char *originalNumber, char *resultNumber, int originalBase, int resultBase);

/*****************************************************************************************************
* Function: main
* Purpose: reads 3 values from the user, ensures the values are valid, and calls the FromBase function
*****************************************************************************************************/
int main()
{
	const int MAX_NUMBER_SIZE = 25;
	const char ALPHABET[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

	char originalNumber[MAX_NUMBER_SIZE];
	char resultNumber[MAX_NUMBER_SIZE];
	int originalBase = 0;
	int resultBase = 0;
	int size = 0;
	bool valid;
	char maxValue;
	char maxAlpha;


	do
	{
		valid = true;

		cout << "Please enter any number with a base between 2-36: ";
		cin >> originalNumber; //stores user input number

		size = strlen(originalNumber); //stores the length of the number

		for (int hh = 0; hh < size; hh++) //converts any lowercase letters into uppercase letters
		{
			if ((originalNumber[hh] > 96) && (originalNumber[hh] < 123))
			{
				originalNumber[hh] = (originalNumber[hh] - 32);
			}
		}

		for (int ii = 0; (ii < size); ii++) //checks every value in the string for non-alphanumeric characters
		{
			if (!isalnum(originalNumber[ii]))
			{
				valid = false;
				strcpy(resultNumber, "error");
				cout << "That number isn't alphanumeric, try again.\n\n";
				break;
			}
		}

		if (valid == true)
		{
			cout << "\nPlease enter the base of your number: ";
			cin >> originalBase; //stores user input base of the number

			if ((originalBase >= 2) && (originalBase <= 10)) //determines if bases 2-10 match the original number
			{
				for (int jj = 0; (jj < size); jj++)
				{
					maxValue = (originalBase + 47);
					if ((originalNumber[jj]) > maxValue)
					{
						valid = false;
						cout << "Your number doesn't match your base, try again.\n\n";
						break;
					}
				}
			}
			else if ((originalBase > 10) && (originalBase <= 36)) //determines if bases 11-36 match the original number
				for (int kk = 0; (kk < size); kk++)
				{
					if (isalpha(originalNumber[kk]))
					{
						maxAlpha = ALPHABET[(originalBase - 11)];

						if (originalNumber[kk] > maxAlpha)
						{
							valid = false;
							cout << "Your number doesn't match your base, try again.\n\n";
							break;
						}
					}
				}
			else //if the base is outside range
			{
				valid = false;
				cout << "That isn't a valid base, try again.\n\n";
			}
		}

		if (valid == true)
		{
			cout << "\nPlease enter the base to convert to (2-36): ";
			cin >> resultBase; //stores user input desired base of the number

			while ((resultBase < 2) || (resultBase > 36))
			{
				cout << "That isn't a valid base, try again.\n" << "\nPlease enter the base to convert to (2-36): ";
				cin >> resultBase;
			}
		}
	} while (valid == false);

	FromBase(originalNumber, resultNumber, originalBase, resultBase);

	cout << originalNumber << " (base " << originalBase << ") = " << resultNumber << " (base " << resultBase << ")\n" << endl;

	return 0;
}
/*****************************************************************************************************
* Function: FromBase
* Purpose: Converts a number of one base to another base
*****************************************************************************************************/
void FromBase(char *originalNumber, char *resultNumber, int originalBase, int resultBase)
{
	const int MAX_NUMBER_SIZE = 25;
	int quotient;
	int size = strlen(originalNumber); //stores the length of the number
	int characterValue;
	double convertedValue = 0;

	if (originalBase == 10)
		originalBase = convertedValue;
	else if (originalBase != 10)
	{
		for (int mm = 0; mm <= (size - 1); mm++)
		{
			if (isdigit(originalNumber[mm]))
				characterValue = ((originalNumber[mm]) - '0');
			else if (isalpha(originalNumber[mm]))                   
				characterValue = ((originalNumber[mm]) - 'A');
			
			convertedValue = convertedValue + (characterValue * pow(originalBase, ((size-1) - mm))); 
				// convertedValue is supposed to equal the originalNumber converted to base 10.
				// isalpha(originalNumber[mm]) - 'A' doesn't seem to work properly. (e.g. 'F' = 70 and 'A' = 65 so F-A != 16)
		}
	}
	
	for (int pp = (size - 1); pp >= 0; pp++)
	{
		if (pp == (size - 1))
		{
			quotient = convertedValue / resultBase;
			resultNumber[pp] = static_cast<int>(convertedValue) % resultBase;
		}
		//couldn't figure out how to set up the formula for converting to any base ...
		else
		{
			quotient = quotient / resultBase;
			resultNumber[pp] = quotient % resultBase;
		}
	}
}


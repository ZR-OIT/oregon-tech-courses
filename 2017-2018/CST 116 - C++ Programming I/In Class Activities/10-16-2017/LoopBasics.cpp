/*
Write a single program with three loops:

1) A for loop that prints the numbers 0..9. Each number should be on a separate line.

2) A while loop keeps prompting the user to enter a number until they enter a negative one.

3) A do-while loop that prints the characters from 'a' to 'c'. Each letter should be on a line by itselfe. For each character, use another loop to print the odd numbers from 11 down to 1. All the numbers should be on the same line.
*/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	// 1)
	int ii = 0;

	for (ii = 0; ii < 10; ii++)
	{
		cout << ii << endl;
	}
	// 2)
	int jj = 0;

	cout << "Please enter a value: \n";
	cin >> jj;

	while (jj > 0)
	{
		cout << "Please enter a value: \n";
		cin >> jj;
	}
	// 3)
	char kk = 'a';
		
	do
	{
		cout << kk << endl;

		for (int numVar = 11; numVar > 0;)
		{
			cout << numVar << " ";
			numVar= numVar-2;
		}
		cout << "\n";
		kk++;
	
	} while (kk < 'd');
	
	system("pause");
	return 0;
}
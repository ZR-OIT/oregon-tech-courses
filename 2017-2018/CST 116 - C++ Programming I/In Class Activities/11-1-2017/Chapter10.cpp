/****************************************************************************************************
* Author: Zak Rowland
* Date Created: 11/1/2017
* Assignment: P.294 Section 10.5
*****************************************************************************************************
* Input:  
*
*
* Processing:
*
*
* Output:
*
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{

	const int MAX_INPUTS = 10;
	float testScores[MAX_INPUTS];
	char testGrades[MAX_INPUTS];
	int countA = 0, countB = 0, countC = 0, countD = 0, countF = 0;

	for (int ii = 0; ii < MAX_INPUTS; ii++)
	{
		cout << "Enter a test score: ";
		cin >> testScores[ii];
		if (testScores[ii] >= 92.0)
			testGrades[ii] = 'A';
		else if (testScores[ii] >= 84.0)
			testGrades[ii] = 'B';
		else if (testScores[ii] >= 75.0)
			testGrades[ii] = 'C';
		else if (testScores[ii] >= 65.0)
			testGrades[ii] = 'D';
		else if (testScores[ii] < 65.0)
			testGrades[ii] = 'F';
		else
			cout << "That's not a valid number.";

		cout << "Score: " << testScores[ii] << "\nGrade: " << testGrades[ii] << "\n";
	}

	float classTotal = 0;
	for (int kk = 0; kk < MAX_INPUTS; kk++)
	{
		classTotal += testScores[kk];
	}
	float classAverage = classTotal / MAX_INPUTS;
	cout << "\nThe class average is: " << classAverage << "\n\n";

	for (int jj = 0; jj < MAX_INPUTS; jj++)
	{
		if (testGrades[jj] == 'A')
			countA++;
		else if (testGrades[jj] == 'B')
			countB++;
		else if (testGrades[jj] == 'C')
			countC++;
		else if (testGrades[jj] == 'D')
			countD++;
		else if (testGrades[jj] == 'F')
			countF++;
	}
	cout << "The number of As is: " << countA << "\nThe Number of Bs is: " << countB
		<< "\nThe number of Cs is: " << countC << "\nThe number of Ds is: " << countD
		<< "\nThe number of Fs is: " << countF << "\n";

		return 0;
}
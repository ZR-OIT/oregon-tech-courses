/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise12-9.cpp
* Date Created: 1/18/2018
* Modifications:
*****************************************************************************************************
* Assignment: Exercise 12.9
*
* Overview: Write a program that accepts from a professor the number of students in a class. Allocate
*			enough room to store final exam scores for all of the students. Allow the professor to
*			enter the final exam scores. Then iterate through all the scores, displaying them one per
*			line. Then, display the average, high, and low score for the class.
*			Display to the screen all of the scores and the average of the scores.
*
* Input:    Number of students and their test scores.
*
* Output:   The list of scores, the average score, the high and low scores. 
*
*****************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Recieves number of students and their test scores, then displays them.
*****************************************************************************************************/
int main()
{
	int students = 0;
	float total = 0;
	float average = 0;
	float largest = 0;
	float smallest = 0;

	cout << "How many students do you have?" << " : ";
	cin >> students;
	cout << endl;
	
	float * ptr = new float[students + 1];

	for (int ii = 0; ii < students; ii++)
	{
		cout << "Enter final score #" << ii + 1 << ": ";
		cin >> *ptr;
		ptr++;
	}
	
	cout << endl;

	ptr--;
	largest = *ptr;

	for (int jj = 0; jj < (students-1); jj++)
	{
		ptr--;
	}

	smallest = *ptr;

	for (int kk = 0; kk < students; kk++)
	{
		cout << "Score #" << kk + 1 << ": " << *ptr << endl;
		
		if (*ptr > largest)
			largest = *ptr;
		else if (*ptr < smallest)
			smallest = *ptr;

		total = total + *ptr;
		
		ptr++;
	}

	cout << endl;

	for (int jj = 0; jj < (students); jj++)
	{
		ptr--;
	}

	delete[] ptr;
	ptr = nullptr;

	average = (total / students);

	cout << "Average score: " << average << endl;
	cout << "Lowest score: " << smallest << endl;
	cout << "Highest score: " << largest << endl;
	cout << endl;

	return 0;
}

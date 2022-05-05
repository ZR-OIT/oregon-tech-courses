/****************************************************************************************************
* Author: Zak Rowland
* Filename: Exercise 13-9.cpp
* Date Created: 2/6/2018
* Modifications:
*****************************************************************************************************
* Assignment: Programming Exercise 13.9
*
* Overview: The objective for this assignment is to create a structure called Employee that
*			contains the fields identified (from 1), then implement the described capabilities
*			(calculations based on the input data), and display the neatly formatted output. Use an
*			array of structures to hold your data. Instead of having to pass all those parallel arrays
*			to the various functions, you can simply pass your array of structures.
*
* Input:	DataFile.txt
*
* Output:   A formatted table of information from the data file.
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;

const int NUM_EMPLOYEES = 25;
const int MAX_STRING = 20;
const int MAX_SSN = 12;

struct Employee
{
	char name[MAX_STRING];
	char ssn[MAX_SSN];
	float wage;
	int hours;
	char time;
	float straightPay;
	float overtimePay;
	float netPay;
};

void FullTime(Employee &data);
void PartTime(Employee &data);

/*****************************************************************************************************
* Function: main
* Purpose:
*****************************************************************************************************/
int main()
{
	const char *fileName = "DataFile.txt";
	char buffer[MAX_STRING];
	int count = 0;
	
	Employee information[NUM_EMPLOYEES];

	ifstream input(fileName);

	if (input.is_open())
	{
		while (!input.eof()) //stores data in structure
		{
			input >> information[count].name;
			input >> buffer;
			strcat(information[count].name, " ");
			strcat(information[count].name, buffer);

			input >> information[count].ssn >> information[count].wage
				>> information[count].hours >> information[count].time;
			
			count++;
		}
		input.close();
	}
	
	else
	{
		cout << "File failed to open." << endl;
	}

	for (int ii = 0; ii < count - 1; ii++) //calls either FullTime or PartTime depending on the data
	{
		if (information[ii].time == 'F')
		{
			FullTime(information[ii]);
		}
		else if (information[ii].time == 'P')
		{
			PartTime(information[ii]);
		}
	}

	cout << setw(20) << left << "Name" << " " << setw(MAX_SSN) << "SSN " //prints column information
		<< " " << setw(6) << left << "Wage" << " " << setw(6) << "Hours"
		<< " " << setw(10) << "Straight" << " " << setw(10) << "Overtime"
		<< " " << setw(8) << "Net" << " " << setw(9) << left << "Full/Part\n" << endl;

	for (int jj = 0; jj < count - 1; jj++)
	{
		cout << left << setw(20) << information[jj].name << " " << setw(MAX_SSN) //prints data
			<< information[jj].ssn << " " << setw(6) << fixed << setprecision(2)
			<< information[jj].wage << " " << setw(6) << information[jj].hours
			<< " " << setw(10) << setprecision(2) << information[jj].straightPay
			<< " " << setw(10) << setprecision(2) << information[jj].overtimePay
			<< " " << setw(8) << setprecision(2) << information[jj].netPay
			<<  " " << setw(9) << information[jj].time << endl;
	}
	
	cout << endl;

	return 0;
}

/*****************************************************************************************************
* Function: FullTime
* Purpose: Calculates full-time employee pay information 
*****************************************************************************************************/
void FullTime(Employee &data)
{
	if (data.hours > 40)
	{
		data.straightPay = (40 * data.wage); //calculates 40 hours of pay
		data.overtimePay = ((data.hours - 40) * (data.wage * 1.5F)); //calculates overtime (time and a half) pay
		data.netPay = ((data.straightPay + data.overtimePay) - 5); //calculates net pay including -$5 for union fees
	}
	else
	{
		data.straightPay = (data.hours * data.wage); // calculates pay based on hours 
		data.overtimePay = 0.0;
		data.netPay = (data.straightPay - 5); //calculates net pay including -$5 for union fees
	}
}
/*****************************************************************************************************
* Function: PartTime
* Purpose: Calculates part-time employee pay information
*****************************************************************************************************/
void PartTime(Employee &data)
{
	if (data.hours > 40)
	{
		data.straightPay = (40 * data.wage); //calculates 40 hours of pay
		data.overtimePay = ((data.hours - 40) * (data.wage * 1.5F)); //calculates overtime (time and a half) pay
		data.netPay = (data.straightPay + data.overtimePay); //calculates net pay
	}
	else
	{
		data.straightPay = (data.hours * data.wage); // calculates pay based on hours 
		data.overtimePay = 0.0;
		data.netPay = data.straightPay; //calculates net pay
	}
}

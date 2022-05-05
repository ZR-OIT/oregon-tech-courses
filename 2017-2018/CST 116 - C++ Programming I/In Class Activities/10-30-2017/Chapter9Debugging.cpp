/********************************************************************
* File: Chap_9_Debugging.cpp
*
* General Instructions: Complete each step before proceeding to the
* next.
*
* Debugging Exercise 1
*
* 1) Insert a breakpoint on the lines indicated in the code.
* 2) Run to Breakpoint 1.
* 3) Place a watch on age and days.
* 4) Add another watch using &age for the name. This will display
*    the address of age.
* 5) Write down the address of age.
* 6) Step Into the code for the function GetAge.
* 7) The execution continues to the function header for GetAge.
* 8) Step into one more time.
* 9) Why did the address of age and value change?
* 10) Step over the cout and cin statements.
* 11) Verify the value entered is stored properly in age.
* 12) Step into until the flow returns to main.
* 13) Step over one more time.
* 14) Why didn't the value entered get transferred back to main?
* 15) Stop debugging and fix the error.
* 16) Run to Breakpoint 1.
* 17) Step over the function call to GetAge.
* 18) Verify that the value entered was returned and stored
*     correctly from GetAge.
* 19) Stop debugging.
*
* Debugging Exercise 2
*
* 1) Run to Breakpoint 1.
* 2) Step over the call to GetAge.
* 3) Step into CalcDays.
* 4) Step into one more time so that the current line is the
*    calculation.
* 5) Why is age greyed out in your watch window?
* 6) Stop debugging.
*
* Debugging Exercise 3
*
* 1) Run to Breakpoint 2.
* 2) When asked, enter the value of 20 for your age.
* 3) Verify that the variable age is 20 and the variable days
*    is 7300.
* 4) Step into the PrintResults function.
* 5) Age is 7300? Not even Ralph is that old.
* 6) Why did the values for both variables change?
* 7) Stop debugging and fix the error.
*
* Debugging Exercise 4
*
* 1) Run to Breakpoint 2.
* 2) Display your Call Stack window.
* 3) View the contents of the window and notice that the top
*    function on the stack is main.
* 4) Step into the PrintResults function.
* 5) Notice that the call stack now shows PrintResults on top of
*    the stack.
********************************************************************/
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

const int DAYS_PER_YEAR = 365;

int GetAge(int &age);
int CalcDays(int age);
void PrintResults(int age, int days);

int main()
{
	int age = 0;
	int days = 0;

	// Breakpoint 1
	// Put breakpoint on the following line 
	age = GetAge(age);
	days = CalcDays(age);

	// Breakpoint 2
	// Put breakpoint on the following line 
	PrintResults(age, days);

	return 0;
}
int GetAge()
{
	int age;
	cout << "Please enter your age: ";
	cin >> age;

	return age;
}
int CalcDays(int years)
{
	int days;

	days = years * DAYS_PER_YEAR;

	return days;
}
void PrintResults(int age, int days)
{
	cout << age << "! Boy are you old!\n";
	cout << "Did you know that you are at least "
		<< days << " days old?\n\n";
}
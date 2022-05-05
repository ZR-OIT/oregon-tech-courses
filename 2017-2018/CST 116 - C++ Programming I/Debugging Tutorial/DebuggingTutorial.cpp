/********************************************************************
* File: Chap_5_Debugging.cpp
*
* General Instructions: Complete each step before proceeding to the
* next.
*
* Debugging Exercise 1
*
* 1) On the lines indicated in the code below, insert a breakpoint.
* 2) With the program not in debugging mode, start debugging by
*    using the "Step Into" tool.
* 3) Click on the Watch1 tab.
* 4) With the cursor in the Name column type money and press enter.
*    This adds a programmer defined watch on the variable money.
* 5) Step Into until you reach the first cout statement. With
*    the current line being that cout statement, Step Into again.
* 6) What happened? Where are we now? What is all of this nasty
*    looking code?
* 7) Remember, stepping into a predefined routine takes you to the
*    code for that routine. If the debugger can't find the code it
*    will show the assembly code for that routine.
* 8) How do we get out of this mess? Use the "Step Out" tool.
* 9) In Visual Studio you will be taken back to the same cout
*    statement. Use the Step Over tool to take you to the next
*    line.
* 10) Step over the next cout statement. Now look at the console
*     window. What was printed?
* 11) Select Stop Debugging either from the Debug menu or from your
*     toolbar.
*
* Debugging Exercise 2
*
* 1) With the program stopped, run to Breakpoint 1 by selecting
*    the Start Debugging menu option, toolbar icon or press F5.
* 2) Step over the cout.
* 3) Step over the cin. Notice that you can now enter a value.
* 4) Enter the value .1 and press enter.
* 5) Notice that the current line of execution is now at the
*    calculation.
* 6) Look at your watch. What is the value of money? 123.449997
* 7) Hover your mouse pointer over raise. What is its value? .1000001
* 8) Step over the calculation. Notice the watch on money is now
*    red. This designates that the variable just changed its value.
* 9) What happened to our money? I thought a raise was supposed
*    to increase our money? Stop debugging and fix the calculation.
*
* Debugging Exercise 3
*
* 1) Choose Disable All Breakpoints from the Debug menu.
* 2) With the cursor on the calculation, Run to Cursor. Remember
*    that the Run to Cursor tool can be accessed by right clicking
*    in the code window and choosing the correct menu option.
* 3) Step over the calculation and verify that this time
*    you end up with more money than before the raise.
* 4) Stop debugging. Now run the entire program by choosing the menu
*    option Start Without Debugging.
*
********************************************************************/

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	float money = 123.45F;
	float raise;

	cout << "You have $";
	cout << money << endl;

	// Breakpoint 1
	// Put a breakpoint on the following line
	cout << "Enter percent raise: ";
	cin >> raise;

	money = (money * raise) + money;

	cout << "After your raise you have $";
	cout << money << endl;

	return 0;
}
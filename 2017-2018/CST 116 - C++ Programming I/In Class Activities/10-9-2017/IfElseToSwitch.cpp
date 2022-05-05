// Zak Rowland 10/9/2017 In-Class Assn.: Convert if/else statements to a switch function.

#include <iostream>

int main()
{
	int operand1, operand2, result;
	int operation;

	std::cout << "Enter operand 1: ";
	std::cin >> operand1;

	std::cout << "Enter operand 2: ";
	std::cin >> operand2;

	std::cout << "\nEnter operation: \n";
	std::cout << "1) Addition\n";
	std::cout << "2) Subtraction\n";
	std::cout << "3) Multiplication\n";
	std::cout << "4) Division\n";
	std::cout << "Selection: ";
	std::cin >> operation;

	switch (operation)
	{

	case 1:
		result = operand1 + operand2;
		std::cout << "\nSum is: " << result << "\n" << std::endl;
		break;

	case 2:
		result = operand1 - operand2;
		std::cout << "\nDifference is: " << result << "\n" << std::endl;
		break;

	case 3:
		result = operand1 * operand2;
		std::cout << "\nProduct is: " << result << "\n" << std::endl;
		break;

	case 4:
		result = operand1 / operand2;
		std::cout << "\nQuotient is: " << result << "\n" << std::endl;
		break;

	default:
		std::cout << "\nPlease enter a valid selection.\n" << std::endl;
		break;

	}
	
	/*if (operation == 1)
	{
		result = operand1 + operand2;
		std::cout << "\nResult is: " << result << std::endl;
	}
	else if (operation == 2)
	{
		result = operand1 - operand2;
		std::cout << "\nResult is: " << result << std::endl;
	}
	else if (operation == 3)
	{
		result = operand1 * operand2;
		std::cout << "\nResult is: " << result << std::endl;
	}
	else if (operation == 4)
	{
		result = operand1 / operand2;
		std::cout << "\nResult is: " << result << std::endl;
	}
	else
	{
		result = 0;
		std::cout << "Please enter a valid selection." << std::endl;
	}
	*/
	
	return 0;

}
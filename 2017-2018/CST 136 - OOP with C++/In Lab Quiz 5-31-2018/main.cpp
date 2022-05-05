/****************************************************************************************************
* Author: Zak Rowland
* Filename: main.cpp
* Date Created: 5/31/2018
* Modifications:
*****************************************************************************************************
* Assignment: In Lab Quiz
*
* Overview: Implement a bounded linked list template class.
*
* Input: Tests from main.cpp
*
* Output: Test results
*
*****************************************************************************************************/
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <crtdbg.h>
#include "TLList.h"
#include "LListNode.h"
#include "TLListException.h"
#include "Date.h"
#include "Person.h"

using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: main
* Purpose: Tests template classes
* Preconditon:
* Postcondition:
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// Negative length
	{
		try
		{
			TLinkedList::TLList <int> empty_list(-10);
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}
	
	// Normal int list
	{
		try
		{
			TLinkedList::TLList <int> int_list(5);
			int_list.Append(1);
			int_list.Prepend(2);
			int_list.Append(3);
			int_list.Prepend(4);
			int_list.Append(5);
			cout << int_list << endl;
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}

	// Normal float list
	{
		try
		{
			TLinkedList::TLList <float> float_list(5);
			float_list.Append(1.1f);
			float_list.Prepend(2.2f);
			float_list.Append(3.3f);
			float_list.Prepend(4.4f);
			float_list.Append(5.5f);
			cout << float_list << endl;
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}
	
	// Normal date list
	{
		try
		{
			TLinkedList::TLList <Date> date_list(5);
			Date d1(2018, 1, 5);
			Date d2(2018, 2, 10);
			Date d3(2018, 3, 15);
			Date d4(2018, 4, 20);
			Date d5(2018, 5, 25);
			date_list.Append(d1);
			date_list.Append(d2);
			date_list.Append(d3);
			date_list.Append(d4);
			date_list.Append(d5);
			cout << date_list << endl;
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}

	// Normal person list
	{
		try
		{
			TLinkedList::TLList <Person> person_list(5);
			Person p1("Zak");
			Person p2("Zak2");
			Person p3("Zak3");
			Person p4("Zak4");
			Person p5("Zak5");

			person_list.Append(p1);
			person_list.Prepend(p2);
			person_list.Append(p3);
			person_list.Prepend(p4);
			person_list.Append(p5);
			cout << person_list << endl;

			{
				TLinkedList::TLList <Person> personcopied_list(person_list);
				cout << "Copied: \n" << personcopied_list << endl;

				TLinkedList::TLList <Person> personassign_list;
				personassign_list = personcopied_list;
				cout << "Assigned: \n" << personassign_list << endl;
			}
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}

	// Full list using append
	{
		try
		{
			TLinkedList::TLList <int> fullappend_list(5);
			fullappend_list.Append(1);
			fullappend_list.Append(2);
			fullappend_list.Append(3);
			fullappend_list.Append(4);
			fullappend_list.Append(5);
			fullappend_list.Append(6);
			cout << fullappend_list << endl;
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}

	// Full list using prepend
	{
		try
		{
			TLinkedList::TLList <int> fullprepend_list(5);
			fullprepend_list.Prepend(1);
			fullprepend_list.Prepend(2);
			fullprepend_list.Prepend(3);
			fullprepend_list.Prepend(4);
			fullprepend_list.Prepend(5);
			fullprepend_list.Prepend(6);
			cout << fullprepend_list << endl;
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}

	// Copy and assign tests on int list
	{
		try
		{
			TLinkedList::TLList <int> intbase_list(5);

			intbase_list.Append(1);
			intbase_list.Append(2);
			intbase_list.Append(3);
			intbase_list.Append(4);
			intbase_list.Append(5);
			cout << "\nOriginal: \n" << intbase_list << endl;
			{
				TLinkedList::TLList <int> intcopied_list(intbase_list);
				cout << "Copied: \n" << intcopied_list << endl;

				TLinkedList::TLList <int> intassign_list;
				intassign_list = intcopied_list;
				cout << "Assigned: \n" << intassign_list << endl;
			}
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}

	// Copy and assign tests on Date list
	{
		try
		{
			TLinkedList::TLList <Date> datebase_list(5);

			Date d1(2018, 1, 5);
			Date d2(2018, 2, 10);
			Date d3(2018, 3, 15);
			Date d4(2018, 4, 20);
			Date d5(2018, 5, 25);
			datebase_list.Append(d1);
			datebase_list.Append(d2);
			datebase_list.Append(d3);
			datebase_list.Append(d4);
			datebase_list.Append(d5);
			cout << "Original: \n" << datebase_list << endl;

			TLinkedList::TLList <Date> datecopied_list(datebase_list);
			cout << "Copied: \n" << datecopied_list << endl;
			TLinkedList::TLList <Date> dateassign_list = datecopied_list;
			cout << "Assigned: \n" << dateassign_list << endl;
		}
		catch (exception &e)
		{
			cout << "An exception has occurred: " << e.what() << endl;
		}
	}
}
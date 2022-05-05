#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Person.h"
#include "Date.h"
#include "Cube.h"
#include "Person.h"

//#include "CubeStack.h"
#include "TStack.h"

#include "TStackException.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//{
	//	TStack <int> mystackI(100);
	//	TStack < TStack < int > > mystackS(100);
	//
	//	mystackS = mystackI(50);
	//}
	try
	{
		TStack <int> mystack(100);

		mystack.Push(1);
		mystack.Push(2);
		mystack.Push(3);
		mystack.Push(4);
		mystack.Push(5);
		mystack.Push(6);

		cout << mystack << endl;

		//for (int i = 0; i < 100; i++)
		//{
		//	int j = mystack.Pop();
		//}

		TStack <int> mystack2(mystack);
		cout << mystack2 << endl;
		TStack <int> mystack3;
		mystack3 = mystack;
		cout << mystack3 << endl;
	}
	catch (TStackException &e)
	{
		//cout << e.GetFileName() << " " << e.GetMethodName() << " " << e.what() << endl;
		cout << e << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	catch (const char e[])
	{
		cout << e << endl;
	}
	catch (int num)
	{
		cout << "The error number is: " << num << endl;
	}
	catch (...)
	{
		cout << "I catch everything" << endl;
	}

	try
	{
		TStack <float> mystack(50);

		mystack.Push(1.2f);
		mystack.Push(2.3f);
		mystack.Push(3.7f);
		mystack.Push(4.9f);
		mystack.Push(5.1f);
		mystack.Push(6.0f);

		cout << mystack << endl;

		//TStack <float> mystack2(mystack);
		//cout << mystack2 << endl;
		//TStack <float> mystack3;
		//mystack3 = mystack;
		//cout << mystack3 << endl;
	}
	catch (TStackException &e)
	{
		//cout << e.GetFileName() << " " << e.GetMethodName() << " " << e.what() << endl;
		cout << e << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	catch (const char e[])
	{
		cout << e << endl;
	}
	catch (int num)
	{
		cout << "The error number is: " << num << endl;
	}
	catch (...)
	{
		cout << "I catch everything" << endl;
	}

	{
		Person *p6 = nullptr;
		try
		{
			TStack <Person> mystack(5);

			Person p1("Jesse");
			Person p2("Todd");
			Person p3("Calvin");
			Person p4("Troy");
			Person p5("Phil");

			mystack.Push(p1);
			mystack.Push(p2);
			mystack.Push(p3);
			mystack.Push(p4);
			mystack.Push(p5);

			p6 = new Person("Claude");
			mystack.Push(*p6);
			delete p6;
			p6 = nullptr;

			//cout << mystack << endl;

			//TStack <Person> mystack2(mystack);
			//cout << mystack2 << endl;
			//TStack <Person> mystack3;
			//mystack3 = mystack;
			//cout << mystack3 << endl;
		}
		catch (TStackException &e)
		{
			//cout << e.GetFileName() << " " << e.GetMethodName() << " " << e.what() << e.GetLine() << endl;
			cout << e << endl;
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}
		catch (const char e[])
		{
			cout << e << endl;
		}
		catch (int num)
		{
			cout << "The error number is: " << num << endl;
		}
		catch (...)
		{
			cout << "I catch everything" << endl;
		}
		delete p6;
		p6 = nullptr;
	}
	//return 0;
	try
	{
		TStack < Date > mystack(6);

		Date d1(2018, 1, 5);
		Date d2(2018, 2, 10);
		Date d3(2018, 3, 15);
		Date d4(2018, 4, 20);
		Date d5(2018, 5, 25);
		Date d6(2018, 5, 30);

		mystack.Push(d1);
		mystack.Push(d2);
		mystack.Push(d3);
		mystack.Push(d4);
		mystack.Push(d5);
		mystack.Push(d6);

		//cout << mystack << endl;

		//TStack <Date> mystack2(mystack);
		//cout << mystack2 << endl;
		//TStack <Date> mystack3;
		//mystack3 = mystack;
		//cout << mystack3 << endl;
	}
	catch (TStackException &e)
	{
		//cout << e.GetFileName() << " " << e.GetMethodName() << " " << e.what() << endl;
		cout << e << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	catch (const char e[])
	{
		cout << e << endl;
	}
	catch (int num)
	{
		cout << "The error number is: " << num << endl;
	}
	catch (...)
	{
		cout << "I catch everything" << endl;
	}

	{
		try
		{
			//CubeStack mystack(3);
			TStack < Cube > mystack(3);

			Cube c1(1);
			Cube c2(2);
			Cube c3(3);
			Cube c4(4);
			Cube c5(5);
			Cube c6(6);

			cout << endl;

			cout << "max size is: " << mystack.GetMaxSize() << endl;
			cout << "Pushing on the stack" << endl;
			cout << "stack size before push is: " << mystack.GetStackSize() << endl;
			mystack.Push(c1);
			cout << "stack size after push is: " << mystack.GetStackSize() << endl;
			cout << endl;

			mystack.Push(c3);
			mystack.Push(c4);

			cout << mystack << endl;

			mystack.Push(c5); // will throw exception
			mystack.Push(c6);

			//TStack <Cube> mystack2(mystack);
			//cout << mystack2 << endl;
			//TStack <Cube> mystack3;
			//mystack3 = mystack;
			//cout << mystack3 << endl;
		}
		catch (TStackException &e)
		{
			//cout << e.GetFileName() << " " << e.GetMethodName() << " " << e.what() << endl;
			cout << e << endl;
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
		}
		catch (const char e[])
		{
			cout << e << endl;
		}
		catch (int num)
		{
			cout << "The error number is: " << num << endl;
		}
		catch (...)
		{
			cout << "I catch everything" << endl;
		}
	}

	return 0;
}
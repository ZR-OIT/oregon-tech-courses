/****************************************************************************************************
* Author: Zak Rowland
* Filename: Person.cpp
* Date Created: 4/7/2018
* Modifications:
*****************************************************************************************************
* Assignment: Lab 2 - Address List
*
* Overview: Create a doubly linked list of the names and addresses, based on the provided files
*			and sample data.
*
* Input:	Tests from main.cpp and data from CSV files.
*
* Output:	Results of tests from main.cpp.
*
*****************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "AddressList.h"

using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: AddressList(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: Class object with properly allocated memory
*****************************************************************************************************/
AddressList::AddressList(void): m_head(nullptr), m_tail(nullptr), m_length(0)
{
}

/*****************************************************************************************************
* Function: AddressList(const AddressList & addressList)
* Purpose: Copy constructor
* Preconditon: An AddressList class object to be copied.
* Postcondition: A copy of the passed class object.
*****************************************************************************************************/
AddressList::AddressList(const AddressList & addressList)
	: m_head(nullptr), m_tail(nullptr), m_length(0)
{
	Node *travel = addressList.m_head;

	while (travel != nullptr)
	{
		Insert(travel->GetPerson()->GetFName(), travel->GetPerson()->GetLName(), travel->GetPerson()->GetEMail(),
			travel->GetPerson()->GetStreet(), travel->GetPerson()->GetCity(), travel->GetPerson()->GetState(), travel->GetPerson()->GetZip());
		travel = travel->GetNext();
	}
}

/*****************************************************************************************************
* Function: ~AddressList(void)
* Purpose: Destructor
* Preconditon: Class object with properly allocated memory.
* Postcondition: Class object memory returned to heap and pointers set to null.
*****************************************************************************************************/
AddressList::~AddressList(void)
{
	Clear();
}

/*****************************************************************************************************
* Function: AddressList::operator=(const AddressList & addressList)
* Purpose: Assignment operator
* Preconditon: An AddressList class object to be assigned to the current class object.
* Postcondition: If the current object is equal to the passed object, make no change.
*				 Otherwise, allocate and copy the passed object into the current object.
*****************************************************************************************************/
AddressList & AddressList::operator=(const AddressList & addressList)
{
	if (&addressList != this)
	{
		Clear();
		Node *travel = addressList.m_head;

		while (travel != nullptr)
		{
			Insert(travel->GetPerson()->GetFName(), travel->GetPerson()->GetLName(), travel->GetPerson()->GetEMail(),
				travel->GetPerson()->GetStreet(), travel->GetPerson()->GetCity(), travel->GetPerson()->GetState(), travel->GetPerson()->GetZip());
			travel = travel->GetNext();
		}
	}

	return *this;
}

/*****************************************************************************************************
* Function: Insert(const char * fname, const char * lname, const char * email, const ...)
* Purpose: Inserts a new node into an ordered list.
* Preconditon: A list, either empty or containing data.
* Postcondition: The list with a new node inserted.
*****************************************************************************************************/
void AddressList::Insert(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	if (m_head == nullptr || m_head->Compare(fname, lname) < 0) //if list is empty or only has 1 item
	{
		prepend(fname, lname, email, street, city, state, zip);
	}
	else
	{
		Node *newNode = new Node(fname, lname, email, street, city, state, zip);
		Node *travel = m_head;
		Node *trail = nullptr;

		while ((travel != nullptr) && (travel->Compare(fname, lname) > 0))
		{
			trail = travel;
			travel = travel->GetNext();
		}

		newNode->SetNext(travel);
		newNode->SetPrev(trail);

		trail->SetNext(newNode);
		if (travel == nullptr)
		{
			m_tail = newNode;
		}
		else
		{
			travel->SetPrev(newNode);
		}
		m_length++;
		m_next = nullptr;
		m_nextR = nullptr;
	}
}

/*****************************************************************************************************
* Function: Insert(const AddressList & addressList)
* Purpose: Inserts a new nodes from an existing list.
* Preconditon: A list, either empty or containing data.
* Postcondition: The list with a new nodes inserted from passed list.
*****************************************************************************************************/
void AddressList::Insert(const AddressList & addressList)
{
	Node *listTravel = addressList.m_head;

	while (listTravel != nullptr && this != &addressList)
	{
		Person *personPtr = listTravel->GetPerson();

		if (m_head == nullptr || m_head->Compare(personPtr->GetFName(), personPtr->GetLName()) < 0) //if list is empty or only has 1 item
		{
			prepend(personPtr->GetFName(), personPtr->GetLName(), personPtr->GetEMail(), 
				personPtr->GetStreet(), personPtr->GetCity(), personPtr->GetState(), personPtr->GetZip());
		}
		else
		{
			Node *newNode = new Node(personPtr->GetFName(), personPtr->GetLName(), personPtr->GetEMail(),
				personPtr->GetStreet(), personPtr->GetCity(), personPtr->GetState(), personPtr->GetZip());
			Node *travel = m_head; //sets travel pointer to head of list
			Node *trail = nullptr;

			while ((travel != nullptr) && (travel->Compare(personPtr->GetFName(), personPtr->GetLName()) > 0))
			{
				trail = travel;
				travel = travel->GetNext();
			}

			newNode->SetNext(travel);
			newNode->SetPrev(trail);

			trail->SetNext(newNode);
			if (travel == nullptr)
			{
				m_tail = newNode;
			}
			else
			{
				travel->SetPrev(newNode);
			}
			m_length++;
			m_next = nullptr;
			m_nextR = nullptr;
		}
		listTravel = listTravel->GetNext();

		if(listTravel != nullptr)
			personPtr = listTravel->GetPerson();
	}
}

/*****************************************************************************************************
* Function: Delete(const char * fname, const char * lname)
* Purpose: Deletes an entry from the list.
* Preconditon: A list, either empty or containing data.
* Postcondition: The list with a node removed, or no node removed if name isn't found.
*****************************************************************************************************/
Person * AddressList::Delete(const char * fname, const char * lname)
{
	Node * travel = m_head;
	Person * found = nullptr;

	while (travel != nullptr && found == nullptr)
	{
		if (travel->Compare(fname, lname) == 0)
		{
			Node * prev = travel->GetPrev();
			Node * next = travel->GetNext();

			if (prev == nullptr && next != nullptr) //if node to delete is head
			{
				Person *temp = new Person(*travel->GetPerson());
				found = temp;
				next->SetPrev(nullptr);
				m_head = next;
				delete travel;
			}
			else if (prev != nullptr && next == nullptr) //if node to delete is tail
			{
				Person *temp = new Person(*travel->GetPerson());
				found = temp;
				prev->SetNext(nullptr);
				m_tail = prev;
				delete travel;
			}
			else if (next == nullptr && prev == nullptr) //if node to delete is only node
			{
				Person *temp = new Person(*travel->GetPerson());
				found = temp;
				m_head = nullptr;
				m_tail = nullptr;
				delete travel;
			}
			else //if node to delete is between two nodes
			{
				Person *temp = new Person(*travel->GetPerson());
				found = temp;
				prev->SetNext(next);
				next->SetPrev(prev);
				delete travel;
			}
			m_length--;
			m_next = nullptr;
			m_nextR = nullptr;
		}
		else
		{
			travel = travel->GetNext();
		}
	}
	return found;
}

/*****************************************************************************************************
* Function: Delete(const AddressList & addressList)
* Purpose: Deletes entries from the list.
* Preconditon: A list, either empty or containing data.
* Postcondition: The list with a nodes removed according to passed list, or no nodes removed if name isn't found.
*****************************************************************************************************/
bool AddressList::Delete(const AddressList & addressList)
{
	bool deleted = false;

	Node *listTravel = addressList.m_head;

	Node * travel = m_head;

	Person * found = nullptr;

	while (listTravel != nullptr && this != &addressList)
	{
		while (travel != nullptr && found == nullptr)
		{
			if (travel->Compare(listTravel->GetPerson()->GetFName(), listTravel->GetPerson()->GetLName()) == 0)
			{
				Node * prev = travel->GetPrev();
				Node * next = travel->GetNext();

				if (prev == nullptr) //if node to delete is head
				{
					found = travel->GetPerson();
					next->SetPrev(nullptr);
					m_head = next;
					delete travel;
				}
				else if (next == nullptr) //if node to delete is tail
				{
					found = travel->GetPerson();
					prev->SetNext(nullptr);
					prev = m_tail;
					delete travel;
				}
				else if (next == nullptr && prev == nullptr) //if node to delete is only node
				{
					found = travel->GetPerson();
					m_head = nullptr;
					m_tail = nullptr;
					delete travel;
				}
				else //if node to delete is between two nodes
				{
					found = travel->GetPerson();
					prev->SetNext(next);
					next->SetPrev(prev);
					delete travel;
				}
				deleted = true;
				m_length--;
				m_next = nullptr;
				m_nextR = nullptr;
			}
			else
			{
				travel = travel->GetNext();
			}
		}
		listTravel = listTravel->GetNext();
		travel = m_head;
		found = false;
	}
	return deleted;
}

/*****************************************************************************************************
* Function: Find(const char * fname, const char * lname) const
* Purpose: Locates an entry in the list.
* Preconditon: A list, either empty or containing data.
* Postcondition: A pointer to the found entry, or nullptr if not found.
*****************************************************************************************************/
Person * AddressList::Find(const char * fname, const char * lname) const
{
	Node * travel = m_head;
	Person * found = nullptr;

	while (travel != nullptr && found == nullptr)
	{
		if (travel->Compare(fname, lname) == 0)
		{
			found = travel->GetPerson();
		}
		else
		{
			travel = travel->GetNext();
		}
	}
	return found;
}

/*****************************************************************************************************
* Function: Clear(void)
* Purpose: Frees all memory for the instance.
* Preconditon: A class object that has allocated memory.
* Postcondition: All memory returned to heap and pointers assigned to null.
*****************************************************************************************************/
void AddressList::Clear(void)
{
	Node *travel = m_head;

	while (travel != nullptr)
	{
		Node *next = travel->GetNext();
		delete travel;
		travel = next;
	}

	m_head = nullptr;
	m_tail = nullptr;
	m_length = 0;
}

/*****************************************************************************************************
* Function: Display(bool forward) const
* Purpose: Display the list either forward or reverse.
* Preconditon:
* Postcondition:
*****************************************************************************************************/
void AddressList::Display(bool forward) const
{
	if (forward == true)
	{
		Node *travel = m_head;

		while (travel != nullptr)
		{
			Node *next = travel->GetNext();
			travel->Display();
			travel = next;
		}
	}
	else
	{
		Node *travel = m_tail;

		while (travel != nullptr)
		{
			Node *previous = travel->GetPrev();
			travel->Display();
			travel = previous;
		}
	}
}

/*****************************************************************************************************
* Function: Length(void) const
* Purpose: Returns the value of the m_length data member.
* Preconditon: No access to private data members.
* Postcondition: The value of a private data member.
*****************************************************************************************************/
size_t AddressList::Length(void) const
{
	return this->m_length;
}

/*****************************************************************************************************
* Function: Next(void)
* Purpose: Allows stepping through the list forward.
* Preconditon: Nullptr
* Postcondition: Either nullptr or a pointer to the next person.
*****************************************************************************************************/
Person * AddressList::Next(void)
{
	Person * next = nullptr;

	if (m_next == nullptr && m_head != nullptr)
	{
		next = m_head->GetPerson();
		m_next = m_head;
	}
	else if (m_head != nullptr)
	{
		m_next = m_next->GetNext();

		if (m_next == nullptr)
		{
			m_next = m_head;
			next = m_next->GetPerson();
		}
		else
			next = m_next->GetPerson();
	}

	return next;
}

/*****************************************************************************************************
* Function: NextR(void)
* Purpose: Allows stepping through the list in reverse.
* Preconditon: Nullptr
* Postcondition: Either nullptr or a pointer to the previous (nextR) node.
*****************************************************************************************************/
Person * AddressList::NextR(void)
{
	Person * next = nullptr;

	if (m_nextR == nullptr && m_tail != nullptr)
	{
		next = m_tail->GetPerson();
		m_nextR = m_tail;
	}
	else if (m_tail != nullptr)
	{
		m_nextR = m_nextR->GetPrev();

		if (m_nextR == nullptr)
		{
			m_nextR = m_tail;
			next = m_nextR->GetPerson();
		}
		else
			next = m_nextR->GetPerson();
	}

	return next;
}

/*****************************************************************************************************
* Function: LoadFile(const char * fileName)
* Purpose: Opens a file and replaces the current address list with its contents.
* Preconditon: A list, either empty or containing data.
* Postcondition: A new list with data from a file.
*****************************************************************************************************/
void AddressList::LoadFile(const char * fileName)
{
	this->Clear();
	AddFile(fileName);
}

/*****************************************************************************************************
* Function: AddFile(const char * fileName)
* Purpose: Opens a file and inserts its contents into the current address list.
* Preconditon: A list, either empty or containing data.
* Postcondition: The existing list merged with the file data.
*****************************************************************************************************/
void AddressList::AddFile(const char * fileName)
{
	const int BUFFER_SIZE = 128;
	char tempLine[BUFFER_SIZE];

	ifstream input(fileName); //opens file

	if (input.is_open()) //checks if file is open
	{
		input.getline(tempLine, BUFFER_SIZE); //grabs a line of data from the file
		while (!input.eof() && strlen(tempLine) > 0)//runs until file ends
		{
			char *fname, *lname, *email, *street, *city, *state, *zip;

			fname = strtok(tempLine, ","); //breaks apart data into respective types
			lname = strtok(nullptr, ",");
			email = strtok(nullptr, ",");
			street = strtok(nullptr, ",");
			city = strtok(nullptr, ",");
			state = strtok(nullptr, ",");
			zip = strtok(nullptr, "\n");

			this->Insert(fname, lname, email, street, city, state, zip);
			input.getline(tempLine, BUFFER_SIZE); //grabs a line of data from the file
		}
		input.close();
	}

	else
		cout << "File failed to open." << endl;
}

/*****************************************************************************************************
* Function: SaveFile(const char * fileName) const
* Purpose: Opens a file and writes the current list into it.
* Preconditon: A list, either empty or containing data.
* Postcondition: A new file containing data from the list.
*****************************************************************************************************/
void AddressList::SaveFile(const char * fileName) const
{
	ofstream output(fileName); //opens file

	if (output.is_open())
	{
		Node *travel = m_head;

		while (travel != nullptr)
		{
			Person *person = travel->GetPerson();
			
			output << person->GetFName() << "," << person->GetLName() << "," << person->GetEMail()
				<< "," << person->GetStreet() << "," << person->GetCity() << "," << person->GetState()
				<< "," << person->GetZip() << "\n";

			travel = travel->GetNext();
		}
	}
	output.close();
}

/*****************************************************************************************************
* Function: prepend(const char * fname, const char * lname, const char * email, const ...)
* Purpose: Prepends a new node into an ordered list.
* Preconditon: A list, either empty or containing data.
* Postcondition: The list with a new node inserted as the head.
*****************************************************************************************************/
void AddressList::prepend(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	if (m_head == nullptr)
	{
		Node *newNode = new Node(fname, lname, email, street, city, state, zip);
		m_head = newNode;
		m_tail = newNode;
	}
	else
	{
		Node *newNode = new Node(fname, lname, email, street, city, state, zip);
		m_head->SetPrev(newNode);
		newNode->SetNext(m_head);
		m_head = newNode;
	}

	m_length++;
	m_next = nullptr;
	m_nextR = nullptr;
}

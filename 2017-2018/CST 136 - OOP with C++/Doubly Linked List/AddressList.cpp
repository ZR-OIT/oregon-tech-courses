/****************************************************************************************************
* Author: Zak Rowland
* Filename: AddressList.cpp
* Date Created: 3/8/2018
* Modifications:
*****************************************************************************************************
* Assignment: Doubly Linked List
*
* Overview: Read file containing names and addresses. Create a linked list of the names and addresses.
*			The linked list must be a doubly linked list, there must be m_next and m_prev pointers.
*			The linked list must be stored ordered by last name and first name.
*			Be able to display the list in both forward and reverse directions.
*
* Input: "AddressBook.csv"
*
* Output: Address list
*
*****************************************************************************************************/

#include "AddressList.h"

/*****************************************************************************************************
* Function: AddressList(void)
* Purpose: Default constructor
*****************************************************************************************************/
AddressList::AddressList(void) : m_head(nullptr), m_tail(nullptr), m_length(0)
{
}

/*****************************************************************************************************
* Function: AddressList(const AddressList & addressList)
* Purpose: Copy constructor
*****************************************************************************************************/
AddressList::AddressList(const AddressList & addressList)
{
	Node *travel = nullptr;

	travel = addressList.m_head;

	while (travel != nullptr)
	{
		travel = travel->GetNext();
	}
}

/*****************************************************************************************************
* Function: ~AddressList(void)
* Purpose: Destructor
*****************************************************************************************************/
AddressList::~AddressList(void)
{
	Clear();
}

/*****************************************************************************************************
* Function: operator=(const AddressList & addressList)
* Purpose: Assignment operator
*****************************************************************************************************/
AddressList & AddressList::operator=(const AddressList & addressList)
{
	m_head = addressList.m_head;
	m_tail = addressList.m_tail;
	m_length = addressList.m_length;

	return *this;
}

/*****************************************************************************************************
* Function: Insert(const char * fname, const char * lname, const char * email, const char * street, 
*					const char * city, const char * state, const char * zip)
* Purpose: Inserts a node into the list
*****************************************************************************************************/
void AddressList::Insert(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	Node *travel = m_head; //sets travel pointer to head of list

	if (travel == nullptr) //if list is empty
	{
		prepend(fname, lname, email, street, city, state, zip);
	}
	else
	{
		while (((travel->GetNext()) != nullptr) && (travel->Compare(fname, lname) > 0))
		{
			travel = travel->GetNext();
		}

		if (travel == m_head)
		{
			prepend(fname, lname, email, street, city, state, zip);
		}
		else if (travel->GetNext() != nullptr)
		{
			Node newNode = Node(fname, lname, email, street, city, state, zip);
			newNode.SetPrev(travel->GetPrev());
			newNode.SetNext(travel);
			travel->GetPrev()->SetNext(&newNode);
			travel->SetPrev(&newNode);
		}
	}

	m_length++;
}

/*****************************************************************************************************
* Function: Display(bool forward)
* Purpose: Displays the list of addresses either forward or backward
*****************************************************************************************************/
void AddressList::Display(bool forward)
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
* Function: Delete(const char * fname, const char * lname)
* Purpose: Return true is address was found and deleted, else false. 
*****************************************************************************************************/
bool AddressList::Delete(const char * fname, const char * lname)
{
	bool deleted = false;
	Person *find = nullptr;

	find = Find(fname, lname);

	if (find == nullptr)
	{
		deleted = false;
	}
	else
	{

	}

	return deleted;
}

/*****************************************************************************************************
* Function: Find(const char * fname, const char * lname) const
* Purpose: Finds an element in the linked list
*****************************************************************************************************/
Person * AddressList::Find(const char * fname, const char * lname) const
{
	return nullptr;
}

/*****************************************************************************************************
* Function: Clear(void)
* Purpose: Deallocates used memory
*****************************************************************************************************/
void AddressList::Clear(void)
{
}

/*****************************************************************************************************
* Function: Length(void)
* Purpose: Returns length of address list
*****************************************************************************************************/
size_t AddressList::Length(void)
{
	return this->m_length;
}

/*****************************************************************************************************
* Function: prepend(const char * fname, const char * lname, const char * email, const char * street, 
*					 const char * city, const char * state, const char * zip)
* Purpose: Adds an address to the beginning of the list
*****************************************************************************************************/
void AddressList::prepend(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	Node newNode = Node(fname, lname, email, street, city, state, zip);
	newNode.SetNext(m_head);
	newNode.SetPrev(nullptr);
	m_head = &newNode;
}

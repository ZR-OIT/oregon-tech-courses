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
	//m_head = addressList.m_head;
	//m_tail = addressList.m_tail;
	//m_length = addressList.m_length;
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
* Function: Insert(const char * fname, const char * lname, const char * email, const char * street, 
*					const char * city, const char * state, const char * zip)
* Purpose: Inserts a node into the list
*****************************************************************************************************/
void AddressList::Insert(const char * fname, const char * lname, const char * email, const char * street, const char * city, const char * state, const char * zip)
{
	if (m_head == nullptr || m_head->Compare(fname, lname) > 0) //if list is empty or only has 1 item
	{
		prepend(fname, lname, email, street, city, state, zip);
	}
	else
	{
		Node *newNode = new Node(fname, lname, email, street, city, state, zip);
		Node *travel = m_head; //sets travel pointer to head of list
		Node *trail = nullptr;

		while ((travel != nullptr) && (travel->Compare(fname, lname) < 0))
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

		//while (((travel->GetNext()) != nullptr) && (travel->Compare(fname, lname) < 0))
		//{
		//	travel = travel->GetNext();
		//}

		//if (travel->GetNext() == nullptr)
		//{
		//	travel->SetNext(newNode);
		//	newNode->SetPrev(travel);
		//	m_tail = newNode;
		//}
		//else
		//{
		//	newNode->SetPrev(m_head);
		//	m_head->SetNext(newNode);
		//}
	}
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
* Purpose: Return true if node was found and deleted, else false. 
*****************************************************************************************************/
bool AddressList::Delete(const char * fname, const char * lname)
{
	bool deleted = false;

	Node * travel = m_head;
	Person * found = nullptr;

	cout << "\n" << endl;

	while (travel != nullptr && found == nullptr)
	{
		if (travel->Compare(fname, lname) == 0)
		{
			found = travel->GetPerson();
			Node * prev = travel->GetPrev();
			Node * next = travel->GetNext();
			
			if (prev == nullptr) //if node to delete is head
			{
				next->SetPrev(nullptr);
				next = m_head;
				delete travel;
			}
			else if (next == nullptr) //if node to delete is tail
			{
				prev->SetNext(nullptr);
				prev = m_tail;
				delete travel;
			}
			else if (next == nullptr && prev == nullptr) //if node to delete is only node
			{
				m_head = nullptr;
				m_tail = nullptr;
				prev->SetNext(nullptr);
				prev->SetPrev(nullptr);
				next->SetNext(nullptr);
				next->SetPrev(nullptr);
				delete travel;
			}
			else //if node to delete is between two nodes
			{
				prev->SetNext(next);
				next->SetPrev(prev);
				delete travel;
			}
			deleted = true;
			m_length--;
		}
		else
		{
			travel = travel->GetNext();
		}
	}
	return deleted;
}

/*****************************************************************************************************
* Function: Find(const char * fname, const char * lname) const
* Purpose: Finds an element in the linked list
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
* Purpose: Deallocates used memory
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
}

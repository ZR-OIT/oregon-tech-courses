/****************************************************************************************************
* Author: Zak Rowland
* Filename: CardStackList.cpp
* Date Created: 4/17/2018
* Modifications:
*****************************************************************************************************
* Assignment: Stacks and Op Overload Lab 3 - Part 1
*
* Overview: Implement a stack in 2 different ways, first as a doubly linked list and second as an array.
*
* Input: Tests from CardStack_main.cpp
*
* Output: Results of tests from CardStack_main.cpp
*
*****************************************************************************************************/
#include <iostream>
#include "CardStackList.h"
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: CardStackList(size_t size)
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new empty Card stack list
*****************************************************************************************************/
CardStackList::CardStackList(size_t size)
		: m_head(nullptr), m_tail(nullptr), m_maxSize(size), m_index(0)
{
	//empty
}

/*****************************************************************************************************
* Function: CardStackList(const CardStackList & csa)
* Purpose: Copy constructor
* Preconditon: No class object
* Postcondition: A new Card stack list copied from the passed Card stack list
*****************************************************************************************************/
CardStackList::CardStackList(const CardStackList & csa)
	//: m_head(csa.m_head), m_tail(csa.m_tail), m_maxSize(csa.m_maxSize), m_index(csa.m_index)
{
	CardNode *travel = csa.m_tail;

	Clear();

	m_maxSize = csa.m_maxSize;

	while (travel != nullptr)
	{
		Push(travel->GetCard()->GetCardRank(), travel->GetCard()->GetCardSuit());
		travel = travel->GetPrev();
	}
}

/*****************************************************************************************************
* Function: ~CardStackList(void)
* Purpose: Destructor
* Preconditon: A Card stack list
* Postcondition: Frees all memory and deletes the current Card stack list
*****************************************************************************************************/
CardStackList::~CardStackList(void)
{
	Clear();
}

/*****************************************************************************************************
* Function: operator=(const CardStackList & csa)
* Purpose: Assignment operator
* Preconditon: Two Card stack lists
* Postcondition: The current Card stack list is set equal to the passed Card stack list
*****************************************************************************************************/
CardStackList & CardStackList::operator=(const CardStackList & csa)
{
	if (this != &csa)
	{
	
		CardNode *travel = csa.m_tail;

		Clear();

		m_maxSize = csa.m_maxSize;

		while (travel != nullptr)
		{
			Push(travel->GetCard()->GetCardRank(), travel->GetCard()->GetCardSuit());
			travel = travel->GetPrev();
		}
	}
	return *this;
}

/*****************************************************************************************************
* Function: Push(Card & card)
* Purpose: Pushes a copy of the passed card onto the stack list
* Preconditon: A Card stack list
* Postcondition: The current Card stack list with a copy of the passed Card pushed onto the stack
*****************************************************************************************************/
bool CardStackList::Push(Card & card)
{
	bool pushed = true;

	pushed = Push(card.GetCardRank(), card.GetCardSuit());

	return pushed;
}

/*****************************************************************************************************
* Function: Push(Card::CardRank rank, Card::CardSuit suit)
* Purpose: Pushes a new card onto the stack list
* Preconditon: A Card stack list
* Postcondition: The current Card stack list with a new Card pushed onto the stack
*****************************************************************************************************/
bool CardStackList::Push(Card::CardRank rank, Card::CardSuit suit)
{
	bool pushed = true;

	if (IsFull())
		pushed = false;

	else
	{
		CardNode *newNode = new CardNode(rank, suit);
		newNode->SetNext(m_head);
		
		if(m_head != nullptr)
			m_head->SetPrev(newNode);
		
		m_head = newNode;
		
		if (m_tail == nullptr)
			m_tail = newNode;
		
		m_index++;
	}

	return pushed;
}

/*****************************************************************************************************
* Function: Pop(void)
* Purpose: Removes a card from the top of the stack list
* Preconditon: A Card stack list
* Postcondition: The current Card stack list with the Card on the top of the stack deleted
*****************************************************************************************************/
Card * CardStackList::Pop(void)
{
	Card *card = nullptr;

 	if (m_head != nullptr)
	{
		CardNode *temp = m_head;
		card = m_head->GetCard();
		m_head = m_head->GetNext();
		temp->SetNext(nullptr);
		temp->SetPrev(nullptr);
		temp->m_card = nullptr;
		delete temp;

		m_index--;
	}
	return card;
}

/*****************************************************************************************************
* Function: Peek(void) const
* Purpose: Checks the top card in the stack list
* Preconditon: A Card stack list
* Postcondition: The Card at the top of the current stack list
*****************************************************************************************************/
Card * CardStackList::Peek(void) const
{
	Card *card = nullptr;

	if (m_head != nullptr)
		card = m_head->GetCard();

	return card;
}

/*****************************************************************************************************
* Function: Clear(void)
* Purpose: Clears the stack list
* Preconditon: A Card stack list
* Postcondition: Memory freed and the current Card stack list deleted
*****************************************************************************************************/
void CardStackList::Clear(void)
{
	CardNode *travel = m_head;

	while (travel != nullptr)
	{
		CardNode *next = travel->GetNext();
		delete travel;
		travel = next;
	}
	m_head = nullptr;
	m_tail = nullptr;
	m_index = 0;
}

/*****************************************************************************************************
* Function: Resize(size_t size)
* Purpose: Changes the size of the stack list
* Preconditon: A Card stack list
* Postcondition: The current card stack list made larger or smaller
*****************************************************************************************************/
bool CardStackList::Resize(size_t size)
{
	bool affected = false;

	if (size < m_maxSize)
	{
		int difference = m_maxSize - size;

		for (int i = 0; i < difference; i++)
		{
			Card *p = Pop();
			delete p;
		}
		m_maxSize = size;
		affected = true;
	}
	
	else if (size > m_maxSize)
	{
		m_maxSize = size;
		affected = false;
	}
	
	return affected;
}

/*****************************************************************************************************
* Function: MaxSize(void) const
* Purpose: Returns the max size of the current stack list
* Preconditon: No access to private data members
* Postcondition: Max size of current array
*****************************************************************************************************/
size_t CardStackList::MaxSize(void) const
{
	return m_maxSize;
}

/*****************************************************************************************************
* Function: CurrSize(void) const
* Purpose: Returns the current size of the current stack list
* Preconditon: No access to private data members
* Postcondition: Current size of current array
*****************************************************************************************************/
size_t CardStackList::CurrSize(void) const
{
	return m_index;
}

/*****************************************************************************************************
* Function: IsFull(void) const
* Purpose: Checks if the current stack list is full
* Preconditon: A Card stack list
* Postcondition: If the current size equals the max size then the array is full
*****************************************************************************************************/
bool CardStackList::IsFull(void) const
{
	bool full = false;

	if (m_index >= m_maxSize)
		full = true;

	return full;
}

/*****************************************************************************************************
* Function: Display(bool topToBotton) const
* Purpose: Displays the current stack list
* Preconditon: A Card stack list
* Postcondition: Output of the Cards in the current Card stack list
*****************************************************************************************************/
void CardStackList::Display(bool topToBotton) const
{
	if (topToBotton == true)
	{
		CardNode *travel = m_head;
		while (travel != nullptr)
		{
			travel->GetCard()->Display();
			travel = travel->GetNext();
		}
	}
	else
	{
		CardNode *travel = m_tail;
		while (travel != nullptr)
		{
			travel->GetCard()->Display();
			travel = travel->GetPrev();
		}
	}
}

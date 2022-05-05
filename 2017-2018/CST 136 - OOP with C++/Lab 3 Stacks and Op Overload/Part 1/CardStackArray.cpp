/****************************************************************************************************
* Author: Zak Rowland
* Filename: CardStackArray.cpp
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
#include "CardStackArray.h"
using std::cout;
using std::cin;
using std::endl;


/*****************************************************************************************************
* Function: CardStackArray(size_t size)
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new empty Card stack array
*****************************************************************************************************/
CardStackArray::CardStackArray(size_t size)
{
	m_cards = new Card*[sizeof(Card) * size];
	
	for (size_t i = 0; i < size; i++)
		m_cards[i] = nullptr;
	
	m_maxSize = size;
	m_index = 0;
}

/*****************************************************************************************************
* Function: CardStackArray(const CardStackArray & csa)
* Purpose: Copy constructor
* Preconditon: No class object
* Postcondition: A new Card stack array copied from the passed Card stack array
*****************************************************************************************************/
CardStackArray::CardStackArray(const CardStackArray & csa)
{
	m_cards = new Card *[csa.m_maxSize];
	m_index = csa.m_index;
	m_maxSize = csa.m_maxSize;

	for (size_t i = 0; i < m_index; i++)
	{
		m_cards[i] = new Card(*csa.m_cards[i]);
	}
}

/*****************************************************************************************************
* Function: ~CardStackArray(void)
* Purpose: Destructor
* Preconditon: A Card stack array
* Postcondition: Frees all memory and deletes the current Card stack array
*****************************************************************************************************/
CardStackArray::~CardStackArray(void)
{
	Clear();
	delete[] m_cards;
	m_cards = nullptr;
}

/*****************************************************************************************************
* Function: operator=(const CardStackArray & csa)
* Purpose: Assignment operator
* Preconditon: Two Card stack arrays
* Postcondition: The current Card stack array is set equal to the passed Card stack array
*****************************************************************************************************/
CardStackArray & CardStackArray::operator=(const CardStackArray & csa)
{
	if (this != &csa)
	{
		Clear();
		delete[] m_cards;
		m_cards = nullptr;

		m_cards = new Card *[csa.m_maxSize];
		m_maxSize = csa.m_maxSize;
		m_index = csa.m_index;

		for (size_t i = 0; i < m_maxSize; i++)
		{
			m_cards[i] = new Card(*csa.m_cards[i]);
		}
	}
	return *this;
}

/*****************************************************************************************************
* Function: Push(const Card & card)
* Purpose: Pushes a copy of the passed card onto the stack array
* Preconditon: A Card stack array
* Postcondition: The current Card stack array with a copy of the passed Card pushed onto the stack
*****************************************************************************************************/
bool CardStackArray::Push(const Card & card)
{
	bool pushed = true;

	pushed = Push(card.GetCardRank(), card.GetCardSuit());

	return pushed;
}

/*****************************************************************************************************
* Function: Push(Card::CardRank rank, Card::CardSuit suit)
* Purpose: Pushes a new card onto the stack array
* Preconditon: A Card stack array
* Postcondition: The current Card stack array with a new Card pushed onto the stack
*****************************************************************************************************/
bool CardStackArray::Push(Card::CardRank rank, Card::CardSuit suit)
{
	bool pushed = true;

	if (IsFull() == true)
	{
		pushed = false;
	}

	else //if (pushed == true)
	{	
		//if (m_index == 0)
		//{  
		//	m_cards = new Card *[1];
		//	m_cards[0] = new Card(rank, suit);
		//	m_index++;
		//}
		//else
		{
			//Card **tempCards = new Card*[m_index + 1];
			//size_t tempMax = m_maxSize;
			//size_t tempCurr = m_index + 1;

			//for (size_t i = 0; i < (tempCurr - 1); i++)
			//{
			//	tempCards[i] = new Card(*m_cards[i]);
			//}

			m_cards[m_index++] = new Card(rank, suit);
			
			//Clear();
			//m_cards = tempCards;
			//m_maxSize = tempMax;
			//m_index = tempCurr;
		}
	}

	return pushed;
}

/*****************************************************************************************************
* Function: Pop(void)
* Purpose: Removes a card from the top of the stack array
* Preconditon: A Card stack array
* Postcondition: The current Card stack array with the Card on the top of the stack deleted
*****************************************************************************************************/
Card * CardStackArray::Pop(void)
{
	Card *card = nullptr;
	if (m_index > 0) 
	{
		card = m_cards[m_index - 1];
		m_cards[m_index - 1] = nullptr;
		m_index--;


		//Card **tempCards = new Card *[m_index - 1];
		//size_t tempMax = m_maxSize;
		//size_t tempCurr = m_index - 1;

		//if (m_cards[m_index - 1] != nullptr)
		//	card = new Card(*m_cards[m_index - 1]);

		//for (size_t i = 0; i < m_index - 1; i++)
		//{
		//	tempCards[i] = new Card(*m_cards[i]);
		//}

		//Clear();
		//m_cards = tempCards;
		//m_maxSize = tempMax;
		//m_index = tempCurr;
	}
	return card;
}

/*****************************************************************************************************
* Function: Peek(void) const
* Purpose: Checks the top card in the stack array
* Preconditon: A Card stack array
* Postcondition: The Card at the top of the current stack array
*****************************************************************************************************/
Card * CardStackArray::Peek(void) const
{
	Card *card = nullptr;
	if (m_index > 0)
		card = m_cards[m_index - 1];
	return card;
}

/*****************************************************************************************************
* Function: Clear(void)
* Purpose: Clears the stack array
* Preconditon: A Card stack array
* Postcondition: Memory freed and the current Card stack array deleted
*****************************************************************************************************/
void CardStackArray::Clear(void)
{
	//if (m_index != 0)
	{
		for(size_t i = 0; i < m_index; i++)
		{
			delete m_cards[i];
			m_cards[i] = nullptr;
		}

		//delete[] m_cards;
		//m_cards = nullptr;
		m_index = 0;
	}
}

/*****************************************************************************************************
* Function: Resize(size_t size)
* Purpose: Changes the size of the stack array
* Preconditon: A Card stack array
* Postcondition: The current card stack array made larger or smaller
*****************************************************************************************************/
bool CardStackArray::Resize(size_t size)
{
	bool affected = false;

	if (size > m_maxSize)
	{
		Card **newCards = new Card*[size];

		for (size_t i = 0; i < m_index; i++)
		{
			newCards[i] = m_cards[i];
		}
		delete[] m_cards;
		m_cards = newCards;
		m_maxSize = size;
	}
	else
	{
		Card **newCards = new Card*[size];
		size_t last = (size < m_index ? size : m_index);

		for (size_t i = 0; i < last; i++)
		{
			newCards[i] = m_cards[i];
		}
		for (size_t i = last; i < m_index; i++)
		{
			delete m_cards[i];
			affected = true;
		}
		delete[] m_cards;
		m_cards = newCards;
		m_index = last;
		m_maxSize = size;
	}


	//if (size < m_maxSize)
	//{
	//	int difference = m_maxSize - size;

	//	for (int i = 0; i < difference; i++)
	//	{
	//		Pop();
	//	}
	//	m_maxSize = size;
	//	affected = true;
	//}
	//else if (size > m_maxSize)
	//{
	//	m_maxSize = size;
	//	affected = false;
	//}

	return affected;
}

/*****************************************************************************************************
* Function: MaxSize(void) const
* Purpose: Returns the max size of the current stack array
* Preconditon: No access to private data members
* Postcondition: Max size of current array
*****************************************************************************************************/
size_t CardStackArray::MaxSize(void) const
{
	return m_maxSize;
}

/*****************************************************************************************************
* Function: CurrSize(void) const
* Purpose: Returns the current size of the current stack array
* Preconditon: No access to private data members
* Postcondition: Current size of current array
*****************************************************************************************************/
size_t CardStackArray::CurrSize(void) const
{
	return m_index;
}

/*****************************************************************************************************
* Function: IsFull(void) const
* Purpose: Checks if the current stack array is full
* Preconditon: A Card stack array
* Postcondition: If the current size equals the max size then the array is full
*****************************************************************************************************/
bool CardStackArray::IsFull(void) const
{
	bool full = false;

	if (m_index >= m_maxSize)
		full = true;

	return full;
}

/*****************************************************************************************************
* Function: Display(bool topToBotton) const
* Purpose: Displays the current stack array
* Preconditon: A Card stack array
* Postcondition: Output of the Cards in the current Card stack array
*****************************************************************************************************/
void CardStackArray::Display(bool topToBotton) const
{
	if (topToBotton == true)
	{
		if (m_index > 0)
		{
			int travSize = m_index - 1;
			Card *travel = m_cards[travSize];
			while (travSize >= 0)
			{
				travel->Display();
				travSize--;
				travel = m_cards[travSize];
			}
		}
	}
	else
	{
		size_t travSize = 0;
		Card *travel = m_cards[0];
		while (travSize < m_index)
		{
			travel->Display();
			travSize++;
			travel = m_cards[travSize];
		}
	}
}

/****************************************************************************************************
* Author: Zak Rowland
* Filename: Card.cpp
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
#include "Card.h"
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: Card(void)
* Purpose: Default constructor
* Preconditon: No class object
* Postcondition: A new Card object with default values
*****************************************************************************************************/
Card::Card(void) : Card(ACE, CLUBS)
{
	//empty
}

/*****************************************************************************************************
* Function: Card(CardRank cardRank, CardSuit cardSuit)
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new Card object with values provided
*****************************************************************************************************/
Card::Card(CardRank cardRank, CardSuit cardSuit)
{
	m_cardRank = cardRank;
	m_cardSuit = cardSuit;
}

/*****************************************************************************************************
* Function: Card(const Card & card)
* Purpose: Copy constructor
* Preconditon: A Card object to be copied
* Postcondition: A copy of the passed Card object
*****************************************************************************************************/
Card::Card(const Card & card) : Card(card.m_cardRank, card.m_cardSuit)
{
}

/*****************************************************************************************************
* Function: ~Card(void)
* Purpose: Destructor
* Preconditon: A Card object
* Postcondition: No class object
*****************************************************************************************************/
Card::~Card(void)
{
	//empty
}

/*****************************************************************************************************
* Function: Equal(const Card & card) const
* Purpose: Determine if 2 Card objects represent the same rank and suit
* Preconditon: An internal Card object and a passed Card object
* Postcondition: A comparison of the two objects
*****************************************************************************************************/
bool Card::Equal(const Card & card) const
{
	bool equal = false;

	if (Compare(card) == 0)
		equal = true;

	return equal;
}

/*****************************************************************************************************
* Function: Equal(CardRank cardRank, CardSuit cardSuit) const
* Purpose: Determine if 2 Card objects represent the same rank and suit
* Preconditon: An internal Card object and a passed Card object
* Postcondition: A comparison of the two objects
*****************************************************************************************************/
bool Card::Equal(CardRank cardRank, CardSuit cardSuit) const
{
	Card temp = Card(cardRank, cardSuit);

	return Equal(temp);
}

/*****************************************************************************************************
* Function: Compare(const Card & card) const
* Purpose: Compares the rank and/or suit of two Card objects
* Preconditon: Two Card objects
* Postcondition: The result of the comparison
*****************************************************************************************************/
int Card::Compare(const Card & card) const
{
	int comparison = 0;

	if (m_cardRank == card.m_cardRank)
		comparison = strcmp(GetSuitStr(), card.GetSuitStr());
	else
	{
		if (m_cardRank > card.m_cardRank)
			comparison = 1;
		else
			comparison = -1;
	}
	return comparison;
}

/*****************************************************************************************************
* Function: GetCardRank(void) const
* Purpose: Returns the Card object's rank
* Preconditon: No access to private data members
* Postcondition: The Card object's rank
*****************************************************************************************************/
Card::CardRank Card::GetCardRank(void) const
{
	return m_cardRank;
}

/*****************************************************************************************************
* Function: GetCardSuit(void) const
* Purpose: Returns the Card object's suit
* Preconditon: No access to private data members
* Postcondition: The Card object's suit
*****************************************************************************************************/
Card::CardSuit Card::GetCardSuit(void) const
{
	return m_cardSuit;
}

/*****************************************************************************************************
* Function: SetCard(CardRank rank, CardSuit suit)
* Purpose: Sets the rank and suit of the Card object
* Preconditon: A Card object
* Postcondition: A Card object with the values passed
*****************************************************************************************************/
void Card::SetCard(CardRank rank, CardSuit suit)
{
	m_cardRank = rank;
	m_cardSuit = suit;
}

/*****************************************************************************************************
* Function: GetRankStr(void) const
* Purpose: Returns the string that corresponds to the rank enumeration
* Preconditon: A rank with an integer value
* Postcondition: A string of the rank
*****************************************************************************************************/
const char * Card::GetRankStr(void) const
{
	return CardRankStr[m_cardRank];
}

/*****************************************************************************************************
* Function: GetSuitStr(void) const
* Purpose: Returns the string that corresponds to the suit enumeration
* Preconditon: A suit with an integer value
* Postcondition: A string of the suit
*****************************************************************************************************/
const char * Card::GetSuitStr(void) const
{
	return CardSuitStr[m_cardSuit];
}

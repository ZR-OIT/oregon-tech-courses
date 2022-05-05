/****************************************************************************************************
* Author: Zak Rowland
* Filename: CardNode.cpp
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
#include "CardNode.h"
using std::cout;
using std::cin;
using std::endl;

/*****************************************************************************************************
* Function: CardNode(Card::CardRank cardRank, Card::CardSuit cardSuit)
* Purpose: Overloaded constructor
* Preconditon: No class object
* Postcondition: A new Card node object with values provided
*****************************************************************************************************/
CardNode::CardNode(Card::CardRank cardRank, Card::CardSuit cardSuit)
{
	m_card = new Card(cardRank, cardSuit);
	m_next = nullptr;
	m_prev = nullptr;
}

/*****************************************************************************************************
* Function: CardNode(const CardNode & node)
* Purpose: Copy constructor
* Preconditon: A node to be copied
* Postcondition: A copy of the passed node
*****************************************************************************************************/
CardNode::CardNode(const CardNode & node) : CardNode(node.m_card->GetCardRank(), node.m_card->GetCardSuit())
{
}

/*****************************************************************************************************
* Function: operator=(const CardNode & node)
* Purpose: Assignment operator
* Preconditon: A node object
* Postcondition: A node object equal to the passed node
*****************************************************************************************************/
CardNode & CardNode::operator=(const CardNode & node)
{
	if (this != &node)
	{
		m_card->SetCard(node.m_card->GetCardRank(), node.m_card->GetCardSuit());
	}
	return *this;
}

/*****************************************************************************************************
* Function: ~CardNode(void)
* Purpose: Destructor
* Preconditon: A node object
* Postcondition: Node object deleted
*****************************************************************************************************/
CardNode::~CardNode(void)
{
	//empty
	delete m_card;
}

/*****************************************************************************************************
* Function: SetNext(CardNode * next)
* Purpose: Sets a pointer to the next Card node
* Preconditon: A node object
* Postcondition: A node object with a next pointer to the passed node
*****************************************************************************************************/
void CardNode::SetNext(CardNode * next)
{
	m_next = next;
}

/*****************************************************************************************************
* Function: SetPrev(CardNode * prev)
* Purpose: Sets a pointer to the previous Card node
* Preconditon: A node object
* Postcondition: A node object with a prev pointer to the passed node
*****************************************************************************************************/
void CardNode::SetPrev(CardNode * prev)
{
	m_prev = prev;
}

/*****************************************************************************************************
* Function: GetNext(void) const
* Purpose: Returns a pointer to the next Card node
* Preconditon: No access to private data members
* Postcondition: A pointer to the next node
*****************************************************************************************************/
CardNode * CardNode::GetNext(void) const
{
	return m_next;
}

/*****************************************************************************************************
* Function: GetPrev(void) const
* Purpose: Returns a pointer to the previous Card node
* Preconditon: No access to private data members
* Postcondition: A pointer to the previous node
*****************************************************************************************************/
CardNode * CardNode::GetPrev(void) const
{
	return m_prev;
}

/*****************************************************************************************************
* Function: GetCard(void) const
* Purpose: Returns a pointer to the Card within the node
* Preconditon: No access to private data members
* Postcondition: A pointer to the Card object
*****************************************************************************************************/
Card * CardNode::GetCard(void) const
{
	return m_card;
}

/*****************************************************************************************************
* Function: NullCard(void)
* Purpose: Sets the value of m_card to nullptr
* Preconditon: A node object
* Postcondition: A node object with m_card set to nullptr
*****************************************************************************************************/
void CardNode::NullCard(void)
{
	m_card = nullptr;
}
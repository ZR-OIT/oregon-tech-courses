#pragma once

#ifndef CARDNODE_H
# define CARDNODE_H

#include "Card.h"

class CardStackList;

class CardNode
{
public:
	// The default ctor for the node class.
	// Notice how you can use the values from the Card::CardRank and
	// Card::CardSuit enumerarions with specifying the name of the enum.
	CardNode(Card::CardRank cardRank = Card::ACE, Card::CardSuit cardSuit = Card::SPADES);

	// Copy ctor.
	CardNode(const CardNode &node);

	// Assignment op.
	CardNode &operator=(const CardNode &node);

	// This dtor does need to be implemented. The CardNode does allocate resources.
	~CardNode(void);

	// A stack represented as a list is a doubly linked list.
	// These methods (SetNext, SetPrev, GetNext, GetPrev) should only
	// be used in the testing code in main.cpp. They should not be used in
	// the CardStackList.cpp file. Use the friend access in the CardStackList.cpp
	// instead.
	void SetNext(CardNode *next);
	void SetPrev(CardNode *prev);

	CardNode * GetNext(void) const;
	CardNode * GetPrev(void) const;

	// Return the pointer to the Card in the node.
	// This method (Getcard) should only be used in the testing code in main.cpp. 
	// It should not be used in the CardStackList.cpp file. Use the friend 
	// access in the CardStackList.cpp
	// instead. 
	Card *GetCard(void) const;

	// Set the value of m_card to nullptr. Calling this method _does not_
	// delete the m_card data memeber, just sets it to nullptr.
	// This method (NullCard) should only be used in the testing code in main.cpp. 
	// It should not be used in the CardStackList.cpp file. Use the friend 
	// access in the CardStackList.cpp
	void NullCard(void);

	// Because we are using CardList as a friend, we do not need to have
	// the Display() in CardNode call the Display method in Card. We can
	// call the Display method in Card directly from the CardList class,
	// because CardList is a friend to Card.
	//void Display(void) const;

	friend class CardStackList;

private:
	Card * m_card;
	
	CardNode *m_next;
	CardNode *m_prev;
};

#endif // CARDNODE_H

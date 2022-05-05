#pragma once

#ifndef CARDSTACKLIST_H
# define CARDSTACKLIST_H

#include "CardNode.h"

class CardStackList
{
public:
	// Default constructor.
	CardStackList(size_t size = STACK_LIST_DEFAULT_SIZE);

	// Copy constructor.
	CardStackList(const CardStackList &csa);

	// dtor
	~CardStackList(void);

	// Assignment operator.
	CardStackList &operator=(const CardStackList &csa);

	// If the Push is successful, return true. If the stack is full
	// return false. When calling Push(Card &card), a __copy__ of card is
	// pushed onto the stack.
	bool Push(Card &card);
	bool Push(Card::CardRank rank, Card::CardSuit suit);

	// A call to Pop() removes the Card that is the top of the stack
	// from the CardStackList. A pointer to the Card object from the removed
	// CardNode is returned. Since the Card was removed from the stack
	// you must delete it on your own in your code (or test suite).
	Card *Pop(void);

	// A call to Peek returns a pointer to the Card that is on top of
	// the CardStackArray. The Card is NOT removed from the stack.
	Card *Peek(void) const;

	// Clear out all Cards from the stack.
	void Clear(void);

	// If the size was made smaller and Cards were deleted, return false.
	// If you're going to truncate Cards from the stack (and loose them), then 
	// truncate the most recently Push-ed Cards from the stack. The Cards
	// that have been in the stack the longest will be retained.
	bool Resize(size_t size = STACK_LIST_DEFAULT_SIZE);

	// What is the maximum number of cards that can be pushed onto this
	// the stack?
	size_t MaxSize(void) const;

	// How many cards are currently on the stack?
	size_t CurrSize(void) const;

	// Is the stack at its capacity?
	bool IsFull(void) const;

	void Display(bool topToBotton = true) const;

private:

	CardNode *m_head;
	CardNode *m_tail;

	size_t m_maxSize;

	// For me, m_index always represents the number of Cards I have
	// in the stack.
	size_t m_index;

	static const size_t STACK_LIST_DEFAULT_SIZE = 10;
};

#endif // CARDSTACKLIST_H

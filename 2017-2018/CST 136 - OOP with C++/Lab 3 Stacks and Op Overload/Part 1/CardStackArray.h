#pragma once

#ifndef CARDSTACKARRAY_H
# define CARDSTACKARRAY_H

# include <cstring>

// There is no need to include the CardNode.h file for the stack
// implemented as an array.
# include "Card.h"

class CardStackArray
{
public:
	// Default constructor.
	CardStackArray(size_t size = STACK_ARRAY_DEFAULT_SIZE);

	// Copy constructor.
	CardStackArray(const CardStackArray &csa);

	// dtor
	~CardStackArray(void);

	// Assignment operator.
	CardStackArray &operator=(const CardStackArray &csa);

	// If the Push is successful, return true. If the stack is full
	// return false. If calling Push(Card &card), a copy of card is
	// pushed onto the stack.
	bool Push(const Card &card);
	bool Push(Card::CardRank rank, Card::CardSuit suit);

	// A call to Pop() removes the book that is the top of the stack
	// from the CardStackArray. A pointer to the Card from the removed
	// CardNode is returned. Since the Card was removed from the stack
	// you must delete it.
	Card *Pop(void);

	// A call to Peek returns a pointer to the Card that is on top of
	// the CardStackArray. The Card is NOT removed from the stack.
	Card *Peek(void) const;

	// Clear out all Cards from the stack.
	void Clear(void);

	// If the size was made smaller and Cards were deleted, return false.
	// If you're going to truncate Cards from the stack (and loose them), then 
	// truncate the most recently Push-ed Cards from the stack. The Cards
	// that have been in the stack the longest will be kept.
	bool Resize(size_t size = STACK_ARRAY_DEFAULT_SIZE);

	// What is the maximum number of cards that can be pushed onto the
	// the stack?
	size_t MaxSize(void) const;

	// How many cards are currently on the stack?
	size_t CurrSize(void) const;

	// Is the stack at its capacity?
	bool IsFull(void) const;

	void Display(bool topToBotton = true) const;

private:

	// An array of pointers to Card data types that are in the
	// stack.
	Card **m_cards;

	size_t m_maxSize;

	// For me, m_index always represents the number of Cards I have
	// in the stack.
	size_t m_index;

	static const size_t STACK_ARRAY_DEFAULT_SIZE = 10;
};

#endif // CARDSTACKARRAY_H

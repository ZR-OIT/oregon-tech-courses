#pragma once
#ifndef DECK_H

# define DECK_H
# define _CRT_SECURE_NO_WARNINGS
# include <iostream>
# include <iomanip>
# include "Card.h"
using std::cout;
using std::left;
using std::setw;
using std::endl;

class Deck
{
public:
	enum CardRank : uint8_t {
		ACE = 1
		, TWO
		, THREE
		, FOUR
		, FIVE
		, SIX
		, SEVEN
		, EIGHT
		, NINE
		, TEN
		, JACK
		, QUEEN
		, KING
	};
	enum CardSuit : uint8_t {
		CLUBS = 1
		, DIAMONDS
		, HEARTS
		, SPADES
	};

	CardRank ranks[13] = { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
		EIGHT, NINE, TEN, JACK, QUEEN, KING };

	CardSuit suits[4] = { CLUBS, DIAMONDS, HEARTS, SPADES };

	Deck(size_t amount);
	Deck(const Deck &deck);
	~Deck(void);
	Deck &operator=(const Deck &deck);
	void Shuffle(void);
	Card *Draw(void);
	Card *Peek(void) const;
	void Clear(void);
	size_t MaxSize(void) const;
	size_t CurrSize(void) const;
	bool IsFull(void) const;
private:
	Deck(void);

	Card ** m_cards;
	size_t m_maxSize;
	size_t m_index;
	static const size_t DECK_SIZE = 52;
};

#endif // DECK_H
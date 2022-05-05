#pragma once

#ifndef HAND_H
# define HAND_H
# define _CRT_SECURE_NO_WARNINGS
# include "Card.h"

class Hand
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

	Hand(void);
	Hand(const Hand &hand);
	Hand &operator=(const Hand &hand);
	~Hand(void);
	void Add(Card *card, bool face_up);
	void FlipAll(void);
	void Display(void);
	void Clear(void);
	int GetHandValue(void);
	int GetAceValue(void);
	int GetCount(void);
private:
	Card ** m_cards;
	int m_count;
	int m_handValue;
	int m_aceValue;
};

#endif // HAND_H

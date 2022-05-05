#pragma once
#ifndef CARD_H

# define CARD_H
# define _CRT_SECURE_NO_WARNINGS
# include <iostream>
# include <iomanip>
using std::cout;
using std::left;
using std::setw;
using std::endl;

class Card
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

	static constexpr const char *rank_strings[14] = {
		"" // an empty placeholder
		, "Ace"
		, "Two"
		, "Three"
		, "Four"
		, "Five"
		, "Six"
		, "Seven"
		, "Eight"
		, "Nine"
		, "Ten"
		, "Jack"
		, "Queen"
		, "King"
	};
	static constexpr const char *suit_strings[5] = {
		"" // an empty placeholder
		, "Clubs"
		, "Diamonds"
		, "Hearts"
		, "Spades"
	};

	Card(void);
	Card(CardRank cardRank, CardSuit cardSuit);
	Card(const Card &card);
	virtual
		~Card(void);
	Card &operator=(const Card &card);

	int Compare(const Card &card) const;

	Card::CardRank GetCardRank(void) const;
	Card::CardSuit GetCardSuit(void) const;

	void SetCard(CardRank rank, CardSuit suit);

	const char * GetRankStr(void) const;
	const char * GetSuitStr(void) const;

	virtual void Display(void) const = 0;
	virtual void Flip(void) = 0;

	virtual int GetValue(void) = 0;
	virtual void SetValue(int value) = 0;
	virtual bool GetFace(void) = 0;
	virtual void SetFace(bool face_up) = 0;
private:
	CardRank m_cardRank;
	CardSuit m_cardSuit;
};

#endif // CARD_H

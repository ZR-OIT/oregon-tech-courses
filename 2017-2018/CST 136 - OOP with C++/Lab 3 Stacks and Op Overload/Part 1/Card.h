#pragma once

#ifndef CARD_H
# define CARD_H

# include <cstdint>
# include <iostream>
# include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::left;

class Card
{
public:
	// We place the enum within the class for Card so that the names
	// in the enum have a scope strictly within the class.
	// We could also consider this encapsulation. We want the Card class
	// to contain all the things necessary, the enum is necessary.
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

	// In the same way that the enumerations are part of the
	// encapsulation for the Card class, the strings that represent
	// the enum names are also part of the class.
	static constexpr const char *CardRankStr[14] = {
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
	static constexpr const char *CardSuitStr[5] = {
		"" // an empty placeholder
		, "Clubs"
		, "Diamonds"
		, "Hearts"
		, "Spades"
	};

	// We, finally, have a true default ctor.
	// If the default ctor is called, it needs to call the ctor below with
	// a Card rank of ACE and a Card suit of CLUBS.
	Card(void);

	// This is the ctor we expect to normall call.
	Card(CardRank cardRank, CardSuit cardSuit);

	// The copy ctor.
	Card(const Card &card);

	// The dtor is very simple. Since a card does not have any allocated
	// resources, we could get away without defining our own dtor, the
	// default one provided by the compiler would be fine. However, WE
	// like to leave no dtor undefined.
	~Card(void);

	// The assignment operator.
	// We don't need this operator for this assignment.
	//Card &operator=(const Card &card);

	// So that we can all have output that looks the same.
	void Display(void) const
	{
		cout << left << setw(6) << CardRankStr[m_cardRank] << "    "
			<< setw(8) << CardSuitStr[m_cardSuit] << endl;
	}

	// Determine is 2 Card objects represent the same rank and suit.
	bool Equal(const Card &card) const;
	bool Equal(CardRank cardRank, CardSuit cardSuit) const;

	// Determine is 2 Card objects to see which one has a "higher" value.
	// For this implementation, we are going to make the ACE the lowest
	// value rank and the KING the highest value rank.
	// CLUBS is the lowest value suit and SPADES is the highest value suit.
	// The values of rank and suit can be easly determined using the enumerations
	// defined above. This is a standard ordering of suits used in the card
	// game of bridge. It also happens to be alphabetical.
	// When comparing cards, we will first compare the rank. If the rank values
	// are the same, we will compare the suit.
	int Compare(const Card &card) const;

	Card::CardRank GetCardRank(void) const;
	Card::CardSuit GetCardSuit(void) const;

	// Set the values in a card to new values.
	// We should probably consider a Card to be immutable, but we will leave
	// that to another assignment.
	void SetCard(CardRank rank, CardSuit suit);

	// Return the rank/suit for a given card as cStrings.
	const char * GetRankStr(void) const;
	const char * GetSuitStr(void) const;

private:

	CardRank m_cardRank;
	CardSuit m_cardSuit;
};

#endif // CARD_H

#include "NumberCard.h"
/****************************************************************************************************
* Author: Zak Rowland
* Filename: main.cpp
* Date Created: 5/10/2018
* Modifications:
*****************************************************************************************************
* Assignment: Blackjack - Lab 6
*
* Overview: Create the game of Blackjack (21) using multple different classes, some derived.
*
* Input: User input menu choices
*
* Output: A game of Blackjack!
*
*****************************************************************************************************/

NumberCard::NumberCard(void) : Card(), m_actualValue(0), m_faceUp(true)
{
//empty
}

NumberCard::NumberCard(CardRank cardRank, CardSuit cardSuit, bool up, int value) : Card(cardRank, cardSuit), m_actualValue(value), m_faceUp(up)
{
}

NumberCard::NumberCard(const NumberCard & card) : Card(card), m_actualValue(card.m_actualValue), m_faceUp(card.m_faceUp)
{
}

NumberCard & NumberCard::operator=(const NumberCard & card)
{
	if (this != &card)
	{
		Card::operator=(card);
		m_actualValue = card.m_actualValue;
		m_faceUp = card.m_faceUp;
	}
	return *this;
}

NumberCard::~NumberCard(void)
{
	//empty
}

void NumberCard::Display(void) const
{
	if (m_faceUp == true)
	{
		if (GetCardSuit() == SPADES)
		{
			if (GetCardRank() == TWO)
			{
				cout << ascii_spades[0];
			}
			else if (GetCardRank() == THREE)
			{
				cout << ascii_spades[1];
			}
			else if (GetCardRank() == FOUR)
			{
				cout << ascii_spades[2];
			}
			else if (GetCardRank() == FIVE)
			{
				cout << ascii_spades[3];
			}
			else if (GetCardRank() == SIX)
			{
				cout << ascii_spades[4];
			}
			else if (GetCardRank() == SEVEN)
			{
				cout << ascii_spades[5];
			}
			else if (GetCardRank() == EIGHT)
			{
				cout << ascii_spades[6];
			}
			else if (GetCardRank() == NINE)
			{
				cout << ascii_spades[7];
			}
			else if (GetCardRank() == TEN)
			{
				cout << ascii_spades[8];
			}
		}
		else if (GetCardSuit() == DIAMONDS)
		{
			if (GetCardRank() == TWO)
			{
				cout << ascii_diamonds[0];
			}
			else if (GetCardRank() == THREE)
			{
				cout << ascii_diamonds[1];
			}
			else if (GetCardRank() == FOUR)
			{
				cout << ascii_diamonds[2];
			}
			else if (GetCardRank() == FIVE)
			{
				cout << ascii_diamonds[3];
			}
			else if (GetCardRank() == SIX)
			{
				cout << ascii_diamonds[4];
			}
			else if (GetCardRank() == SEVEN)
			{
				cout << ascii_diamonds[5];
			}
			else if (GetCardRank() == EIGHT)
			{
				cout << ascii_diamonds[6];
			}
			else if (GetCardRank() == NINE)
			{
				cout << ascii_diamonds[7];
			}
			else if (GetCardRank() == TEN)
			{
				cout << ascii_diamonds[8];
			}
		}
		else if (GetCardSuit() == CLUBS)
		{
			if (GetCardRank() == TWO)
			{
				cout << ascii_clubs[0];
			}
			else if (GetCardRank() == THREE)
			{
				cout << ascii_clubs[1];
			}
			else if (GetCardRank() == FOUR)
			{
				cout << ascii_clubs[2];
			}
			else if (GetCardRank() == FIVE)
			{
				cout << ascii_clubs[3];
			}
			else if (GetCardRank() == SIX)
			{
				cout << ascii_clubs[4];
			}
			else if (GetCardRank() == SEVEN)
			{
				cout << ascii_clubs[5];
			}
			else if (GetCardRank() == EIGHT)
			{
				cout << ascii_clubs[6];
			}
			else if (GetCardRank() == NINE)
			{
				cout << ascii_clubs[7];
			}
			else if (GetCardRank() == TEN)
			{
				cout << ascii_clubs[8];
			}
		}
		else //HEARTS
		{
			if (GetCardRank() == TWO)
			{
				cout << ascii_hearts[0];
			}
			else if (GetCardRank() == THREE)
			{
				cout << ascii_hearts[1];
			}
			else if (GetCardRank() == FOUR)
			{
				cout << ascii_hearts[2];
			}
			else if (GetCardRank() == FIVE)
			{
				cout << ascii_hearts[3];
			}
			else if (GetCardRank() == SIX)
			{
				cout << ascii_hearts[4];
			}
			else if (GetCardRank() == SEVEN)
			{
				cout << ascii_hearts[5];
			}
			else if (GetCardRank() == EIGHT)
			{
				cout << ascii_hearts[6];
			}
			else if (GetCardRank() == NINE)
			{
				cout << ascii_hearts[7];
			}
			else if (GetCardRank() == TEN)
			{
				cout << ascii_hearts[8];
			}
		}
	}
	else
	{
		cout << ascii_facedown;
	}
}

void NumberCard::Flip(void)
{
	m_faceUp = !m_faceUp;
}

int NumberCard::GetValue(void)
{
	return m_actualValue;
}

void NumberCard::SetValue(int value)
{
	m_actualValue = value;
}

bool NumberCard::GetFace(void)
{
	return m_faceUp;
}

void NumberCard::SetFace(bool face_up)
{
	m_faceUp = face_up;
}

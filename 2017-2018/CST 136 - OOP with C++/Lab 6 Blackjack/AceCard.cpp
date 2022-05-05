#include "AceCard.h"
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

AceCard::AceCard(void) : Card(), m_actualValue(0), m_faceUp(true)
{
}

AceCard::AceCard(CardRank cardRank, CardSuit cardSuit, bool up, int value) : Card(cardRank, cardSuit), m_actualValue(value), m_faceUp(up)
{
}

AceCard::AceCard(const AceCard & card) : Card(card), m_actualValue(card.m_actualValue), m_faceUp(card.m_faceUp)
{
}

AceCard & AceCard::operator=(const AceCard & card)
{
	if (this != &card)
	{
		Card::operator=(card);
		m_actualValue = card.m_actualValue;
		m_faceUp = card.m_faceUp;
	}
	return *this;
}

AceCard::~AceCard(void)
{
	m_actualValue = 0;
	m_faceUp = false;
}

void AceCard::Display(void) const
{
	if (m_faceUp == true)
	{
		if (GetCardSuit() == SPADES)
		{
			cout << ascii_spades;
		}
		else if (GetCardSuit() == DIAMONDS)
		{
			cout << ascii_diamonds;
		}
		else if (GetCardSuit() == CLUBS)
		{
			cout << ascii_clubs;
		}
		else //HEARTS
		{
			cout << ascii_hearts;
		}
	}
	else
	{
		cout << ascii_facedown;
	}
}

void AceCard::Flip(void)
{
	m_faceUp = !m_faceUp;
}

int AceCard::GetValue(void)
{
	return m_actualValue;
}

void AceCard::SetValue(int value)
{
	m_actualValue = value;
}

bool AceCard::GetFace(void)
{
	return m_faceUp;
}

void AceCard::SetFace(bool face_up)
{
	m_faceUp = face_up;
}

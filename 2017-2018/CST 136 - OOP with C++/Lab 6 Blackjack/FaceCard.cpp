#include "FaceCard.h"
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

FaceCard::FaceCard(void) : Card(), m_actualValue(0), m_faceUp(true)
{
	//empty
}

FaceCard::FaceCard(CardRank cardRank, CardSuit cardSuit, bool up) : Card(cardRank, cardSuit), m_actualValue(10), m_faceUp(up)
{
}

FaceCard::FaceCard(const FaceCard & card) : Card(card), m_actualValue(card.m_actualValue), m_faceUp(card.m_faceUp)
{
}

FaceCard & FaceCard::operator=(const FaceCard & card)
{
	if (this != &card)
	{
		Card::operator=(card);
		m_actualValue = card.m_actualValue;
		m_faceUp = card.m_faceUp;
	}
	return *this;
}

FaceCard::~FaceCard(void)
{
	//empty
}

void FaceCard::Display(void) const
{
	if (m_faceUp == true)
	{
		if (GetCardSuit() == SPADES)
		{
			if (GetCardRank() == JACK)
			{
				cout << ascii_spades[0];
			}
			else if (GetCardRank() == QUEEN)
			{
				cout << ascii_spades[1];
			}
			else if (GetCardRank() == KING)
			{
				cout << ascii_spades[2];
			}
		}
		else if (GetCardSuit() == DIAMONDS)
		{
			if (GetCardRank() == JACK)
			{
				cout << ascii_diamonds[0];
			}
			else if (GetCardRank() == QUEEN)
			{
				cout << ascii_diamonds[1];
			}
			else if (GetCardRank() == KING)
			{
				cout << ascii_diamonds[2];
			}
		}
		else if (GetCardSuit() == CLUBS)
		{
			if (GetCardRank() == JACK)
			{
				cout << ascii_clubs[0];
			}
			else if (GetCardRank() == QUEEN)
			{
				cout << ascii_clubs[1];
			}
			else if (GetCardRank() == KING)
			{
				cout << ascii_clubs[2];
			}
		}
		else //HEARTS
		{
			if (GetCardRank() == JACK)
			{
				cout << ascii_hearts[0];
			}
			else if (GetCardRank() == QUEEN)
			{
				cout << ascii_hearts[2];
			}
			else if (GetCardRank() == KING)
			{
				cout << ascii_hearts[2];
			}
		}	
	}
	else
	{
		cout << ascii_facedown;
	}
}

void FaceCard::Flip(void)
{
	m_faceUp = !m_faceUp;
}

int FaceCard::GetValue(void)
{
	return m_actualValue;
}

void FaceCard::SetValue(int value)
{
	m_actualValue = value;
}

bool FaceCard::GetFace(void)
{
	return m_faceUp;
}

void FaceCard::SetFace(bool face_up)
{
	m_faceUp = face_up;
}

#include "Hand.h"
#include "AceCard.h"
#include "FaceCard.h"
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

Hand::Hand(void)
{
	m_cards = nullptr;
	m_count = 0;
	m_handValue = 0;
	m_aceValue = 0;
}

Hand::Hand(const Hand & hand)
{
	m_count = hand.m_count;
	m_handValue = hand.m_handValue;
	m_aceValue = hand.m_aceValue;

	for (size_t c = 0; c < m_count; c++)
	{
		if (hand.m_cards[c]->GetCardRank() == ACE)
		{
			m_cards[c] = new AceCard(Card::CardRank(ACE), Card::CardSuit(hand.m_cards[c]->GetCardSuit()), hand.m_cards[c]->GetFace(), 1);
		}
		else if (hand.m_cards[c]->GetCardRank() == JACK || hand.m_cards[c]->GetCardRank() == QUEEN || hand.m_cards[c]->GetCardRank() == KING)
		{
			m_cards[c] = new FaceCard(Card::CardRank(hand.m_cards[c]->GetCardRank()), Card::CardSuit(hand.m_cards[c]->GetCardSuit()), hand.m_cards[c]->GetFace());
		}
		else
		{
			m_cards[c] = new NumberCard(Card::CardRank(hand.m_cards[c]->GetCardRank()), Card::CardSuit(hand.m_cards[c]->GetCardSuit()), hand.m_cards[c]->GetCardRank(), hand.m_cards[c]->GetFace());
		}
	}
}

Hand & Hand::operator=(const Hand & hand)
{
	if (this != &hand)
	{
		if (m_count > 0)
		{
			Clear();
			delete m_cards;
		}

		m_count = hand.m_count;
		m_handValue = hand.m_handValue;
		m_aceValue = hand.m_aceValue;
		m_cards = new Card*[sizeof(Card) * m_count];

		for (size_t c = 0; c < m_count; c++)
		{
			if (hand.m_cards[c]->GetCardRank() == ACE)
			{
				m_cards[c] = new AceCard(Card::CardRank(ACE), Card::CardSuit(hand.m_cards[c]->GetCardSuit()), hand.m_cards[c]->GetFace(), 1);
			}
			else if (hand.m_cards[c]->GetCardRank() == JACK || hand.m_cards[c]->GetCardRank() == QUEEN || hand.m_cards[c]->GetCardRank() == KING)
			{
				m_cards[c] = new FaceCard(Card::CardRank(hand.m_cards[c]->GetCardRank()), Card::CardSuit(hand.m_cards[c]->GetCardSuit()), hand.m_cards[c]->GetFace());
			}
			else
			{
				m_cards[c] = new NumberCard(Card::CardRank(hand.m_cards[c]->GetCardRank()), Card::CardSuit(hand.m_cards[c]->GetCardSuit()), hand.m_cards[c]->GetFace(), hand.m_cards[c]->GetCardRank());
			}
		}
	}
	return *this;
}

Hand::~Hand(void)
{
	Clear();
	delete[] m_cards;
	m_cards = nullptr;
}

void Hand::Add(Card * card, bool face_up)
{
	if (m_count == 0)
	{
		m_cards = new Card *[1];

		if (card->GetCardRank() == ACE)
		{
			m_cards[m_count] = new AceCard(Card::CardRank(ACE), Card::CardSuit(card->GetCardSuit()), face_up, 1);
			m_handValue += 1;
			m_aceValue += 11;
		}
		else if (card->GetCardRank() == JACK || card->GetCardRank() == QUEEN || card->GetCardRank() == KING)
		{
			m_cards[m_count] = new FaceCard(Card::CardRank(card->GetCardRank()), Card::CardSuit(card->GetCardSuit()), face_up);
			m_handValue += 10;
			m_aceValue += 10;
		}
		else
		{
			m_cards[m_count] = new NumberCard(Card::CardRank(card->GetCardRank()), Card::CardSuit(card->GetCardSuit()), face_up, card->GetCardRank());
			m_handValue += card->GetCardRank();
			m_aceValue += card->GetCardRank();
		}
		m_count++;
	}
	else
	{
		Card ** temp = new Card*[m_count + 1];
		int temp_count = m_count + 1;
		int temp_hand = 0;
		int temp_ace = 0;
		
		if (face_up == false)
		{
			for (int i = 0; i < temp_count - 1; i++)
			{
				if (m_cards[i]->GetCardRank() == ACE)
				{
					temp[i] = new AceCard(Card::CardRank(ACE), Card::CardSuit(m_cards[i]->GetCardSuit()), !face_up, 1);
					temp_hand += 1;
					temp_ace += 11;
				}
				else if (m_cards[i]->GetCardRank() == JACK || m_cards[i]->GetCardRank() == QUEEN || m_cards[i]->GetCardRank() == KING)
				{
					temp[i] = new FaceCard(Card::CardRank(m_cards[i]->GetCardRank()), Card::CardSuit(m_cards[i]->GetCardSuit()), !face_up);
					temp_hand += 10;
					temp_ace += 10;
				}
				else
				{
					temp[i] = new NumberCard(Card::CardRank(m_cards[i]->GetCardRank()), Card::CardSuit(m_cards[i]->GetCardSuit()), !face_up, m_cards[i]->GetCardRank());
					temp_hand += m_cards[i]->GetCardRank();
					temp_ace += m_cards[i]->GetCardRank();
				}
			}

			if (card->GetCardRank() == ACE)
			{
				temp[temp_count - 1] = new AceCard(Card::CardRank(ACE), Card::CardSuit(card->GetCardSuit()), face_up, 1);
			}
			else if (card->GetCardRank() == JACK || card->GetCardRank() == QUEEN || card->GetCardRank() == KING)
			{
				temp[temp_count - 1] = new FaceCard(Card::CardRank(card->GetCardRank()), Card::CardSuit(card->GetCardSuit()), face_up);
			}
			else
			{
				temp[temp_count - 1] = new NumberCard(Card::CardRank(card->GetCardRank()), Card::CardSuit(card->GetCardSuit()), face_up, card->GetCardRank());
			}
		}
		else
		{
			for (int i = 0; i < temp_count - 1; i++)
			{
				if (m_cards[i]->GetCardRank() == ACE)
				{
					temp[i] = new AceCard(Card::CardRank(ACE), Card::CardSuit(m_cards[i]->GetCardSuit()), face_up, 1);
					temp_hand += 1;
					temp_ace += 11;
				}
				else if (m_cards[i]->GetCardRank() == JACK || m_cards[i]->GetCardRank() == QUEEN || m_cards[i]->GetCardRank() == KING)
				{
					temp[i] = new FaceCard(Card::CardRank(m_cards[i]->GetCardRank()), Card::CardSuit(m_cards[i]->GetCardSuit()), face_up);
					temp_hand += 10;
					temp_ace += 10;
				}
				else
				{
					temp[i] = new NumberCard(Card::CardRank(m_cards[i]->GetCardRank()), Card::CardSuit(m_cards[i]->GetCardSuit()), face_up, m_cards[i]->GetCardRank());
					temp_hand += m_cards[i]->GetCardRank();
					temp_ace += m_cards[i]->GetCardRank();
				}
			}

			if (card->GetCardRank() == ACE)
			{
				temp[temp_count - 1] = new AceCard(Card::CardRank(ACE), Card::CardSuit(card->GetCardSuit()), face_up, 1);
				temp_hand += 1;
				temp_ace += 11;
			}
			else if (card->GetCardRank() == JACK || card->GetCardRank() == QUEEN || card->GetCardRank() == KING)
			{
				temp[temp_count - 1] = new FaceCard(Card::CardRank(card->GetCardRank()), Card::CardSuit(card->GetCardSuit()), face_up);
				temp_hand += 10;
				temp_ace += 10;
			}
			else
			{
				temp[temp_count - 1] = new NumberCard(Card::CardRank(card->GetCardRank()), Card::CardSuit(card->GetCardSuit()), face_up, card->GetCardRank());
				temp_hand += card->GetCardRank();
				temp_ace += card->GetCardRank();
			}
		}
		
		Clear();
		m_cards = temp;
		m_count = temp_count;
		m_handValue = temp_hand;
		m_aceValue = temp_ace;
	}
}

void Hand::FlipAll(void)
{
	m_handValue = 0;
	m_aceValue = 0;

	for (int f = 0; f < m_count; f++)
	{
		m_cards[f]->SetFace(true);
		
		if (m_cards[f]->GetCardRank() == ACE)
		{
			m_handValue += 1;
			m_aceValue += 11;
		}
		else if (m_cards[f]->GetCardRank() == JACK || m_cards[f]->GetCardRank() == QUEEN || m_cards[f]->GetCardRank() == KING)
		{
			m_handValue += 10;
			m_aceValue += 10;
		}
		else
		{
			m_handValue += m_cards[f]->GetCardRank();
			m_aceValue += m_cards[f]->GetCardRank();
		}
	}
}

void Hand::Display(void)
{
	for (int i = 0; i < m_count; i++)
	{
		m_cards[i]->Display();
		cout << " ";
	}
}

void Hand::Clear(void)
{
	for (size_t i = 0; i < m_count; i++)
	{
		delete m_cards[i];
		m_cards[i] = nullptr;
	}
	m_count = 0;
	m_aceValue = 0;
	m_handValue = 0;
	delete[] m_cards;
	m_cards = nullptr;
}

int Hand::GetHandValue(void)
{
	return m_handValue;
}

int Hand::GetAceValue(void)
{
	return m_aceValue;
}

int Hand::GetCount(void)
{
	return m_count;
}

#include "Deck.h"
#include "AceCard.h"
#include "FaceCard.h"
#include "NumberCard.h"
#include <time.h>

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


Deck::Deck(void)
{
	m_cards = nullptr;
	m_index = 0;
	m_maxSize = 0;
}

Deck::Deck(size_t amount)
{
	m_maxSize = DECK_SIZE * amount;
	m_index = 0;

	m_cards = new Card*[sizeof(Card) * m_maxSize]; 
	
	for (size_t deck_count = 0; deck_count < amount; deck_count++)
	{
		for (size_t suit_index = 0; suit_index < 4; suit_index++)
		{
			m_cards[m_index] = new AceCard(Card::CardRank(ACE), Card::CardSuit(suits[suit_index]), false, 1);
			m_index++;

			for (size_t number_index = 1; number_index < 10; number_index++)
			{
				m_cards[m_index] = new NumberCard(Card::CardRank(ranks[number_index]), Card::CardSuit(suits[suit_index]), false, ranks[number_index]);
				m_index++;
			}

			for (size_t face_index = 11; face_index < 14; face_index++)
			{
				m_cards[m_index] = new FaceCard(Card::CardRank(face_index), Card::CardSuit(suits[suit_index]), false);
				m_index++;
			}
		}
	}
}

Deck::Deck(const Deck & deck)
{
	m_index = deck.m_index;
	m_maxSize = deck.m_maxSize;
	m_cards = new Card*[sizeof(Card) * m_index];

	for (size_t c = 0; c < m_maxSize; c++)
	{
		if (deck.m_cards[c]->GetCardRank() == ACE)
		{
			m_cards[c] = new AceCard(Card::CardRank(ACE), Card::CardSuit(deck.m_cards[c]->GetCardSuit()), false, 1);
		}
		else if (deck.m_cards[c]->GetCardRank() == JACK || deck.m_cards[c]->GetCardRank() == QUEEN || deck.m_cards[c]->GetCardRank() == KING)
		{
			m_cards[c] = new FaceCard(Card::CardRank(deck.m_cards[c]->GetCardRank()), Card::CardSuit(deck.m_cards[c]->GetCardSuit()), false);
		}
		else
		{
			m_cards[c] = new NumberCard(Card::CardRank(deck.m_cards[c]->GetCardRank()), Card::CardSuit(deck.m_cards[c]->GetCardSuit()), false, deck.m_cards[c]->GetCardRank());
		}
	}
}

Deck::~Deck(void)
{
	Clear();
	delete[] m_cards;
	m_cards = nullptr;
}

Deck & Deck::operator=(const Deck & deck)
{
	if (this != &deck)
	{
		Clear();
		delete m_cards;

		m_index = deck.m_index;
		m_maxSize = deck.m_maxSize;
		m_cards = new Card*[sizeof(Card) * m_maxSize];

		for (size_t c = 0; c < m_index; c++)
		{
			if (deck.m_cards[c]->GetCardRank() == ACE)
			{
				m_cards[c] = new AceCard(Card::CardRank(ACE), Card::CardSuit(deck.m_cards[c]->GetCardSuit()), false, 1);
			}
			else if (deck.m_cards[c]->GetCardRank() == JACK || deck.m_cards[c]->GetCardRank() == QUEEN || deck.m_cards[c]->GetCardRank() == KING)
			{
				m_cards[c] = new FaceCard(Card::CardRank(deck.m_cards[c]->GetCardRank()), Card::CardSuit(deck.m_cards[c]->GetCardSuit()), false);
			}
			else
			{
				m_cards[c] = new NumberCard(Card::CardRank(deck.m_cards[c]->GetCardRank()), Card::CardSuit(deck.m_cards[c]->GetCardSuit()), false, deck.m_cards[c]->GetCardRank());
			}
		}
	}
	return *this;
}

void Deck::Shuffle(void)
{
	int random = 0;
	Card * temp = nullptr;

	cout << "Shuffling deck ... " << endl;

	srand((unsigned) time(0));
	for (int s = 0; s < 5; s++)
	{
		for (int i = 0; i < m_index; i++)
		{
			random = (rand() % (m_index - 1));
			temp = m_cards[i];
			m_cards[i] = m_cards[random];
			m_cards[random] = temp;
		}
	}
	temp = nullptr;
}

/*****************************************************************************************************
* Function: Draw(void)
* Purpose: Removes a card from the top of the stack array
* Preconditon: A Card stack array
* Postcondition: The current Card stack array with the Card on the top of the stack deleted
*****************************************************************************************************/
Card * Deck::Draw(void)
{
	Card *card = nullptr;
	if (m_index > 0)
	{
		card = m_cards[m_index - 1];
		m_index--;
	}
	return card;
}

/*****************************************************************************************************
* Function: Peek(void) const
* Purpose: Checks the top card in the stack array
* Preconditon: A Card stack array
* Postcondition: The Card at the top of the current stack array
*****************************************************************************************************/
Card * Deck::Peek(void) const
{
	Card *card = nullptr;
	if (m_index > 0)
		card = m_cards[m_index - 1];
	return card;
}

/*****************************************************************************************************
* Function: Clear(void)
* Purpose: Clears the stack array
* Preconditon: A Card stack array
* Postcondition: Memory freed and the current Card stack array deleted
*****************************************************************************************************/
void Deck::Clear(void)
{
	for (size_t i = 0; i < m_index; i++)
	{
		delete m_cards[i];
		m_cards[i] = nullptr;
	}
	delete[] m_cards;
	m_cards = nullptr;
	m_index = 0;
}

/*****************************************************************************************************
* Function: MaxSize(void) const
* Purpose: Returns the max size of the current stack array
* Preconditon: No access to private data members
* Postcondition: Max size of current array
*****************************************************************************************************/
size_t Deck::MaxSize(void) const
{
	return m_maxSize;
}

/*****************************************************************************************************
* Function: CurrSize(void) const
* Purpose: Returns the current size of the current stack array
* Preconditon: No access to private data members
* Postcondition: Current size of current array
*****************************************************************************************************/
size_t Deck::CurrSize(void) const
{
	return m_index;
}

/*****************************************************************************************************
* Function: IsFull(void) const
* Purpose: Checks if the current stack array is full
* Preconditon: A Card stack array
* Postcondition: If the current size equals the max size then the array is full
*****************************************************************************************************/
bool Deck::IsFull(void) const
{
	bool full = false;

	if (m_index >= m_maxSize)
		full = true;

	return full;
}
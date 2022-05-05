#include "HumanPlayer.h"
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

HumanPlayer::HumanPlayer(void) : Player(), m_score(0), m_type('H'), m_bust(false)
{
}

HumanPlayer::HumanPlayer(Hand * hand, char * name, bool bust, int score) : Player(hand, name), m_score(score), m_type('H'), m_bust(bust)
{
}

HumanPlayer::HumanPlayer(const HumanPlayer & human) : Player(human), m_score(human.m_score), m_type('H'), m_bust(human.m_bust)
{
}

HumanPlayer & HumanPlayer::operator=(const HumanPlayer & human)
{
	if (this != &human)
	{
		Player::operator=(human);
		m_score = human.m_score;
		m_type = 'H';
		m_bust = human.m_bust;
	}
	return *this;
}

HumanPlayer::~HumanPlayer(void)
{
	m_score = 0;
	m_type = 0;
	m_bust = false;
}

void HumanPlayer::DisplayHand(void)
{
	cout << "[ " << m_name << " ][ Value: " << m_hand->GetHandValue() << " ][ If Ace: " << m_hand->GetAceValue() << " ]";
	m_hand->Display();
	cout << endl;
}

void HumanPlayer::AddCard(Card * card, bool face_up) const
{
	m_hand->Add(card, face_up);
	delete card;
	card = nullptr;
}

void HumanPlayer::Hit(Deck &deck) const
{
	Card *temp_card = deck.Draw();
	m_hand->Add(temp_card, true);
	delete temp_card;
	temp_card = nullptr;
}

void HumanPlayer::Stand(void) const
{
	cout << m_name << " is standing.\n" << endl;
}

char * HumanPlayer::GetName(void) const
{
	return m_name;
}

Hand * HumanPlayer::GetHand(void) const
{
	return m_hand;
}

bool HumanPlayer::GetBust(void) const
{
	return m_bust;
}

void HumanPlayer::SetBust(bool bust)
{
	m_bust = bust;
}

int HumanPlayer::GetScore(void) const
{
	return m_score;
}

void HumanPlayer::SetScore(int score)
{
	m_score = score;
}

char HumanPlayer::GetType(void) const
{
	return m_type;
}

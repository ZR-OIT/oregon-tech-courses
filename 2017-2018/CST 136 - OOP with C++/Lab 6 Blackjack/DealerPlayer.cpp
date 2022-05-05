#include "DealerPlayer.h"
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

DealerPlayer::DealerPlayer(void) : Player(), m_score(0), m_type('D')
{
}

DealerPlayer::DealerPlayer(Hand * hand, char * name, bool bust, int score) : Player(hand, name), m_score(score), m_type('D'), m_bust(bust)
{
}

DealerPlayer::DealerPlayer(const DealerPlayer & dealer) : Player(dealer), m_score(dealer.m_score), m_type('D'), m_bust(dealer.m_bust)
{
}

DealerPlayer & DealerPlayer::operator=(const DealerPlayer & dealer)
{
	if (this != &dealer)
	{
		Player::operator=(dealer);
		m_score = dealer.m_score;
		m_type = 'D';
		m_bust = dealer.m_bust;
	}
	return *this;
}

DealerPlayer::~DealerPlayer(void)
{
	m_score = 0;
	m_type = 0;
	m_bust = false;
}

void DealerPlayer::DisplayHand(void)
{
	cout << "[ " << m_name << " ][ Value: " << m_hand->GetHandValue() << " ][ If Ace: " << m_hand->GetAceValue() << " ]";
	m_hand->Display();
	cout << endl;
}

void DealerPlayer::AddCard(Card * card, bool face_up) const
{
	m_hand->Add(card, face_up);
	delete card;
	card = nullptr;
}

void DealerPlayer::Hit(Deck & deck) const
{
	Card *temp_card = deck.Draw();
	m_hand->Add(temp_card, temp_card->GetFace());
	delete temp_card;
	temp_card = nullptr;
}

void DealerPlayer::Stand(void) const
{
	cout << "\n[ " << m_name << " ] is standing." << endl;
}

char * DealerPlayer::GetName(void) const
{
	return m_name;
}

Hand * DealerPlayer::GetHand(void) const
{
	return m_hand;
}

bool DealerPlayer::GetBust(void) const
{
	return m_bust;
}

void DealerPlayer::SetBust(bool bust)
{
	m_bust = bust;
}

int DealerPlayer::GetScore(void) const
{
	return m_score;
}

void DealerPlayer::SetScore(int score)
{
	m_score = score;
}

char DealerPlayer::GetType(void) const
{
	return m_type;
}

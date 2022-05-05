#include "BotPlayer.h"
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

BotPlayer::BotPlayer(void) : Player(), m_score(0), m_type('B'), m_bust(false)
{
}

BotPlayer::BotPlayer(Hand * hand, char * name, bool bust, int score) : Player(hand, name), m_score(score), m_type('B'), m_bust(bust)
{
}

BotPlayer::BotPlayer(const BotPlayer & bot) : Player(bot), m_score(bot.m_score), m_type('B'), m_bust(bot.m_bust)
{
}

BotPlayer & BotPlayer::operator=(const BotPlayer & bot)
{
	if (this != &bot)
	{
		Player::operator=(bot);
		m_score = bot.m_score;
		m_type = 'B';
		m_bust = bot.m_bust;
	}
	return *this;
}

BotPlayer::~BotPlayer(void)
{
	m_score = 0;
	m_type = 0;
	m_bust = false;
}

void BotPlayer::DisplayHand(void)
{
	cout << "[ " << m_name << " ][ Value: " << m_hand->GetHandValue() << " ][ If Ace: " << m_hand->GetAceValue() << " ]";
	m_hand->Display();
	cout << endl;
}

void BotPlayer::AddCard(Card * card, bool face_up) const
{
	m_hand->Add(card, face_up);
	delete card;
	card = nullptr;
}

void BotPlayer::Hit(Deck & deck) const
{
	Card *temp_card = deck.Draw();
	m_hand->Add(temp_card, temp_card->GetFace());
	delete temp_card;
	temp_card = nullptr;
}

void BotPlayer::Stand(void) const
{
	cout << "\n[ "<< m_name << " ] is standing." << endl;
}

char * BotPlayer::GetName(void) const
{
	return m_name;
}

Hand * BotPlayer::GetHand(void) const
{
	return m_hand;
}

bool BotPlayer::GetBust(void) const
{
	return m_bust;
}

void BotPlayer::SetBust(bool bust)
{
	m_bust = bust;
}

int BotPlayer::GetScore(void) const
{
	return m_score;
}

void BotPlayer::SetScore(int score)
{
	m_score = score;
}

char BotPlayer::GetType(void) const
{
	return m_type;
}

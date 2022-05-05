#include "Player.h"
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

Player::Player(void) : m_name(nullptr), m_hand(nullptr)
{
	//empty
}

Player::Player(Hand * hand, char * name)
{
	m_hand = hand;
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
}

Player::Player(const Player & player) : Player(player.m_hand, player.m_name)
{
}

Player & Player::operator=(const Player & player)
{
	if (this != &player)
	{
		m_name = new char[strlen(player.m_name) + 1];
		strcpy(m_name, player.m_name);
		m_hand->Clear();
		m_hand = new Hand(*player.m_hand);
	}
	return *this;
}

Player::~Player(void)
{
	delete m_hand;
	m_hand = nullptr;

	delete[] m_name;
	m_name = nullptr;
}

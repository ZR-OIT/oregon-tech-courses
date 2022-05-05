#pragma once

#ifndef PLAYER_H
# define PLAYER_H
# define _CRT_SECURE_NO_WARNINGS
# include "Card.h"
# include "Hand.h"
# include "Deck.h"

class Player
{
public:
	Player(void);
	Player(Hand * hand, char * name);
	Player(const Player &player);
	Player &operator=(const Player &player);
	virtual
		~Player(void);
	virtual void AddCard(Card * card, bool face_up) const = 0;
	virtual void Hit(Deck &deck) const = 0;
	virtual void Stand(void) const = 0;
	virtual char * GetName(void) const = 0;
	virtual Hand * GetHand(void) const = 0;
	virtual bool GetBust(void) const = 0;
	virtual void SetBust(bool bust) = 0;
	virtual int GetScore(void) const = 0;
	virtual void SetScore(int score) = 0;
	virtual char GetType(void) const = 0;
protected:
	Hand * m_hand;
	char * m_name;
};
#endif // PLAYER_H

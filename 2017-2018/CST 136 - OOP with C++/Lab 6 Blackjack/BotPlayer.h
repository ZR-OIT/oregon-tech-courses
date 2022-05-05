#pragma once

#ifndef BOTPLAYER_H
# define BOTPLAYER_H
# define _CRT_SECURE_NO_WARNINGS
# include "Player.h"

class BotPlayer : virtual public Player
{
public:
	BotPlayer(void);
	BotPlayer(Hand * hand, char * name, bool bust, int score);
	BotPlayer(const BotPlayer &bot);
	BotPlayer &operator=(const BotPlayer &bot);
	~BotPlayer(void);
	void DisplayHand(void);
	virtual void AddCard(Card * card, bool face_up) const;
	virtual void Hit(Deck &deck) const;
	virtual void Stand(void) const;
	virtual char * GetName(void) const;
	virtual Hand * GetHand(void) const;
	virtual bool GetBust(void) const;
	virtual void SetBust(bool bust);
	virtual int GetScore(void) const;
	virtual void SetScore(int score);
	virtual char GetType(void) const;
private:
	int m_score;
	bool m_bust;
	char m_type;
};

#endif // BOTPLAYER_H
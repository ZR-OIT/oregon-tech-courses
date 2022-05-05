#pragma once

#ifndef HUMANPLAYER_H
# define HUMANPLAYER_H
# define _CRT_SECURE_NO_WARNINGS
# include "Player.h"

class HumanPlayer : virtual public Player
{
public:
	HumanPlayer(void);
	HumanPlayer(Hand * hand, char * name, bool bust, int score);
	HumanPlayer(const HumanPlayer &human);
	HumanPlayer &operator=(const HumanPlayer &human);
	~HumanPlayer(void);
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

#endif // HUMANPLAYER_H
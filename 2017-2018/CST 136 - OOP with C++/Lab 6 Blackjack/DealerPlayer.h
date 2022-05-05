#pragma once

#ifndef DEALERPLAYER_H
# define DEALERPLAYER_H
# define _CRT_SECURE_NO_WARNINGS
# include "Player.h"

class DealerPlayer : virtual public Player
{
public:
	DealerPlayer(void);
	DealerPlayer(Hand * hand, char * name, bool bust, int score);
	DealerPlayer(const DealerPlayer &dealer);
	DealerPlayer &operator=(const DealerPlayer &dealer);
	~DealerPlayer(void);
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

#endif // DEALERPLAYER_H
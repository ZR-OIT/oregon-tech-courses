#pragma once

#ifndef ACECARD_H
# define ACECARD_H
# define _CRT_SECURE_NO_WARNINGS
# include "Card.h"

class AceCard : virtual public Card
{
public:
	AceCard(void);
	AceCard(CardRank cardRank, CardSuit cardSuit, bool up, int value);
	AceCard(const AceCard &card);
	AceCard &operator=(const AceCard &card);
	~AceCard(void);
	virtual void Display(void) const;
	virtual void Flip(void);
	virtual int GetValue(void);
	virtual void SetValue(int value);
	virtual bool GetFace(void);
	virtual void SetFace(bool face_up);
	

	char ascii_spades[6] = "|A S|";//"|♠ A|";
	char ascii_diamonds[6] = "|A D|";//"|♦ A|";
	char ascii_clubs[6] = "|A C|";//"|♣ A|";
	char ascii_hearts[6] = "|A H|";//"|♥ A|";
	char ascii_facedown[6] = "|???|";
private:
	int m_actualValue;
	bool m_faceUp;
};

#endif // ACECARD_H

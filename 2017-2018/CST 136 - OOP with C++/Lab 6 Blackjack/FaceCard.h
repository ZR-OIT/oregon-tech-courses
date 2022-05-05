#pragma once

#ifndef FACECARD_H
# define FACECARD_H
# define _CRT_SECURE_NO_WARNINGS
# include "Card.h"

class FaceCard : virtual public Card
{
public:
	FaceCard(CardRank cardRank, CardSuit cardSuit, bool up);
	FaceCard(const FaceCard &card);
	FaceCard &operator=(const FaceCard &card);
	~FaceCard(void);
	virtual void Display(void) const;
	virtual void Flip(void);
	virtual int GetValue(void);
	virtual void SetValue(int value);
	virtual bool GetFace(void);
	virtual void SetFace(bool face_up);

	char *ascii_spades[3] = { { "|J S|" },{ "|Q S|" },{ "|K S|" } };//{ { "|♠ J|" },{ "|♠ Q|" },{ "|♠ K|" } };
	char *ascii_diamonds[3] = { { "|J D|" },{ "|Q D|" },{ "|K D|" } };//{ { "|♦ J|" },{ "|♦ Q|" },{ "|♦ K|" } };
	char *ascii_clubs[3] = { { "|J C|" },{ "|Q C|" },{ "|K C|" } };//{ { "|♣ J|" },{ "|♣ Q|" },{ "|♣ K|" } };
	char *ascii_hearts[3] = { { "|J H|" },{ "|Q H|" },{ "|K H|" } };//{ { "|♥ J|" },{ "|♥ Q|" },{ "|♥ K|" } };
	char ascii_facedown[6] = "|???|";
private:
	FaceCard(void);

	int m_actualValue;
	bool m_faceUp;
};

#endif // FACECARD_H

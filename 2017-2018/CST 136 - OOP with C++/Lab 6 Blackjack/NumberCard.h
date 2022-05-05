#pragma once

#ifndef NUMBERCARD_H
# define NUMBERCARD_H
# define _CRT_SECURE_NO_WARNINGS
# include "Card.h"

class NumberCard : virtual public Card
{
public:
	NumberCard(void);
	NumberCard(CardRank cardRank, CardSuit cardSuit, bool up, int value);
	NumberCard(const NumberCard &card);
	NumberCard &operator=(const NumberCard &card);
	~NumberCard(void);
	
	virtual void Display(void) const;
	virtual void Flip(void);
	virtual int GetValue(void);
	virtual void SetValue(int value);
	virtual bool GetFace(void);
	virtual void SetFace(bool face_up);

	char *ascii_spades[9] = { { "|2 S|" },{ "|3 S|" },{ "|4 S|" },{ "|5 S|" },{ "|6 S|" },{ "|7 S|" },{ "|8 S|" },{ "|9 S|" },{ "|10S|" } };//{ {"|♠ 2|"},{"|♠ 3|"}, {"|♠ 4|"}, {"|♠ 5|"}, {"|♠ 6|"}, {"|♠ 7|"}, {"|♠ 8|"}, {"|♠ 9|"}, {"|♠10|"} };
	char *ascii_diamonds[9] = { { "|2 D|" },{ "|3 D|" },{ "|4 D|" },{ "|5 D|" },{ "|6 D|" },{ "|7 D|" },{ "|8 D|" },{ "|9 D|" },{ "|10D|" } };//{ {"|♦ 2|"}, {"|♦ 3|"}, {"|♦ 4|"}, {"|♦ 5|"}, {"|♦ 6|"}, {"|♦ 7|"}, {"|♦ 8|"}, {"|♦ 9|"}, {"|♦10|"} };
	char *ascii_clubs[9] = { { "|2 C|" },{ "|3 C|" },{ "|4 C|" },{ "|5 C|" },{ "|6 C|" },{ "|7 C|" },{ "|8 C|" },{ "|9 C|" },{ "|10C|" } };//{ {"|♣ 2|"}, {"|♣ 3|"}, {"|♣ 4|"}, {"|♣ 5|"}, {"|♣ 6|"}, {"|♣ 7|"}, {"|♣ 8|"}, {"|♣ 9|"}, {"|♣10|"} };
	char *ascii_hearts[9] = { { "|2 H|" },{ "|3 H|" },{ "|4 H|" },{ "|5 H|" },{ "|6 H|" },{ "|7 H|" },{ "|8 H|" },{ "|9 H|" },{ "|10H|" } };//{ {"|♥ 2|"}, { "|♥ 3|" }, { "|♥ 4|" }, { "|♥ 5|" }, { "|♥ 6|" }, { "|♥ 7|" }, { "|♥ 8|" }, { "|♥ 9|" }, { "|♥10|" } };
	char ascii_facedown[6] = "|???|"; 
private:
	int m_actualValue;
	bool m_faceUp;
};

#endif // NUMBERCARD_H

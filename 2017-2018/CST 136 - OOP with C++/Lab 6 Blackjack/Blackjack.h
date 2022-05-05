#pragma once

#ifndef BLACKJACK_H
# define BLACKACK_H
# define _CRT_SECURE_NO_WARNINGS
# include "Player.h"
# include "HumanPlayer.h"
# include "BotPlayer.h"
# include "DealerPlayer.h"
# include "Card.h"
# include "Deck.h"

class Blackjack
{
public:
	Blackjack(int players, int decks, char types[], char * names[]);
	Blackjack(const Blackjack &blackjack);
	Blackjack &operator=(const Blackjack &blackjack);
	~Blackjack(void);
	void BeginGame(void);
	void ShowHand(Player &player);
	void ShowAllHands(void);
	void DealerTurn(Player &player);
	void HumanTurn(Player &player);
	void BotTurn(Player &player);
	void NewRound(void);
private:
	Blackjack(void);

	Player ** m_players;
	DealerPlayer * m_dealer;
	int m_playerCount;
	int m_bustCount;
	bool m_dealerBust;
	Deck * m_deck;
};

#endif // BOTPLAYER_H
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
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <crtdbg.h>
#include "Card.h"
#include "AceCard.h"
#include "FaceCard.h"
#include "NumberCard.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "DealerPlayer.h"
#include "Blackjack.h"

using std::cout;
using std::cin;
using std::endl;

const int MAX_NAME = 50;

enum CardRank : uint8_t {
	ACE = 1
	, TWO
	, THREE
	, FOUR
	, FIVE
	, SIX
	, SEVEN
	, EIGHT
	, NINE
	, TEN
	, JACK
	, QUEEN
	, KING
};
enum CardSuit : uint8_t {
	CLUBS = 1
	, DIAMONDS
	, HEARTS
	, SPADES
};

static constexpr const char *rank_strings[14] = {
	"" // an empty placeholder
	, "Ace"
	, "Two"
	, "Three"
	, "Four"
	, "Five"
	, "Six"
	, "Seven"
	, "Eight"
	, "Nine"
	, "Ten"
	, "Jack"
	, "Queen"
	, "King"
};
static constexpr const char *suit_strings[5] = {
	"" // an empty placeholder
	, "Clubs"
	, "Diamonds"
	, "Hearts"
	, "Spades"
};

void RunTests(void);

/*****************************************************************************************************
* Function: main
* Purpose: Controls the classes that create a Blackjack game
* Preconditon: None
* Postcondition: A finished round of Blackjack
*****************************************************************************************************/
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool tests = false;
	int player_count = 0;
	int deck_count = 0;
	char * player_names[5];
	char player_types[5];
	char temp_name[MAX_NAME];

	cout << "How many players? (1 to 5)" << endl;
	cin >> player_count;

	cout << "How many decks? (1, 2 , 4, or 6)" << endl;
	cin >> deck_count;

	while ((deck_count != 1) && (deck_count != 2) && (deck_count != 4) && (deck_count != 6))
	{
		cout << "\nThat isn't a valid option!" << endl;
		cout << "How many decks? (1, 2 , 4, or 6)" << endl;
		cin >> deck_count;
	}

	while (player_count > 5 || player_count < 1)
	{
		cout << "\nThat isn't a valid option!" << endl;
		cout << "\nHow many players? (1 to 5)" << endl;
		cin >> player_count;
	}

	for (int i = 1; i <= player_count; i++)
	{
		cout << "Is [Player " << i << "] a Human (H) or a Bot (B)?" << endl;
		cin >> player_types[i - 1];

		while ((player_types[i - 1] != 'H') && (player_types[i - 1] != 'B'))
		{
			cout << "\nThat isn't a valid option!" << endl;
			cout << "\nIs [Player " << i << "] a Human (H) or a Bot (B)?" << endl;
			cin >> player_types[i - 1];
		}

		cout << "What is [Player " << i << "'s] name?" << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp_name, MAX_NAME);

		player_names[i - 1] = new char[strlen(temp_name) + 1];
		strcpy(player_names[i - 1], temp_name);
		temp_name[0] = '\0';
	}
	
	cout << "\n-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-\n" << endl;
	
	Blackjack * game = new Blackjack(player_count, deck_count, player_types, player_names);

	for (int c = 0; c < player_count; c++)
	{
		delete[] player_names[c];
		player_names[c] = '\0';
	}

	game->BeginGame();
	delete game;

	if (tests = true)
	{
		RunTests();
	}
	return 0;
}


/*****************************************************************************************************
* Function:
* Purpose:
* Preconditon:
* Postcondition:
*****************************************************************************************************/
void RunTests(void)
{
	cout << "-------------------------------------------------------------" << endl;
	// Deck and Shuffle Tests
	{
		Deck * temp_deck = new Deck(1);
		temp_deck->Shuffle();
		Card * temp_card = nullptr;

		for (int i = 0; i < (52 * 1); i++)
		{
			temp_card = temp_deck->Draw();
			cout << "Card #" << (i + 1) << " = " << temp_card->GetRankStr() << " of " << temp_card->GetSuitStr() << endl;
			delete temp_card;
		}

		temp_deck->Clear();
		delete temp_deck;
		temp_deck = nullptr;
		temp_card = nullptr;
	}
	cout << "-------------------------------------------------------------" << endl;
	// Hand and Deck Tests
	{
		Deck * temp_deck2 = new Deck(1);
		temp_deck2->Shuffle();
		Hand * temp_hand2 = new Hand();
		Card * temp_card2 = nullptr;

		temp_card2 = temp_deck2->Draw();
		temp_hand2->Add(temp_card2, true);
		delete temp_card2;

		temp_card2 = temp_deck2->Draw();
		temp_hand2->Add(temp_card2, true);
		delete temp_card2;

		temp_card2 = temp_deck2->Draw();
		temp_hand2->Add(temp_card2, true);
		delete temp_card2;

		temp_hand2->Display();

		temp_hand2->Clear();
		delete temp_hand2;
		temp_deck2->Clear();
		delete temp_deck2;

		temp_deck2 = nullptr;
		temp_hand2 = nullptr;
	}
	cout << "-------------------------------------------------------------" << endl;

	// Human Tests
	{
		Deck * temp_deck3 = new Deck(1);
		temp_deck3->Shuffle();
		HumanPlayer * me = new HumanPlayer(new Hand(), "Zak", false, 0);

		me->Hit(*temp_deck3);
		me->DisplayHand();
		me->Hit(*temp_deck3);
		me->DisplayHand();
		me->Hit(*temp_deck3);
		me->DisplayHand();
		me->Stand();

		delete me;

		temp_deck3->Clear();
		delete temp_deck3;
		temp_deck3 = nullptr;
	}
	cout << "-------------------------------------------------------------" << endl;

	// Dealer Tests
	{
		Deck * temp_deck4 = new Deck(1);
		temp_deck4->Shuffle();
		Card * temp_card4 = nullptr;
		HumanPlayer * me = new HumanPlayer(new Hand(), "Zak", false, 0);
		DealerPlayer * dealer = new DealerPlayer(new Hand(), "Dealer", false, 0);

		me->Hit(*temp_deck4);
		me->DisplayHand();
		me->Hit(*temp_deck4);
		me->DisplayHand();
		me->Hit(*temp_deck4);
		me->DisplayHand();
		me->Stand();

		dealer->Hit(*temp_deck4);
		dealer->DisplayHand();
		dealer->Hit(*temp_deck4);
		dealer->DisplayHand();
		dealer->Hit(*temp_deck4);
		dealer->DisplayHand();
		dealer->Stand();

		delete me;
		delete dealer;

		for (int i = 0; i < (46); i++)
		{
			temp_card4 = temp_deck4->Draw();
			cout << "Card #" << (i + 1) << " = " << temp_card4->GetRankStr() << " of " << temp_card4->GetSuitStr() << endl;
			delete temp_card4;
		}

		temp_deck4->Clear();
		delete temp_deck4;
		temp_deck4 = nullptr;
		temp_card4 = nullptr;
	}
	cout << "-------------------------------------------------------------" << endl;
}

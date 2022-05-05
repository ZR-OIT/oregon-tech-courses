#include "Blackjack.h"
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

Blackjack::Blackjack(int players, int decks, char types[], char * names[])
{
	m_players = new Player*[sizeof(Player) * (players)];

	for (int i = 0; i < players; i++)
	{
		if (types[i] == 'H')
		{
			m_players[i] = new HumanPlayer(new Hand(), names[i], false, 0);
			m_playerCount++;
		}
		else if (types[i] == 'B')
		{
			m_players[i] = new BotPlayer(new Hand(), names[i], false, 0);
			m_playerCount++;
		}
	}
	m_dealer = new DealerPlayer(new Hand(), "The Dealer", false, 0);

	m_deck = new Deck(decks);
	m_deck->Shuffle();
	m_bustCount = 0;
	m_dealerBust = false;
}

Blackjack::Blackjack(const Blackjack & blackjack)
{
	m_players = new Player*[sizeof(Player) * blackjack.m_playerCount];
	for (int i = 0; i < blackjack.m_playerCount; i++)
	{
		if (blackjack.m_players[i]->GetType() == 'H')
		{
			m_players[i] = new HumanPlayer(new Hand(*blackjack.m_players[i]->GetHand()), blackjack.m_players[i]->GetName(), 
				blackjack.m_players[i]->GetBust(), blackjack.m_players[i]->GetScore());
		}
		else if (blackjack.m_players[i]->GetType() == 'B')
		{
			m_players[i] = new BotPlayer(new Hand(*blackjack.m_players[i]->GetHand()), blackjack.m_players[i]->GetName(), 
				blackjack.m_players[i]->GetBust(), blackjack.m_players[i]->GetScore());
		}
	}
	m_dealer = new DealerPlayer(new Hand(*blackjack.m_dealer->GetHand()), blackjack.m_dealer->GetName(),
		blackjack.m_dealer->GetBust(), blackjack.m_dealer->GetScore());

	m_deck = new Deck(*blackjack.m_deck);
	m_playerCount = blackjack.m_playerCount;
	m_bustCount = blackjack.m_bustCount;
	m_dealerBust = blackjack.m_dealerBust;
}

Blackjack & Blackjack::operator=(const Blackjack & blackjack)
{
	if (this != &blackjack)
	{
		m_players = new Player*[sizeof(Player) * blackjack.m_playerCount];
		for (int i = 0; i < blackjack.m_playerCount; i++)
		{
			if (blackjack.m_players[i]->GetType() == 'H')
			{
				m_players[i] = new HumanPlayer(new Hand(*blackjack.m_players[i]->GetHand()), blackjack.m_players[i]->GetName(),
					blackjack.m_players[i]->GetBust(), blackjack.m_players[i]->GetScore());
			}
			else if (blackjack.m_players[i]->GetType() == 'B')
			{
				m_players[i] = new BotPlayer(new Hand(*blackjack.m_players[i]->GetHand()), blackjack.m_players[i]->GetName(),
					blackjack.m_players[i]->GetBust(), blackjack.m_players[i]->GetScore());
			}
		}
		m_dealer = new DealerPlayer(new Hand(*blackjack.m_dealer->GetHand()), blackjack.m_dealer->GetName(),
			blackjack.m_dealer->GetBust(), blackjack.m_dealer->GetScore());

		m_deck = new Deck(*blackjack.m_deck);
		m_playerCount = blackjack.m_playerCount;
		m_bustCount = blackjack.m_bustCount;
		m_dealerBust = blackjack.m_dealerBust;
	}
	return *this;
}

Blackjack::~Blackjack(void)
{
	for (int i = 0; i < m_playerCount; i++)
	{
		delete m_players[i];
		m_players[i] = nullptr;
	}
	delete m_players;

	delete m_dealer;
	m_dealer = nullptr;

	//m_deck->Clear();
	delete m_deck;
	m_deck = nullptr;

	m_playerCount = 0;
	m_bustCount = 0;
	m_dealerBust = false;
}

void Blackjack::BeginGame(void)
{
	char option = '\0';
	int temp_score = 0;
	int temp_dealer = 0;
	int dealer_cards = 0;
	char * temp_name = nullptr;
	Player * dealer_charlie = nullptr;
	Player * player_charlie = nullptr;

	cout << "\nDealing ...\n" << endl;
	cout << "===========================================================================================" << endl;
	for (int i = 0; i < m_playerCount; i++)
	{
		m_players[i]->AddCard(m_deck->Draw(), true);
		ShowHand(*m_players[i]);
		cout << "-------------------------------------------------------------------------------------------" << endl;
	}
	
	m_dealer->AddCard(m_deck->Draw(), true);
	ShowHand(*m_dealer);
	cout << "===========================================================================================" << endl;
	cout << "\nDealing ... \n" << endl;
	cout << "===========================================================================================" << endl;
	for (int i = 0; i < m_playerCount; i++)
	{
		m_players[i]->AddCard(m_deck->Draw(), true);
		ShowHand(*m_players[i]);
		cout << "-------------------------------------------------------------------------------------------" << endl;
	}
	
	m_dealer->AddCard(m_deck->Draw(), false);
	ShowHand(*m_dealer);
	cout << "===========================================================================================" << endl;

	for (int t = 0; t < m_playerCount; t++)
	{
		if (m_players[t]->GetType() == 'H')
		{
			if (m_players[t]->GetBust() == false)
			{
				HumanTurn(*m_players[t]);
			}
		}
		else if (m_players[t]->GetType() == 'B')
		{
			if (m_players[t]->GetBust() == false)
			{
				BotTurn(*m_players[t]);
			}
		}
	}
	
	//If at least 1 player hasn't busted
	if (m_bustCount < m_playerCount)
	{
		DealerTurn(*m_dealer);

		if (m_dealerBust == false)
		{
			dealer_cards = m_dealer->GetHand()->GetCount();
			temp_dealer = m_dealer->GetScore();
			if (dealer_cards == 5)
			{
				cout << "\n[ " << m_dealer->GetName() << " ] got a 5 Card Charlie!" << endl;
				dealer_charlie = m_dealer;
			}
		}

		for (int s = 0; s < m_playerCount; s++)
		{
			if (m_players[s]->GetBust() == false)
			{
				temp_score = m_players[s]->GetScore();
				temp_name = m_players[s]->GetName();

				if (m_players[s]->GetHand()->GetCount() == 5 && dealer_cards < 5)
				{
					cout << "\n[ " << temp_name << " ] got a 5 Card Charlie!" << endl;
					player_charlie = m_players[s];
				}
	
				//Determine winners
				if (m_players[s] == player_charlie && dealer_charlie == nullptr)
				{
					cout << "\n[ " << temp_name << " ] wins with a score of " << temp_score << "!" << endl;
				}
				else if (m_dealer == dealer_charlie && player_charlie == nullptr)
				{
					cout << "\n[ " << temp_name << " ] loses with a score of " << temp_score << "!" << endl;
				}
				else if (temp_score > temp_dealer)
				{
					cout << "\n[ " << temp_name << " ] wins with a score of " << temp_score << "!" << endl;
				}
				else if (temp_score == temp_dealer)
				{
					cout << "\n[ " << temp_name << " ] ends in a push with " << m_dealer->GetName() << "!" << endl;
				}
				else if (temp_score < temp_dealer)
				{
					cout << "\n[ " << temp_name << " ] loses with a score of " << temp_score << "!" << endl;
				}
			}
		}
	}
	//If all players busted
	else
	{
		if (m_dealerBust == false)
		{
			temp_dealer = m_dealer->GetHand()->GetHandValue();
			temp_name = m_dealer->GetName();
			cout << "All players bust!" << endl;
			cout << "\n[ " << temp_name << " ] wins with a score of " << temp_dealer << "!" << endl;
		}
	}

	//Clear hands
	for (int p = 0; p < m_playerCount; p++)
	{
		m_players[p]->GetHand()->Clear();
		m_players[p]->SetBust(false);
		m_players[p]->SetScore(0);
	}
	m_dealer->GetHand()->Clear();
	m_bustCount = 0;
	m_dealerBust = false;

	cout << "\nPlay another round? (Y / N) ";
	
	std::cin >> option;
	
	while ((option != 'Y') && (option != 'N'))
	{
		cout << "\nThat isn't a valid option!" << endl;
		cout << "\nPlay another round? (Y / N) ";
		std::cin >> option;
	}

	if ((option == 'Y'))
	{
		cout << "\n-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-\n" << endl;
		NewRound();
	}
	else
	{
		cout << "\n-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-><><-\n" << endl;
		cout << "\nExiting game ..." << endl;
	}
}

void Blackjack::ShowHand(Player &player)
{
	cout << "[ " << player.GetName() << "'s Hand ] : ";
	player.GetHand()->Display();
	cout << " : [ Hand Value: " << player.GetHand()->GetHandValue() << " ] [ Hand Value with Ace: " << player.GetHand()->GetAceValue() << " ] " << endl;
}

void Blackjack::ShowAllHands(void)
{
	cout << "===========================================================================================" << endl;
	for (int i = 0; i < m_playerCount; i++)
	{
		ShowHand(*m_players[i]);
		cout << "-------------------------------------------------------------------------------------------" << endl;
	}

	ShowHand(*m_dealer);
	cout << "===========================================================================================" << endl;
}

void Blackjack::DealerTurn(Player &player)
{
	char option = '\0';

	cout << "\nIt's [ " << player.GetName() << "'s ] turn!\n" << endl;

	player.GetHand()->FlipAll();
	ShowAllHands();

	do
	{
		if (player.GetHand()->GetHandValue() <= 16 || player.GetHand()->GetAceValue() <= 17)
		{
			option = 'H';
			cout << "\n[ " << player.GetName() << " ] is hitting ... " << endl;
			player.Hit(*m_deck);
			player.GetHand()->FlipAll();
			ShowAllHands();
			if (player.GetHand()->GetHandValue() > 21)
			{
				cout << "\n[ " << player.GetName() << " ] has bust!" << endl;
				player.SetBust(true);
				m_dealerBust = true;
			}
		}
		else
		{
			option = 'S';
			player.Stand();
			ShowAllHands();
			if ((player.GetHand()->GetAceValue() <= 21) && (player.GetHand()->GetAceValue() > player.GetHand()->GetHandValue()))
			{
				player.SetScore(player.GetHand()->GetAceValue());
			}
			else
			{
				player.SetScore(player.GetHand()->GetHandValue());
			}
		}
	} while (player.GetBust() == false && option != 'S');

	cout << endl;
}

void Blackjack::HumanTurn(Player &player)
{
	char option = '\0';

	do
	{
		cout << "\nIt's [ " << player.GetName() << "'s ] turn!" << endl;
		cout << "\nHit or Stand? (H / S) ";
		std::cin >> option;
		while ((option != 'H') && (option != 'S'))
		{
			cout << "\nThat isn't a valid option!" << endl;
			cout << "\nHit or Stand? (H / S) ";
			std::cin >> option;
		}
		cout << endl;

		if (option == 'H')
		{
			cout << "\n[ " << player.GetName() << " ] is hitting ... " << endl;
			player.Hit(*m_deck);
			ShowAllHands();
			if (player.GetHand()->GetHandValue() > 21)
			{
				cout << "\n[ " << player.GetName() << " ] has bust!" << endl;
				player.SetBust(true);
				m_bustCount++;
			}
		}
		else
		{
			player.Stand();
			ShowAllHands();
			if ((player.GetHand()->GetAceValue() <= 21) && (player.GetHand()->GetAceValue() > player.GetHand()->GetHandValue()))
			{
				player.SetScore(player.GetHand()->GetAceValue());
			}
			else
			{
				player.SetScore(player.GetHand()->GetHandValue());
			}
		}

	} while (player.GetBust() == false && option != 'S');
	cout << endl;
}

void Blackjack::BotTurn(Player &player)
{
	char option = '\0';

	cout << "It's [ " << player.GetName() << "'s ] turn!" << endl;

	player.GetHand()->FlipAll();
	ShowAllHands();

	do
	{
		if (player.GetHand()->GetHandValue() <= 16 || player.GetHand()->GetAceValue() <= 17)
		{
			option = 'H';
			cout << "\n[ " << player.GetName() << " ] is hitting ... " << endl;
			player.Hit(*m_deck);
			player.GetHand()->FlipAll();
			ShowAllHands();
			if (player.GetHand()->GetHandValue() > 21)
			{
				cout << "\n[ " << player.GetName() << " ] has bust!" << endl;
				player.SetBust(true);
				m_bustCount++;
			}
		}
		else
		{
			option = 'S';
			player.Stand();
			ShowAllHands();
			if ((player.GetHand()->GetAceValue() <= 21) && (player.GetHand()->GetAceValue() > player.GetHand()->GetHandValue()))
			{
				player.SetScore(player.GetHand()->GetAceValue());
			}
			else
			{
				player.SetScore(player.GetHand()->GetHandValue());
			}
		}
	} while (player.GetBust() == false && option != 'S');

	cout << endl;
}

void Blackjack::NewRound(void)
{
	if (m_deck->CurrSize() < (m_playerCount * 4))
	{
		size_t deck_count = (m_deck->MaxSize() / 52);
		Deck * temp_deck = new Deck(deck_count);
		temp_deck->Shuffle();

		m_deck->Clear();
		m_deck = temp_deck;
	}
	BeginGame();
}


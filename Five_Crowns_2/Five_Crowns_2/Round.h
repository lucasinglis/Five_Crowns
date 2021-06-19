#include <iostream>
#include <string>
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Human.h"
#include "Computer.h"
#include "CardDealer.h"
#include <time.h>

using namespace std;

class Round {

public:
	Round(int roundIndex, Human* human_ptr, Computer* computer_ptr, bool next_player,bool newGame);
	Round(int roundIndex, Human* human_ptr, Computer* computer_ptr, bool next_player, vector<Card> discard, vector<Card> draw,bool newGame);
	void startRound();
	void printRound();
	void setUpRound();
	void printDeck(vector <Card> deck);
	void playRound();
	int getRound();
	void updateWild();
	void saveGame();
	string cardsToString(vector <Card> cards);
	Human getHuman();
	Computer getComputer();
	bool getNextPlayer();

private:
	static int m_roundIndex;
	//1 for human 2 for computer
	static bool m_playerTurn;
	bool isNewGame;
	// roundIndex in Round class had to +3 can also be used to see what number wild card is and for outputs
	vector <Card> m_roundDrawDeck;
	vector <Card> m_roundDiscardDeck;
	Computer m_Computer;
	Human m_Human;
	CardDealer m_Dealer;
	static int m_Round_HumanScore;
	static int m_Round_ComputerScore;
	int m_menuChoice;
	Player* players[2];

};
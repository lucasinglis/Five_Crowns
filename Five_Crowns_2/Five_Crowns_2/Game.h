
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include "Round.h"
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

class Game {
public:
	Game();
	bool coinToss();
	void newGame();
	void StartGame();
	int getRoundNum();
	int getComputerScore();
	int getHumanScore();
	void loadGame(string fileName);
	vector <Card> createCardVector(vector<string> stringCards);

private:
	int m_newGame = true;
	int m_roundCount = 1;
	static int computer_score;
	static int human_score;
	Human human;
	Computer computer;
	bool next_player;
	vector <Card> inDiscardPile;
	vector <Card> inDrawPile;

};
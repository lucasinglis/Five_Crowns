#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <ctype.h>
#include "Card.h"
//#include "Round.h"
#include <fstream>

using namespace std;

class Player {

public:
	Player();
	int getScore();
	void setScore(int score);
	void setHand(vector<Card> hand);
	void addToHand(Card addCard);
	void printHand();
	void removeFromHand(int index);
	Card getCard(int index);
	void printScore();
	void printPlayer();
	int play(vector <Card> &drawPile, vector <Card> &discardPile);
	virtual int drawCard(vector <Card> &drawPile, vector <Card> &discardPile);
	void addCard(Card newCard);
	virtual void discardCard(vector <Card> &discardPile);
	vector <Card> getHand();
	bool canGoOut();
	void numWildCards();
	void numJokers();
	vector <string> handToString(vector <Card> c_hand);
	vector<vector<Card>> possibleCombo(vector <string> s_hand);
	void sortHand(vector <string>& s_hand);
	bool stringWild(string card);
	bool stringJoker(string card);
	void setRoundNumber(int roundNumber);
	int getRoundNumber();
	int bestHandCombo(vector <Card> p_hand);
	vector<vector<Card>> findValidBooksRuns(vector<vector<string>> possibleCombo);
	bool checkRun(vector<Card> possibleCombo);
	bool checkBook(vector<Card> possibleCombo);
	vector<string> noWildAndJoker(vector<string> possibleCombo);
	int faceToInt(string Face);
	int scoreOfHand(vector<Card> p_hand);
	void printBestCombo();
	int getHandScore();
	void setStringHand(vector<string> inHand);


protected:
	vector <Card> m_hand;
	vector <string> m_string_hand;
	vector <string> bestCombo;
	int m_playerScore;
	int handScore = 99999;

private:
	
	int m_totalWild;
	int m_totalJoker;
	int m_roundNum;

};
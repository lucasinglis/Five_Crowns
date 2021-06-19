#pragma once

#include <iostream>
#include <string>

using namespace std;

class Card {

public:
	Card();
	Card(string inFace, string inSuit);
	bool setFace(string inFace);
	bool setSuit(string inSuit);
	bool isWildCard();
	string getSuit();
	string getFace();
	void updateWildCard(string inFace);
	void printCard();
	int compareTo(Card right);
	bool isValid();
	string stringCard();
	string getNumFace();

private:

	string m_Face;
	string m_Suit;
	bool m_Wildcard;

	static const char THREE = '3';
	static const char FOUR = '4';
	static const char FIVE = '5';
	static const char SIX = '6';
	static const char SEVEN = '7';
	static const char EIGHT = '8';
	static const char NINE = '9';
	static const char TEN = 'X';
	static const char JACK = 'J';
	static const char QUEEN = 'Q';
	static const char KING = 'K';

	//Suit values
	static const char SPADES = 'S';
	static const char CLUBS = 'C';
	static const char DIAMONDS = 'D';
	static const char HEARTS = 'H';
	static const char TRIDENTS = 'T';
	static const char J_ONE = '1';
	static const char J_TWO = '2';
	static const char J_THREE = '3';



};
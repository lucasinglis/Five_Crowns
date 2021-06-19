#pragma once
#include "Card.h"
#include <queue>
#include <fstream>
#include <algorithm>
#include<vector>
#include<random>
#include<chrono>

class Deck {

public:
	Deck();
	Deck(vector <Card> deckCards);
	bool isEmpty();
	Card dealCard();
	void updateWildCards(string face);
	void printDeck();

private:
	vector <Card> m_deckCards;
};
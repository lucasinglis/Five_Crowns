#pragma once
#pragma once
#include "Deck.h"
#include <queue>
#include <fstream>
#include <algorithm>
#include<vector>
#include<random>
#include<chrono>
#include <time.h>  

class CardDealer {

public:
	CardDealer();
	Card dealCard();
	void updateWildCards(string face);
	Deck getFirstDeck();
	Deck getSecondDeck();

private:

	Deck firstDeck;
	Deck secondDeck;
};
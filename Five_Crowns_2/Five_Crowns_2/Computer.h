#pragma once
#include "Player.h"
#include <time.h>

class Computer : public Player {

public:
	Computer();
	int drawCard(vector <Card> &drawPile, vector <Card> &discardPile);
	void discardCard(vector <Card> &discardPile);

	~Computer();

private:
	int drawScore = 9999;
	int drawIndex;
	int discardScore = 9999;
	int discardIndex;
};
#pragma once
#include "Player.h"
#include "Computer.h"

class Human : public Player {
public:
	Human();
	void printMenu();
	int getMenuValue();
	int drawCard(vector <Card> &drawPile, vector <Card> &discardPile);
	void discardCard(vector <Card> &discardPile);

private:
	int m_menuChoice;
};
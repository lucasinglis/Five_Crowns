/************************************************************
* Name:  Lucas Inglis
* Project : Five Crowns
* Class : Computer.cpp
* Date : 10/22/2019
*************************************************************/
#include "Computer.h"

Computer::Computer()
{

}

/* *********************************************************************
Function Name: computerMenu
Purpose: get what the computer will do durring its turn
Parameters: none
Return Value: int turn which is the number corresponding to specific game actions
Local Variables: int turn, the option the computer picks
Algorithm:
	randomly pick a number that corresponds to a game action
Assistance Received: none
********************************************************************* 
int Computer::computerMenu() {
	srand(time(NULL));
	int turn = rand() % 2 + 1;

	if (turn == 1)
	{
		return 1;
	}
	else if (turn == 2)
	{
		return 2;
	}
	else if (turn == 3)
	{
		return 3;
	}
	else if (turn == 4)
	{
		return 4;
	}
}*/

/* *********************************************************************
Function Name: drawCard
Purpose: see what deck to draw from
Parameters:
	vector <Card> &drawPile : draw pile as of now
	vector <Card> &discardPile : discard pile as of not
Return Value: int
Local Variables:
	Card topDiscard : top card on discard pile
	Card topDraw : top card on draw
	int handDrawScore : score of card with draw card
	int handDiscardScore : score of cards with discard card
	Computer tempComputer : temp computer to play with the cards
	vector <Card> tempHand : temp hand of the computer
	string stringCardDraw : string representation of draw card
	string stringCardDiscard : string representation of discard card
	int turn : random number to see if the computer will pick from draw or discard
Algorithm:
	1: create a temp computer to play with the cards to not mess with the original
	2: if either deck has a joker or wildCard pick from that pile
	3: if not then take the top card from the discard or draw and try and go out with it
	4: whatever score returned from going out is lower then pick from that pile
Assistance Received:
********************************************************************* */
int Computer::drawCard(vector <Card> &drawPile, vector <Card> &discardPile)
{


	Card topDiscard = discardPile[0];
	Card topDraw = drawPile[0];
	int handDrawScore , handDiscardScore;
	Computer tempComputer;
	vector <Card> tempHand = this->m_hand;
	tempComputer.setHand(tempHand);
	string stringCardDraw , stringCardDiscard;
	stringCardDiscard = topDiscard.getFace() + topDiscard.getSuit();
	stringCardDraw = topDraw.getFace() + topDraw.getSuit();

	/*
	for (int i = 0; i < m_hand.size(); i++)
	{
		tempComputer.m_hand.push_back(topDraw);
		erasedCard = tempComputer.m_hand[0];
		tempComputer.m_hand.erase(tempComputer.m_hand.begin());			
		tempComputer.canGoOut();
		tempComputer.m_hand.pop_back();
		tempComputer.m_hand.push_back(erasedCard);
		tempScore = tempComputer.handScore;

		if (tempScore < tempComputer.drawScore)
		{
			this->drawScore = tempScore;
			this->drawIndex = i;
		}
	}

	for (int i = 0; i < m_hand.size(); i++)
	{
		tempComputer.m_hand.push_back(topDiscard);
		erasedCard = tempComputer.m_hand[0];
		tempComputer.m_hand.erase(tempComputer.m_hand.begin());
		tempComputer.canGoOut();
		tempComputer.m_hand.pop_back();
		tempComputer.m_hand.push_back(erasedCard);
		tempScore = tempComputer.handScore;

		if (tempScore < tempComputer.discardScore)
		{
			this->discardScore = tempScore;
			this->discardIndex = i;
		}
	}
	*/

	
	if (stringJoker(stringCardDiscard)) {
		cout << "Computer picked from top of Discard pile because the card is a joker" << endl;
		this->addCard(topDiscard);
		discardPile.erase(discardPile.begin());
	}
	else if (stringWild(stringCardDiscard) ) 
	{
		cout << "Computer picked from top of Discard pile because the card is a wildcard " << endl;
		this->addCard(topDiscard);
		discardPile.erase(discardPile.begin());
	}
	else if (stringJoker(stringCardDraw)) {
		cout << "Computer picked from top of Draw pile because the card is a joker" << endl;
		this->addCard(topDraw);
		drawPile.erase(drawPile.begin());
	}
	else if (stringWild(stringCardDraw))
	{
		cout << "Computer picked from top of Draw pile because the card is a wildcard " << endl;
		this->addCard(topDraw);
		drawPile.erase(drawPile.begin());
	}
	else {
	

		tempComputer.setRoundNumber(getRoundNumber());
		tempComputer.m_hand.push_back(topDraw);
		tempComputer.canGoOut();
		handDrawScore = tempComputer.handScore;
		tempComputer.m_hand.erase(tempComputer.m_hand.begin() + (tempComputer.m_hand.size()-1) );
		tempComputer.m_string_hand.erase(tempComputer.m_string_hand.begin() + (tempComputer.m_string_hand.size() - 1));

		tempComputer.m_hand.push_back(topDiscard);
		tempComputer.canGoOut();
		handDiscardScore = tempComputer.handScore;
		tempComputer.m_hand.erase(tempComputer.m_hand.begin() + (tempComputer.m_hand.size()-1) );
		tempComputer.m_string_hand.erase(tempComputer.m_string_hand.begin() + (tempComputer.m_string_hand.size() - 1));

		if ((handDiscardScore < handDrawScore))
		{
			cout << "Computer picked from discard pile since it gave the computer a better book/run combo" << endl;
			this->addCard(topDiscard);
			discardPile.erase(discardPile.begin());
		}
		else if ((handDiscardScore > handDrawScore))
		{
			cout << "Computer picked from draw pile since it gave the computer a better book/run combo" << endl;
			this->addCard(topDraw);
			drawPile.erase(drawPile.begin());
		}
		else
		{
			srand(time(NULL));
			int turn = rand() % 2;

			cout << " -------- Draw or Discard does not give the computer a better combo. Picking randomly between the two ----------- " << endl;

			if (turn == 0)
			{
				cout << "Computer picked from draw pile" << endl;
				this->addCard(drawPile.at(0));
				drawPile.erase(drawPile.begin());
			}
			else if (turn == 1)
			{
				cout << "Computer picked from discard pile" << endl;
				this->addCard(discardPile.at(0));
				discardPile.erase(discardPile.begin());
			}
		}
		
	}

	return 1;
}

/* *********************************************************************
Function Name: discardCard
Purpose: figure out what card to discard
Parameters:
	vector <Card> &discardPile : discard pile as of now
Return Value:
Local Variables:
	Computer tempComputer : temp computer so we dont mess with original
	vector <Card> tempHand : temp hand so we dont mess with original
	vector <int> cardScores : scores after going out with a specific card removed
	Card erasedCard : card removed from the hand to see what score it will get
	string stringCard : string representation of a card
	int min : min score
	int removeIndex : index in cardScores with the lowest score
Algorithm:
	1: remove a card from the hand and go out
	2: get the score associated with the removed card an put it into cardScores
	3: look through cardScores and find its lowest value
	4: set that index to removeIndex
	5: remove card from your hand at removeIndex
Assistance Received:
********************************************************************* */
void Computer::discardCard(vector <Card> &discardPile)
{

	Computer tempComputer;
	vector <Card> tempHand = this->m_hand;
	tempComputer.setHand(tempHand);
	vector <int> cardScores;
	Card erasedCard;
	string stringCard;
	int min = 100000;
	int removeIndex;

	cout << "Computer's hand before dropping a card - index 1->" << m_hand.size() << " : " << endl;
	printHand();
	cout << endl;

	for (int i = 0; i < m_hand.size(); i++)
	{
		erasedCard = tempComputer.m_hand[0];
		tempComputer.m_hand.erase(tempComputer.m_hand.begin());
		tempComputer.canGoOut();		
		cardScores.push_back(tempComputer.handScore);
		//tempComputer.m_hand.pop_back();
		tempComputer.m_hand.push_back(erasedCard);

	}

	for (int i =0; i < cardScores.size(); i++)
	{
		stringCard = m_hand[i].getFace() + m_hand[i].getSuit();
		if (stringJoker(stringCard) || stringWild(stringCard) )
		{
			continue;
		}
		else
		{
			if (cardScores[i] < min)
			{
				min = cardScores[i];
				removeIndex = i;
			}
			if ( cardScores[i] == 0)
			{
				cout << "Computer is removing card at index " << (removeIndex + 1) << " because without it the computer can go out" << endl;
			}
		}

	}

	cout << "The computer removed card at index " << (removeIndex + 1) << " since it wasnt a wild/joker card and didn't help with books/runs" << endl;
	discardPile.insert(discardPile.begin(), m_hand[removeIndex]);
	this->m_hand.erase(m_hand.begin() + removeIndex);

	/*
	if (this->discardScore < this->drawScore)
	{
		cout << "Computer is removing card at index " << discardIndex << endl;
		discardPile.insert(discardPile.begin(), m_hand[discardIndex]);
		m_hand.erase(m_hand.begin() + discardIndex);
	}
	else if (this->discardScore > this->drawScore)
	{
		cout << "Computer is removing card at index " << drawIndex << endl;
		discardPile.insert(discardPile.begin(), m_hand[drawIndex]);
		m_hand.erase(m_hand.begin() + drawIndex);
	}
	else
	{
		cout << "------- Does not make a difference what card to remove so removing a random card ------" << endl;
		srand(time(NULL));
		int turn = rand() % (getHand().size() - 1);

		switch (turn)
		{
		case 0:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 1:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 2:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 3:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 4:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 5:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 6:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 7:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 8:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 9:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 10:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 11:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 12:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		case 13:
			cout << "the computer removed card at index: " << turn << endl;
			discardPile.insert(discardPile.begin(), m_hand.at(turn));
			m_hand.erase(m_hand.begin() + (turn));
			break;
		}

	}
	*/

}

/* *********************************************************************
Function Name: ~Computer
Purpose:computer object destructor
Parameters:

Return Value:
Local Variables:

Algorithm: destruct computer object
Assistance Received:
********************************************************************* */
Computer::~Computer()
{
}
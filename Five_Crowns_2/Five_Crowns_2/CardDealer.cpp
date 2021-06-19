#include "CardDealer.h"

/* *********************************************************************
Function Name: CardDealer
Purpose: card dealer constructor
Parameters:
Return Value:
Local Variables: 
Algorithm:
Assistance Received: 
********************************************************************* */
CardDealer::CardDealer()
{

}

/* *********************************************************************
Function Name: dealCard
Purpose: deal out cards from the two decks
Parameters:
	
Return Value: Card
Local Variables: 
	
Algorithm: see if the first deck is empty if so then pick from second deck. If second is empty then pick from first. If both
are not empty then randomly pick from both
Assistance Received: 
********************************************************************* */
Card CardDealer::dealCard()
{
	srand(time(NULL));
	//randomly deal a card from one of the 2 decks until both are empty
	if (firstDeck.isEmpty())
		if (secondDeck.isEmpty())
		{
			Card emptyCard("45","m");
			return emptyCard;
		}
		else
			return secondDeck.dealCard();
	else
		if (secondDeck.isEmpty())
			return firstDeck.dealCard();
		else
		{
			int choice = rand() % 2;
			if (0 == choice)
				return firstDeck.dealCard();
			else
				return secondDeck.dealCard();
		}
}

/* *********************************************************************
Function Name: updateWildCards
Purpose: upate the wildcards in the deck
Parameters:
	string face : face of the card that is a wildCard
Return Value:
Local Variables:

Algorithm: call the deck function update wildCards on both decks
Assistance Received:
********************************************************************* */
void CardDealer::updateWildCards(string face)
{
	firstDeck.updateWildCards(face);
	secondDeck.updateWildCards(face);
}

/* *********************************************************************
Function Name: getFirstDeck
Purpose: return the first deck
Parameters:

Return Value: Deck
Local Variables:

Algorithm: return firstDeck
Assistance Received:
********************************************************************* */
Deck CardDealer::getFirstDeck()
{
	return firstDeck;
}

/* *********************************************************************
Function Name: getSecondDeck
Purpose: return second deck
Parameters:

Return Value: Deck
Local Variables:

Algorithm:
Assistance Received:
********************************************************************* */
Deck CardDealer::getSecondDeck()
{
	return secondDeck;
}
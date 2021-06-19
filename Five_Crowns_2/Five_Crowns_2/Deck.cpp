/************************************************************
* Name:  Lucas Inglis
* Project : Five Crowns
* Class : Deck.cpp
* Date : 10/22/2019
*************************************************************/
#include "Deck.h"
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine random(seed);

/* *********************************************************************
 Function Name:Deck
 Purpose: deck constructor
 Parameters: none
 Return Value: none
 Local Variables:
	char SUITS, array of possible suits
	char jokerFace, face value of a joker
	char jokerSuit, array of suit values for joker
	int MIN_FACE, min face value of a card
	int MAX_FACE, max face value of a card
 Algorithm:
 Assistance Received: none
 ********************************************************************* */
Deck::Deck() {
	string SUITS[] = { "s" , "c" , "d" , "h" , "t" };
	string jokerFace = "j";
	string jokerSuit[] = { "1","2","3" };
	int MIN_FACE = 3, MAX_FACE = 13;

	for (int j = 0; j < 5; j++) {
		for (int k = MIN_FACE; k <= MAX_FACE; k++) {
			//Card currentCard(to_string(k), SUITS[j]);
			Card card(to_string(k),SUITS[j]);
			m_deckCards.push_back(card);
		}
	}

	for (int w = 0; w < 3; w++) {
		//Card currentCard(jokerFace, jokerSuit[w]);
		Card card(jokerFace, jokerSuit[w]);
		m_deckCards.push_back(card);
	}

	shuffle(m_deckCards.begin(), m_deckCards.end(), random);
}

/* *********************************************************************
Function Name:Deck
Purpose: Custom constructor for deck
Parameters:
	deckCards, vector of card objects
Return Value: none
Local Variables: none
Algorithm:
	set m_deckIndex to 0 and set m_deckCards to deckCards
Assistance Received:
********************************************************************* */
Deck::Deck(vector <Card> deckCards)
{
	m_deckCards = deckCards;
}

/* *********************************************************************
 Function Name:isEmpty
 Purpose: see if deck is empty
 Parameters:none
 Return Value: bool
 Local Variables:none
 Algorithm: if size of m_deckCards is 0 return true else return false
 Assistance Received: none
 ********************************************************************* */
bool Deck::isEmpty()
{
	if (m_deckCards.size() == 0)
	{
		return true;
	 }
	return false;
}

/* *********************************************************************
 Function Name:dealCard
 Purpose: deal a card from the deck
 Parameters: none
 Return Value: Card
 Local Variables:
	Card returnCard, top card of the deck
 Algorithm:
	check to see if deck is empty if not return top card from m_deckCards and remove if from m_deckCards
 Assistance Received: none
 ********************************************************************* */
Card Deck::dealCard()
{

	Card returnCard = m_deckCards.at(0);
	//if deck is empty return null
	if (isEmpty()) //cardVector.size() == 0)
	{
		Card emptyCard("45","m");
		return emptyCard;
	}

	//Get a reference to the first card 

	// remove card from cardVector
	m_deckCards.erase(m_deckCards.begin());

	//return the reference to the removed first card
	return returnCard;
}

/* *********************************************************************
 Function Name: updateWildCards
 Purpose: update decks wild cards
 Parameters: string face, face of the wildcards for the round
 Return Value: none
 Local Variables:
	Card card, one card in the deck to be check to see if it is a wild card
 Algorithm:
	go through each card in m_deckCards and check to see if wild card
 Assistance Received: none
 ********************************************************************* */
void Deck::updateWildCards(string face)
{
	for (Card card : m_deckCards)
		card.updateWildCard(face);
}

/* *********************************************************************
Function Name: printDeck
Purpose: print the deck
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	go through m_deckCards and call printCard() on each card
Assistance Received: none
********************************************************************* */
void Deck::printDeck()
{
	for (int i = 0; i < m_deckCards.size(); i++)
	{
		m_deckCards[i].printCard();
	}
}
/************************************************************
* Name:  Lucas Inglis
* Project : Five Crowns
* Class : Card.cpp
* Date : 12/30/2019
*************************************************************/
#include "Card.h"

/* *********************************************************************
Function Name: Card
Purpose: Defalt constructor for card
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	Set m_Face and m_Suit to spaces
Assistance Received: none
********************************************************************* */
Card::Card() {
	m_Face = " ";
	m_Suit = " ";
}

/* *********************************************************************
Function Name: Card
Purpose: Custom constructor for card
Parameters:
	face, face of the card as a char
	suit, suit of the card as a char
Return Value: none
Local Variables: none
Algorithm:
		call setFace passing in face and setSuit passing in suit
Assistance Received: none
********************************************************************* */
Card::Card(string inFace, string inSuit) {
	if (!(setSuit(inSuit)))
	{
		cout << "Card class reports incorrect suit " << inSuit;
		cout << "         setting suit to default suit" << endl;
	}

	if (!(setFace(inFace)))
	{
		cout << "Card class reports incorrect face " << inFace;
		cout << "         setting suit to default face" << endl;
	}
	//by default this is not a wild card
	if ( (m_Face == "j" || m_Face == "J") && (m_Suit == "1" || m_Suit == "2" || m_Suit == "3"))
	{
		m_Wildcard = true;
	}
	else
	{
		m_Wildcard = false;
	}

}

/* *********************************************************************
Function Name: setFace
Purpose: setFace of the card
Parameters:
	string face, face of the card as a char
Return Value:	none
Local Variables: 
	bool status, if the input was valus and face could be set to it
	int intFace, integer value of the face
Algorithm:
	checks to see if face matches a const of all the possible faces of a card.
	If it does then the face of the card is set to face
Assistance Received: none
********************************************************************* */
bool Card::setFace(string inFace)
{

	bool status = false;
	if (  (inFace == "j" || inFace == "J") && (m_Suit == "1" || m_Suit == "2" || m_Suit == "3"))
	{
		m_Face = inFace;
		status = true;
		return status;
	}


	if (inFace == "x" || inFace == "X")
	{
		inFace = "10";
	}
	else if (inFace == "j" || inFace == "J")
	{
		inFace = "11";
	}
	else if (inFace == "q" || inFace == "Q")
	{
		inFace = "12";
	}
	else if (inFace == "k" || inFace == "K")
	{
		inFace = "13";
	}
	
	int intFace = stoi(inFace);

	//if ( Deck.MINFACE >= 3 && inFace <= 13)
	if ( intFace>= 3 && intFace <= 13)
	{
		m_Face = inFace;
		status = true;
	}
	else
	{
		m_Face = "0";
	}

	return status;
}

/* *********************************************************************
Function Name: setSuit
Purpose: set the suit of the card
Parameters: 
	string inSuit : suit that the card will be set to
Return Value: bool
Local Variables: 
	bool status : status if the card's suit was set right
Algorithm: take in the suit and check to see if its a valid suit if so set the suit and return true
Assistance Received: none
********************************************************************* */
bool Card::setSuit(string inSuit)
{
	//char yes = inSuit[0];
	bool status = false;

	if (inSuit == "s")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "h")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "c")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "d")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "t")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "1")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "2")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "3")
	{
		m_Suit = inSuit;
		status = true;
	}
	else if (inSuit == "m")
	{
		m_Suit = inSuit;
		status = false;
	}

	return status;
}

/* *********************************************************************
Function Name: isWildCard
Purpose: return if card is wildCard
Parameters: none
Return Value:	bool
Local Variables: none
Algorithm:
	returns wildCard bool
Assistance Received: none
********************************************************************* */
 bool Card::isWildCard()
{
	return m_Wildcard;
}

 /* *********************************************************************
Function Name: isValid
Purpose: sees if a card is valid
Parameters: none
Return Value: bool
Local Variables: none
Algorithm: see if you can set the face and suit of the card if you can then return true else return false
Assistance Received: none
********************************************************************* */
 bool Card::isValid()
 {
	 if (!(this->setSuit(this->getSuit())) && !(this->setFace(this->getFace())))
	 {
		 return false;
	 }

	 return true;
 }

 /* *********************************************************************
 Function Name: getSuit
 Purpose: return suit of card
 Parameters: none
 Return Value:	char
 Local Variables: none
 Algorithm:
	 returns suit
 Assistance Received: none
 ********************************************************************* */
 string Card::getSuit()
 {
	 return m_Suit;
 }

 /* *********************************************************************
Function Name: getNumFace
Purpose: return the number value of the face
Parameters:
Return Value: string
Local Variables: none
Algorithm: return the m_Face value since it is a number and not a symbol
Assistance Received: none
********************************************************************* */
 string Card::getNumFace()
 {
	 return m_Face;
 }

 /* *********************************************************************
 Function Name: getFace
 Purpose: return face of card
 Parameters: none
 Return Value: char
 Local Variables: none
 Algorithm: return m_Face
 Assistance Received: none
 ********************************************************************* */
 string Card::getFace()
 {
	 if (m_Face == "10")
	 {
		 return "X";
	 }
	 else if (m_Face == "11")
	 {
		 return "J";
	 }
	 else if (m_Face == "12")
	 {
		 return "Q";
	 }
	 else if (m_Face == "13")
	 {
		 return "K";
	 }
	 else if (m_Face == "0")
	 {
		 return m_Face;
	 }
	 else if (m_Face == "j")
	 {
		 return m_Face;
	 }

	 return m_Face;
 }

 /* *********************************************************************
 Function Name: updateWildCard
 Purpose: update wildcard value of a card
 Parameters: inFace
 Return Value: void
 Local Variables: none
 Algorithm: if face of card equal round number +2 then that card is wild
 Assistance Received: none
 ********************************************************************* */
 void Card::updateWildCard(string inFace)
 {
	 if (m_Face == inFace)
	 {
		 m_Wildcard = true;
	 }
	 else if (inFace == "j")
	 {
		 m_Wildcard == true;
	 }
 }

 /* *********************************************************************
 Function Name: printCard
 Purpose: print the card to the screen
 Parameters: none
 Return Value: void
 Local Variables: none
 Algorithm: cout face and suit of the cars
 Assistance Received: none
 ********************************************************************* */
 void Card::printCard()
 {
	 if (m_Face == "10")
	 {
		 cout << "X" << m_Suit << " ";
	 }
	 else if (m_Face == "11")
	 {
		 cout << "J" << m_Suit << " ";
	 }
	 else if (m_Face == "12")
	 {
		 cout << "Q" << m_Suit << " ";
	 }
	 else if (m_Face == "13")
	 {
		 cout << "K" << m_Suit << " ";
	 }
	 else
	 {
		 cout << m_Face << m_Suit << " ";
	 }

 }
 /* *********************************************************************
Function Name: stringCard
Purpose: take a card and returns string representation of it
Parameters: 
Return Value: string
Local Variables: 
	string card : string representation of the card to return
Algorithm: depending on face value assign face of card to XJKQ or just the number and assign suit to correct suit
Assistance Received: none
********************************************************************* */
 string Card::stringCard()
 {
	 string card;

	 if (m_Face == "10")
	 {
		 card = "X" + m_Suit;
	 }
	 else if (m_Face == "11")
	 {
		 card = "J" + m_Suit;
	 }
	 else if (m_Face == "12")
	 {
		 card = "Q" + m_Suit;
	 }
	 else if (m_Face == "13")
	 {
		 card = "K" + m_Suit;
	 }
	 else
	 {
		 card = m_Face + m_Suit;
	 }

	 return card;
 }

 /* *********************************************************************
 Function Name: compareTo
 Purpose: compares current card to another
 Parameters: Card right
 Return Value: int
 Local Variables: none
 Algorithm: if card is larger then right return 1 if not return -1 else return 0
 Assistance Received: none
 ********************************************************************* */
  int Card::compareTo(Card right)
 {
	 if (m_Face < right.m_Face)
		 return -1;
	 if (m_Face > right.m_Face)
		 return +1;
	 //TO DO: do we want to sort be suit in the order specified in Deck.SUITS
	 return 0;
 }
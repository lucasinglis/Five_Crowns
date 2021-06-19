#include "Human.h"


Human::Human()
{

}

/* *********************************************************************
Function Name: printMenu
Purpose: print the players options
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	cout the players options
Assistance Received: none
********************************************************************* */
void Human::printMenu() {
	cout << "0: Pick from Draw Pile" << endl;
	cout << "1: Pick from Discard Pile" << endl;
	cout << "2: Ask for Help" << endl;
	cout << "3: Quit the game and save" << endl;
}

/* *********************************************************************
 Function Name: drawCard
 Purpose: ask the human what option to do
 Parameters:
	vector <Card> &drawPile : draw pile at the time
	vector <Card> &discardPile : discard pile at the time
 Return Value: int
 Local Variables:
	int option : 
	Computer tempComputer : temp computer to play with humans hand and score
	int tempScore : humans score at the time
	vector <Card> tempDrawPile : temp draw pile 
	vector <Card> tempDiscardPile : temp discard pile
	vector <Card> tempHand : temp of human player hand
	vector <string> tempStringHand : temp of string representation of human hand
	bool goOut : if the tempComputer can go out
 Algorithm:
	1: ask user what they want to do 0) draw from draw pile 1) draw from discard pile 2) ask for help 3) to save the game
	2: if human picks 2 then create a temp computer with the humans hand and try to go out with it. Respond what the computer did back to the 
	   player.
 Assistance Received:
 ********************************************************************* */
int Human::drawCard(vector <Card> &drawPile, vector <Card> &discardPile)
{
	printMenu();
	int option = getMenuValue();
	//draw from the pile and update it
	if (0 == option)
	{
		addCard(drawPile.at(0));
		drawPile.erase(drawPile.begin());
	}
	else if (1 == option)
	{
		addCard(discardPile.at(0));
		discardPile.erase(discardPile.begin());
	}
	else if (2 == option)
	{
		Computer tempComputer;
		int tempScore = getScore();
		vector <Card> tempDrawPile = drawPile;
		vector <Card> tempDiscardPile = discardPile;
		vector <Card> tempHand = m_hand;
		vector <string> tempStringHand = handToString(tempHand);
		bool goOut;
		tempComputer.setHand(tempHand);
		tempComputer.setScore(tempScore);
		tempComputer.setStringHand(tempStringHand);
		tempComputer.setRoundNumber(getRoundNumber());


		cout << "----------------The computers opinion: -------------------------" << endl;
		tempComputer.play(tempDrawPile,tempDiscardPile);
		goOut = tempComputer.canGoOut();
		if (goOut == true)
		{
			cout << "The computer was able to go out with your had and its suggestion so you better listen!!!!!" << endl;
		}
		cout << "Best book and run before computer's opinion: ";
		printBestCombo();
		cout << endl;
		cout << "Best book and run after computer's opinion:  ";
		tempComputer.printBestCombo();
		cout << endl;
		return 2;
	}
	return 1;
}

/* *********************************************************************
 Function Name: discardCard
 Purpose: ask what card to discard from human
 Parameters:
	vector <Card> &discardPile : discard pile at the time
 Return Value:
 Local Variables:
	int response : index of the card the human wants to get rid of
 Algorithm:
	1: ask user for the index of the card they want to get rid of (1 -> length of hand)
	2: remove card at that index
 Assistance Received:
 ********************************************************************* */
void Human::discardCard(vector <Card> &discardPile)
{
	int response;
	do
	{
		printHand();
		cout << "Please enter which card to discard 1 -> " << m_hand.size() << ": ";
		cin >> response;
	} while (!(response >= 1 && response <= getHand().size()));

	//remove the last card in hand to discard pile
	discardPile.insert(discardPile.begin(), getHand().at(response - 1));
	m_hand.erase(m_hand.begin()+(response - 1));
}

/* *********************************************************************
Function Name: getMenuValue
Purpose: get the input of what the player want to do
Parameters: none
Return Value: menu option of the user
Local Variables:
	menuValue, number value of the option user picked
	stringMenuChoice, string value of the option user picked to be converted to int
Algorithm:
	cin player's option and validate its a correct one
Assistance Received: none
********************************************************************* */
int Human::getMenuValue() {
	int menuValue;
	string stringMenuChoice;

	do {
		cout << "Please enter what u want to do: " << endl;
		cin >> stringMenuChoice;
		menuValue = stoi(stringMenuChoice);
	} while (!(menuValue == 0 || menuValue == 1 || menuValue == 2 || menuValue == 3));

	return menuValue;
}
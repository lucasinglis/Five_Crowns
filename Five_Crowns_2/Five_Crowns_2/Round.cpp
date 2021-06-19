#include "Round.h"

int Round::m_roundIndex = 1;
int Round::m_Round_ComputerScore = 0;
int Round::m_Round_HumanScore = 0;
bool Round::m_playerTurn = true;

/* *********************************************************************
 Function Name: Round
 Purpose: constructor for round
 Parameters:
	int roundIndex : current round number
	Human* human_ptr : human player
	Computer* computer_ptr : computer player
	bool next_player : the next player of the game
	bool newGame : if the game was a save state or not
 Return Value:
 Local Variables:

 Algorithm:
	1: set rounds memeber variables to their proper perameters
	2: if the round index is 1 and next_player is true then set human as the first player in the players array else set the computer as the first
 Assistance Received:
 ********************************************************************* */
Round::Round(int roundIndex, Human* human_ptr, Computer* computer_ptr, bool next_player,bool newGame)
{
	m_Human = *human_ptr;
	m_Computer = *computer_ptr;
	m_roundIndex = roundIndex;
	m_playerTurn = next_player;
	isNewGame = newGame;

	if (m_roundIndex == 1)
	{
		if (next_player == true)
		{
			players[0] = &m_Human;
			players[1] = &m_Computer;

		}
		else
		{
			players[0] = &m_Computer;
			players[1] = &m_Human;
		}
	}
	else
	{
		if (next_player == true)
		{
			players[0] = &m_Human;
			players[1] = &m_Computer;

		}
		else
		{
			players[0] = &m_Computer;
			players[1] = &m_Human;
		}
	}
}

/* *********************************************************************
 Function Name: Round
 Purpose: constructor for round when there is a save file
 Parameters:
	int roundIndex : current round number
	Human* human_ptr : human player
	Computer* computer_ptr : computer player
	bool next_player : the next player of the game
	vector<Card> discard : discard pile for the round given by the save file
	vector<Card> draw : draw pile for the round that was given by the save file
	bool newGame : if the game was a save state or not
 Return Value:
 Local Variables:

 Algorithm:
	1: set all rounds member variables to their proper parameters
	2: call updateWild to set the wildCards for the round
	2: if the round index is 1 and next_player is true then set human as the first player in the players array else set the computer as the first
 Assistance Received:
 ********************************************************************* */
Round::Round(int roundIndex, Human* human_ptr, Computer* computer_ptr, bool next_player, vector<Card> discard, vector<Card> draw,bool newGame)
{
	m_Human = *human_ptr;
	m_Computer = *computer_ptr;
	m_roundIndex = roundIndex;
	m_playerTurn = next_player;
	m_roundDrawDeck = draw;
	m_roundDiscardDeck = discard;
	isNewGame = newGame;
	updateWild();

	if (m_roundIndex == 1)
	{
		if (next_player == true)
		{
			players[0] = &m_Human;
			players[1] = &m_Computer;

		}
		else
		{
			players[0] = &m_Computer;
			players[1] = &m_Human;
		}
	}
	else
	{
		if (next_player == true)
		{
			players[0] = &m_Human;
			players[1] = &m_Computer;

		}
		else
		{
			players[0] = &m_Computer;
			players[1] = &m_Human;
		}
	}


}

/* *********************************************************************
 Function Name: setUpRound
 Purpose: set up a round
 Parameters:

 Return Value:
 Local Variables:
	vector<Card>emptyHand : empty hand to give to players so there is no garbage numbers in their hand
	vector<string>emptyStringHand : empty hand to give to players so there is no garbage numbers in their hand
	Card nextCard : next card given by the cardDealer
 Algorithm:
	1: set players hands and string hands to empty vectors for clearing
	2: add round number + 2 cards to each player from the m_Dealer
	3: put the rest on the draw pile and the last one on the discard
 Assistance Received:
 ********************************************************************* */
void Round::setUpRound()
{
	vector<Card>emptyHand;
	vector<string>emptyStringHand;
	players[0]->setHand(emptyHand);
	players[1]->setHand(emptyHand);
	players[0]->setStringHand(emptyStringHand);
	players[1]->setStringHand(emptyStringHand);


	for (int count = 0; count < m_roundIndex + 2; count++)
	{
		players[0]->addCard(m_Dealer.dealCard());
		players[1]->addCard(m_Dealer.dealCard());
	}

	Card nextCard = m_Dealer.dealCard();
	while (false != nextCard.isValid())
	{
		m_roundDrawDeck.push_back(nextCard);
		nextCard = m_Dealer.dealCard();
	}

	m_roundDiscardDeck.push_back(m_roundDrawDeck.at(0));
	m_roundDrawDeck.erase(m_roundDrawDeck.begin());

	updateWild();

	players[0]->setRoundNumber(m_roundIndex);
	players[1]->setRoundNumber(m_roundIndex);

	printRound();
}

/* *********************************************************************
 Function Name: updateWild
 Purpose: update wild card in the draw and discard decks
 Parameters:

 Return Value:
 Local Variables:

 Algorithm:
	1: go through each deck and call updateWildCard on each card in the deck with the string representation of the round number
 Assistance Received:
 ********************************************************************* */
void Round::updateWild()
{
	for (int i = 0; i < m_roundDrawDeck.size(); i++)
	{
		m_roundDrawDeck[i].updateWildCard(to_string(m_roundIndex + 2));
	}
	
	for (int i = 0; i < m_roundDiscardDeck.size(); i++)
	{
		m_roundDiscardDeck[i].updateWildCard(to_string(m_roundIndex + 2));
	}

}

/* *********************************************************************
 Function Name: startRound
 Purpose: starts a round
 Parameters:

 Return Value:
 Local Variables:

 Algorithm:
	1: if isNewGame true then its a new round and call setUpRound
	2: if not then just play the round
 Assistance Received:
 ********************************************************************* */
void Round::startRound()
{ 

	if (isNewGame == true)
	{
			setUpRound();	
			//start the Round
			//once round it done set serialized bool to false
	}
	playRound();
}

/* *********************************************************************
 Function Name: saveGame
 Purpose: save a game to a file
 Parameters:

 Return Value:
 Local Variables:
	ofstream saved_file : ofstream to write to the file
 Algorithm:
 Assistance Received:
 ********************************************************************* */
void Round::saveGame() {
	ofstream saved_file;
	saved_file.open("./saveGame.txt");
	saved_file << "Round: " << m_roundIndex << endl;
	saved_file << endl;
	saved_file << "Computer: " << endl;
	saved_file << "    Score: " << m_Computer.getScore() << endl;
	saved_file << "    Hand: " << cardsToString(m_Computer.getHand()) << endl;
	saved_file << endl;
	saved_file << "Human: " << endl;
	saved_file << "    Score: " << m_Human.getScore() << endl;
	saved_file << "    Hand: " << cardsToString(m_Human.getHand()) << endl;
	saved_file << endl;
	saved_file << "Draw Pile: " << cardsToString(m_roundDrawDeck) << endl;
	saved_file << endl;
	saved_file << "Discard Pile: " << cardsToString(m_roundDiscardDeck) << endl;
	saved_file << endl;
	if (m_playerTurn == true)
	{
		saved_file << "Next Player: Human" << endl;
	}
	else if (m_playerTurn == false)
	{
		saved_file << "Next Player: Computer" << endl;
	}
	exit(0);
}

/* *********************************************************************
 Function Name:cardsToString
 Purpose: take a vector of cards and return them as on long string
 Parameters:
	vector <Card> cards : card to be sent as a string
 Return Value: string
 Local Variables:
	cardsInString
 Algorithm:
	1: call stringCard on all cards in the vector and concatenate it to one long string
 Assistance Received:
 ********************************************************************* */
string Round::cardsToString(vector <Card> cards)
{
	string cardsInString;

	for (int i =0;i<cards.size();i++)
	{
		Card currentCard = cards[i];
		cardsInString = cardsInString + currentCard.stringCard() + " ";
	}

	return cardsInString;
}

/* *********************************************************************
 Function Name: playRound
 Purpose: play a round
 Parameters:

 Return Value:
 Local Variables:
	int nextPlayerIndex : index in the players array
	int dummy : dummy int since play() returns an int
	bool firstGoOut : if the first player can go out
	bool secondGoOut : if second player can go out
	string save_game : response for the player to say if they wanted to save the game
 Algorithm:
	1: ask player if they want to save game
	2: check if first player can go out without making a turn
	3: let first player play
	4: check if first player can go out
	5: if so give second player a chance to play and see if they can go out as well
	6: print out best book and run combo of each player
	7: set the m_playerTurn to whoever went out first (true = human | false = computer)
	8: add the appropriate points to each players score and end the round
 Assistance Received:
 ********************************************************************* */
void Round::playRound()
{
	int nextPlayerIndex = 0;
	int dummy = 0;
	bool firstGoOut = false;
	bool secondGoOut = false;
	string save_game;

	do
	{
		cout << "Do you wish to save the game 1 for yes 2 for no:" << endl;
		cin >> save_game;
	} while ( !( (stoi(save_game)==1) || (stoi(save_game) == 2) ) );

	if (stoi(save_game)==1)
	{
		saveGame();
	}


	while (!firstGoOut && !secondGoOut)//players[nextPlayerIndex]->getCanOut() != 0)
	{

		firstGoOut = players[nextPlayerIndex]->canGoOut();
		
		if (firstGoOut)
		{
			cout << "A Player Went Out!! Giving other players a last turn!" << endl;
			cout << "-----------------------------------" << endl;
			cout << "Draw Deck: ";
			printDeck(m_roundDrawDeck);
			cout << endl;
			cout << "Discard Deck: ";
			printDeck(m_roundDiscardDeck);
			cout << endl;
			cout << "Players best book/run combo : ";
			players[nextPlayerIndex+1]->printBestCombo();
			cout << endl;
			dummy = players[nextPlayerIndex + 1]->play(m_roundDrawDeck, m_roundDiscardDeck);
			//check books and runs then calculate scores 
			secondGoOut = players[nextPlayerIndex + 1]->canGoOut();
			if (m_playerTurn == true)
			{
				m_playerTurn == true;
			}
			else if (m_playerTurn == false)
			{
				m_playerTurn == false;
			}
			break;
		}

		dummy = players[nextPlayerIndex]->play(m_roundDrawDeck, m_roundDiscardDeck);
		firstGoOut = players[nextPlayerIndex]->canGoOut();
		cout << "Players best book/run combo : ";
		players[nextPlayerIndex]->printBestCombo();
		cout << endl;
		if (firstGoOut)
		{
			cout << "A Player Went Out!! Giving other players a last turn!" << endl;
			cout << "-----------------------------------" << endl;
			cout << "Draw Deck: ";
			printDeck(m_roundDrawDeck);
			cout << endl;
			cout << "Discard Deck: ";
			printDeck(m_roundDiscardDeck);
			cout << endl;
			cout << "Players best book/run combo : ";
			players[nextPlayerIndex+1]->printBestCombo();
			cout << endl;
			dummy = players[nextPlayerIndex + 1]->play(m_roundDrawDeck, m_roundDiscardDeck);
			//check books and runs then calculate scores 
			secondGoOut = players[nextPlayerIndex + 1]->canGoOut();
			if (m_playerTurn == true)
			{
				m_playerTurn == true;
			}
			else if (m_playerTurn == false)
			{
				m_playerTurn == false;
			}
			break;
		}

		printRound();

		secondGoOut = players[nextPlayerIndex + 1]->canGoOut();

		if (secondGoOut)
		{
			cout << "A Player Went Out!! Giving other players a last turn!" << endl;
			cout << "-----------------------------------" << endl;
			cout << "Draw Deck: ";
			printDeck(m_roundDrawDeck);
			cout << endl;
			cout << "Discard Deck: ";
			printDeck(m_roundDiscardDeck);
			cout << endl;
			cout << "Players best book/run combo : ";
			players[nextPlayerIndex]->printBestCombo();
			cout << endl;
			dummy = players[nextPlayerIndex]->play(m_roundDrawDeck, m_roundDiscardDeck);
			//check books and runs then calculate scores calculate scores 
			firstGoOut = players[nextPlayerIndex]->canGoOut();
			if (m_playerTurn == true)
			{
				m_playerTurn == false;
			}
			else if (m_playerTurn == false)
			{
				m_playerTurn == true;
			}
			break;
		}

		dummy = players[nextPlayerIndex+1]->play(m_roundDrawDeck, m_roundDiscardDeck);
		secondGoOut = players[nextPlayerIndex + 1]->canGoOut();
		cout << "Players best book/run combo : ";
		players[nextPlayerIndex+1]->printBestCombo();
		cout << endl;
		//call firstGoOut = canGoOut
		//secondGoOut = players[nextPlayerIndex + 1]->canGoOut();
		if (secondGoOut)
		{
			cout << "A Player Went Out!! Giving other players a last turn!" << endl;
			cout << "-----------------------------------" << endl;
			cout << "Draw Deck: ";
			printDeck(m_roundDrawDeck);
			cout << endl;
			cout << "Discard Deck: ";
			printDeck(m_roundDiscardDeck);
			cout << endl;
			cout << "Players best book/run combo : ";
			players[nextPlayerIndex]->printBestCombo();
			cout << endl;
			dummy = players[nextPlayerIndex]->play(m_roundDrawDeck, m_roundDiscardDeck);
			//check books and runs then calculate scores calculate scores 
			firstGoOut = players[nextPlayerIndex]->canGoOut();
			if (m_playerTurn == true)
			{

			}
			else if (m_playerTurn == false)
			{

			}
			break;
		}

		//otherwise switch players
		//nextPlayerIndex = (nextPlayerIndex + 1) % 2;

		//otherwise ask if game should be serialized
		printRound();

	}
	


	//print the books and runs, add scores and such then start new round

	if (m_playerTurn == true)
	{
		int temp = players[nextPlayerIndex]->getScore();
		temp += players[nextPlayerIndex]->getHandScore();
		players[nextPlayerIndex]->setScore(temp);
		cout << "After the round the human's score is: " << players[nextPlayerIndex]->getScore() << endl;
		cout << "Human's book/run combo was: " << endl;
		players[nextPlayerIndex]->printBestCombo();
		cout << endl;

		int temp2 = players[nextPlayerIndex+1]->getScore();
		temp2 += players[nextPlayerIndex+1]->getHandScore();		
		players[nextPlayerIndex+1]->setScore(temp2);
		cout << "After the round the computer's score is: " << players[nextPlayerIndex +1]->getScore() << endl;
		cout << "Computer's book/run combo was: " << endl;
		players[nextPlayerIndex+1]->printBestCombo();
		cout << endl;
	}
	else if (m_playerTurn == false)
	{
		int temp3 = players[nextPlayerIndex]->getScore();
		temp3 += players[nextPlayerIndex]->getHandScore();
		players[nextPlayerIndex]->setScore(temp3);
		cout << "After the round the computer's score is: " << players[nextPlayerIndex]->getScore() << endl;
		cout << "Computer's book/run combo was: " << endl;
		players[nextPlayerIndex]->printBestCombo();
		cout << endl;

		int temp4 = players[nextPlayerIndex + 1]->getScore();
		temp4 += players[nextPlayerIndex + 1]->getHandScore();
		players[nextPlayerIndex + 1]->setScore(temp4);
		cout << "After the round the Human's score is: " << players[nextPlayerIndex + 1]->getScore() << endl;
		cout << "Human's book/run combo was: " << endl;
		players[nextPlayerIndex+1]->printBestCombo();
		cout << endl;
	}



	isNewGame = true;
}

/* *********************************************************************
 Function Name:printDeck
 Purpose: print a vector of cards to the screen
 Parameters:
	vector <Card> deck : deck to be printed to the screen
 Return Value:
 Local Variables:

 Algorithm:
	1: call printCard on every card in the deck
 Assistance Received:
 ********************************************************************* */
void Round::printDeck(vector <Card> deck)
{
	for (int i = 0; i < deck.size(); i++)
	{
		deck[i].printCard();
	}
}

/* *********************************************************************
 Function Name:getNextPlayer
 Purpose: get the next player
 Parameters:

 Return Value: bool
 Local Variables:

 Algorithm:
	1: return m_playerTurn member variable
 Assistance Received:
 ********************************************************************* */
bool Round::getNextPlayer()
{
	return m_playerTurn;
}

/* *********************************************************************
 Function Name: getHuman
 Purpose: return human player object
 Parameters:

 Return Value: Human
 Local Variables:

 Algorithm:
	1: return m_Human member variable
 Assistance Received:
 ********************************************************************* */
Human Round::getHuman()
{
	return m_Human;
}

/* *********************************************************************
 Function Name:getComputer
 Purpose: return computer player object
 Parameters:

 Return Value: Computer
 Local Variables:

 Algorithm:
	1: return m_Computer member variable
 Assistance Received:
 ********************************************************************* */
Computer Round::getComputer()
{
	return m_Computer;
}

/* *********************************************************************
 Function Name: getRound
 Purpose: return round number
 Parameters:

 Return Value: int 
 Local Variables:
	
 Algorithm:
	1: return m_roundIndex member variable
 Assistance Received:
 ********************************************************************* */
int Round::getRound()
{
	return m_roundIndex;
}
/* *********************************************************************
Function Name: printRound
Purpose: print all info on the round
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	cout all information about a round
Assistance Received: none
********************************************************************* */
void Round::printRound() {
	cout << "Round: " << m_roundIndex;
	cout << endl;
	cout << "Computer:" << endl;
	cout << "\tScore: " << m_Computer.getScore() << endl;
	cout << "\tHand: ";
	m_Computer.printHand();
	cout << endl;

	cout << endl;
	cout << "Human:" << endl;
	cout << "\tScore: " << m_Human.getScore() << endl;
	cout << "\tHand: ";
	m_Human.printHand();
	cout << endl;

	cout << endl;
	cout << "Draw Pile: ";
	printDeck(m_roundDrawDeck);
	cout << endl;
	cout << endl;
	cout << "Discard Pile: ";
	printDeck(m_roundDiscardDeck);
	cout << endl;
	cout << endl;
}
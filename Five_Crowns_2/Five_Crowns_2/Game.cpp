#include "Game.h"

int Game::human_score;
int  Game::computer_score;

Game::Game()
{
	//create two players
	//human = new Human();
	//no class for computer so it is just a player
	//computer = new Computer();

	//default round number
	m_roundCount = 1;

}

/* *********************************************************************
Function Name: StartGame
Purpose: to start the game and see if user wants to load in a save file
Parameters: none
Return Value: none
Local Variables:
	gameFile, the y/n answer for if the user wants to load a file
Algorithm:
	get the user input and validate input then call StartNewGame for y or LoadGameFile for
	n
Assistance Received: none
********************************************************************* */
void Game::StartGame() {
	cout << "------------------Welcome to 5 Crowns------------------" << endl;

	char gameFile;

	do {
		cout << "Do you want to enter a save file (y/n)?" << endl;
		cin >> gameFile;
		gameFile = tolower(gameFile);
	} while (!(gameFile == 'y' || gameFile == 'n'));

	if (gameFile == 'y')
	{
		
		string fileName;
		m_newGame = false;
		cout << "Please enter the file path or name: " << endl;
		cin >> fileName;
		ifstream load;
		load.open(fileName);
		while (load.fail())
		{
			cout << "Please entr a valid file path or name: " << endl;
			cin >> fileName;
			load.open(fileName);
		}

		loadGame(fileName);
		newGame();
	}
	else if (gameFile == 'n')
	{
		cout << "A new game has started." << endl;
		m_newGame = true;
		newGame();
	}

}

/* *********************************************************************
 Function Name: newGame
 Purpose: start a new game
 Parameters: 
	
 Return Value: 
 Local Variables:
	Round round : round object for the round
 Algorithm: 
	1: if m_newGame is true then do the cointoss and start the game
	2: if m_newGame is false then set the round numbers in human and computer players
	3: play the round with the current state of the game
	4: once loaded round is ended set m_newGame to true
	5: play a new round 
 Assistance Received: 
 ********************************************************************* */
void Game::newGame()
{
	if (m_newGame == true)
	{
		next_player = coinToss();

		for (; m_roundCount <= 11; m_roundCount++)
		{
			//create  a round
			Round round(m_roundCount, &human, &computer, next_player,m_newGame);
			round.startRound();
			human.setScore(round.getHuman().getScore());
			computer.setScore(round.getComputer().getScore());
			next_player = round.getNextPlayer();
			//play the round

		}
	}
	else if (m_newGame == false)
	{
		human.setRoundNumber(m_roundCount);
		computer.setRoundNumber(m_roundCount);

		for (; m_roundCount <= 11; m_roundCount++)
		{
			if (m_newGame == true)
			{
				//create  a round
				Round round(m_roundCount, &human, &computer, next_player, m_newGame);
				round.startRound();
				human.setScore(round.getHuman().getScore());
				computer.setScore(round.getComputer().getScore());
				next_player = round.getNextPlayer();
				//play the round
			}
			else if (m_newGame == false)
			{
				Round round(m_roundCount, &human, &computer, next_player, inDiscardPile, inDrawPile, m_newGame);
				round.printRound();
				round.startRound();
				m_newGame = true;
				human.setScore(round.getHuman().getScore());
				computer.setScore(round.getComputer().getScore());
				next_player = round.getNextPlayer();
			}

			

		}

	}

	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;
	cout << "After all rounds, the human score is: " << human.getScore() << endl;
	cout << "After all rounds, the computer score is: " << computer.getScore() << endl;

	if (human.getScore() < computer.getScore()) {
		cout << "Human player won the game" << endl;
	}

	else if (human.getScore() > computer.getScore()) {
		cout << "Computer player won the game " << endl;
	}

	else {
		cout << "The game ended in a tie " << endl;
	}

	cout << "-------------------------------------Thank you for playing-----------------------------------------------------------------" << endl;

}

/* *********************************************************************
 Function Name: getComputerScore
 Purpose: return computer_score
 Parameters:

 Return Value:
 Local Variables:

 Algorithm: return computer_score
 Assistance Received:
 ********************************************************************* */
int Game::getComputerScore()
{
	return computer_score;
}

/* *********************************************************************
 Function Name: getHumanScore
 Purpose: return human_score
 Parameters:

 Return Value:
 Local Variables:

 Algorithm: return human_score
 Assistance Received:
 ********************************************************************* */
int Game::getHumanScore()
{
	return human_score;
}

/* *********************************************************************
 Function Name: getRoundNum
 Purpose: return m_roundCount
 Parameters:

 Return Value:
 Local Variables:

 Algorithm: return m_roundCount
 Assistance Received:
 ********************************************************************* */
int Game::getRoundNum()
{
	return m_roundCount;
}

/* *********************************************************************
 Function Name: loadGame
 Purpose: load a save file
 Parameters:
	string fileName
 Return Value:
 Local Variables:
	ifstream inFile : file to be loaded
	string singleLine : single line of the file
	string nextPlay : next player
	vector <string> discardDeck : discard deck from the file
	vector <string> drawDeck : draw deck from the file
	vector <string> playerHand : a player hand from the file
	string computerScoreLine : line where computer score is on
	string humanScoreLine : line where human score is on
	string computerHandLine : line where computer hand is on
	string humanHandLine : line where human hand is on
	stringstream line : stringstream to be searched for specific words
	string word : single word in the line
	vector<Card> computerCards : hand of computer from file in card objects
	int computerScore : computer score from file in int
	vector<Card> humanCards hand of human from file in card objects
	int humanScore human score from file
 Algorithm: 
	1: search through the file for specific keywords until the end
	2: if keyword is found extract the data and set the proper variables to what the save file said
 Assistance Received:
 ********************************************************************* */
void Game::loadGame(string fileName)
{
	ifstream inFile;
	string singleLine;
	string nextPlay;
	vector <string> discardDeck;
	vector <string> drawDeck;
	vector <string> playerHand;
	string computerScoreLine;
	string humanScoreLine;
	string computerHandLine;
	string humanHandLine;

	inFile.open(fileName);

	if (!inFile)
	{
		cout << "Cannot read save file" << endl;
		exit(1);
	}

	while (getline(inFile, singleLine))
	{
		stringstream line(singleLine);
		string word;
		line >> word;

		if (word.find("Round") != string::npos)
		{
			line >> m_roundCount;
		}

		if (word.find("Computer") != string::npos)
		{
			vector<Card> computerCards;
			int computerScore;

			getline(inFile, computerScoreLine);
			stringstream temp(computerScoreLine);
			string tempWord;
			temp >> tempWord >> computerScore;

			getline(inFile, computerHandLine);
			stringstream temp2(computerHandLine);
			temp2 >> tempWord;
			while (temp2 >> tempWord)
			{
				playerHand.push_back(tempWord);
			}

			computerCards = createCardVector(playerHand);
			computer.setHand(computerCards);
			computer.setScore(computerScore);
			playerHand.clear();
		}

		if (word.find("Human") != string::npos)
		{
			vector<Card> humanCards;
			int humanScore;

			getline(inFile, humanScoreLine);
			stringstream temp(humanScoreLine);
			string tempWord;
			temp >> tempWord >> humanScore;

			getline(inFile, humanHandLine);
			stringstream temp2(humanHandLine);
			temp2 >> tempWord;
			while (temp2 >> tempWord)
			{
				playerHand.push_back(tempWord);
			}

			humanCards = createCardVector(playerHand);
			human.setHand(humanCards);
			human.setScore(humanScore);
			playerHand.clear();

		}

		if (word.find("Next") != string::npos)
		{
			line >> word;
			line >> word;
			nextPlay = word;

			if (nextPlay == "Human")
			{
				next_player = true;
			}
			else if (nextPlay == "Computer")
			{
				next_player = false;
			}
		}

		if (word.find("Discard") != string::npos)
		{
			line >> word;
			while (line >> word)
			{
				discardDeck.push_back(word);
			}
			bool isDiscard = true;
			inDiscardPile = createCardVector(discardDeck);

		}

		if (word.find("Draw") != string::npos)
		{
			line >> word;
			while (line >> word)
			{
				drawDeck.push_back(word);
			}
			bool isDiscard = false;
			inDrawPile = createCardVector(drawDeck);
		}
	}

	inFile.close();
}

/* *********************************************************************
 Function Name: createCardVector
 Purpose: create a vector of cards from a vector of strings
 Parameters:
	vector<string> stringCards : cards in string form to be converted to card objects
 Return Value: vector <Card>
 Local Variables:
	vector <Card> cards : vector of cards that were once strings
	char tempsuit : suit of the card
	char tempface : face of the card
	string face : string representation of the face
	string suit : string representation of the suit
	Card newCard : card object to be pushed to cards
 Algorithm:
	1: take the first character from the string and put it into tempSuit. Do the same for face
	2: convert them to strings
	3: create a card with the face and suit values and then push it onto cards
 Assistance Received:
 ********************************************************************* */
vector <Card> Game::createCardVector(vector<string> stringCards)
{
	vector <Card> cards;
	char tempsuit;
	char tempface;
	//string suit;
	//string face;

	for (int i = 0; i < stringCards.size(); i++)
	{
		tempsuit = tolower(stringCards[i][0]);
		tempface = tolower(stringCards[i][1]);
		string face(1,tempface);
		string suit(1,tempsuit);
		Card newCard(suit, face);
		cards.push_back(newCard);
	}

	return cards;
}

/* *********************************************************************
 Function Name: coinToss
 Purpose: do the coun toss
 Parameters:

 Return Value: bool
 Local Variables:
	int response : responce from the player
	int coin : 1 for heads 2 for tails and random for which one it gets
 Algorithm:
	1: as user for heads(1) or tails(2)
	2: randomly pick one or two and set value to coin
	3: if player gusses correctly then they go first if not then computer goes first
 Assistance Received:
 ********************************************************************* */
bool Game::coinToss()
{
	int response;
	do
	{
		cout << "Please enter 0 for heads and 1 for tails: " << endl;
		cin >> response;

	} while (response != 0 && response != 1);

	srand(time(NULL));
	int coin = rand() % 2;
	if (coin == 0)
	{
		cout << "The coin landed on: Heads" << endl;
	}
	else if (coin == 1)
	{
		cout << "The coin landed on: Tails"<< endl;
	}
	if (coin == response)
	{
		cout << "You guess right you go first"<< endl;
		return true;
	}
	else if (coin != response)
	{
		cout << "You guess wrong computer goes first" << endl;
		return false;
	}
	return true;
}
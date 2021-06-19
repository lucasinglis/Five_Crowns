#include "Player.h"


/* *********************************************************************
Function Name: Player
Purpose: player default constructor
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	set member variables to default values
Assistance Received: none
********************************************************************* */
Player::Player() {
	m_playerScore = 0;
	m_hand.clear();

}

/* *********************************************************************
 Function Name: drawCard
 Purpose: virtual function for drawCard
 Parameters:
	vector <Card> &drawPile : draw pile at the time
	vector <Card> &discardPile : discard pile at the time
 Return Value:
 Local Variables:
	
 Algorithm:
 Assistance Received:
 ********************************************************************* */
int Player::drawCard(vector <Card> &drawPile, vector <Card> &discardPile)
{
	//add first card in draw
	addCard(drawPile.at(0));
	drawPile.erase(drawPile.begin());

	return 1;
}

/* *********************************************************************
 Function Name: addCard
 Purpose: add a card to hand
 Parameters:
	Card newCard : card to be added to hand
 Return Value:
 Local Variables:

 Algorithm:
	1: push_back card given to hand
 Assistance Received:
 ********************************************************************* */
void Player::addCard(Card newCard)
{
	m_hand.push_back(newCard);

}

/* *********************************************************************
 Function Name: discardCard
 Purpose: virtual function for discardCard
 Parameters:
	vector <Card> &discardPile : discard card at the time
 Return Value:
 Local Variables:

 Algorithm:
 Assistance Received:
 ********************************************************************* */
void Player::discardCard(vector <Card> &discardPile)
{
	//remove the last card in hand to discard pile
	discardPile.insert(discardPile.begin(), m_hand.at(0));
	m_hand.erase(m_hand.begin());
}

/* *********************************************************************
 Function Name: getHand
 Purpose: return players hand
 Parameters:

 Return Value: vector <Card>
 Local Variables:

 Algorithm:
 Assistance Received:
 ********************************************************************* */
vector <Card> Player::getHand()
{
	return m_hand;
}

/* *********************************************************************
 Function Name: setRoundNumber
 Purpose: set the round number
 Parameters:
	int roundNumber : new round number
 Return Value:
 Local Variables:

 Algorithm:
	1: set m_roundNum to roundNumber
 Assistance Received:
 ********************************************************************* */
void Player::setRoundNumber(int roundNumber)
{
	m_roundNum = roundNumber;
}

/* *********************************************************************
 Function Name: play
 Purpose: play the turn of the player 
 Parameters: 
	vector <Card> &drawPile : draw pile at the time
	vector <Card> &discardPile : discard pile at the time
 Return Value: int
 Local Variables:
	int option : option of the player
 Algorithm:
	1) based on the return value from drawCard either call discard card or let the player play again
 Assistance Received:
 ********************************************************************* */
int Player::play(vector <Card> &drawPile, vector <Card> &discardPile)
{
	//draw a card from draw or discard

	int option = drawCard(drawPile, discardPile);
	//discard a card

	if (1 == option)
	{
		discardCard(discardPile);
	}
	else if (2 == option)
	{
		play(drawPile, discardPile);
	}

	//check if all books and runs
	//goOut = checkHand(hand);
	//report if you can go out
	//if (goOut == 0)
	//{
		//System.out.println("You Went Out");
		//canOut = 0;
		//return 1;
	//}

	return 1;
}

/* *********************************************************************
 Function Name: handToString
 Purpose: take a vector of cards and turn them into a vector of string representations of the cards
 Parameters:
	vector <Card> c_hand : current hand of cards
 Return Value: vector <string>
 Local Variables:
	vector <string> s_hand : string hand to be sent back
	vector<Card>::iterator i : vector iterator to go through all cards in c_hand
 Algorithm:
	1: go through each card in c_hand can call stringCard on them to then push onto s_hand
 Assistance Received:
 ********************************************************************* */
vector<string> Player::handToString(vector <Card> c_hand)
{
	vector <string> s_hand;
	vector<Card>::iterator i;
	for ( i = c_hand.begin(); i != c_hand.end(); i++)
	{
		string card = i->stringCard();
		s_hand.push_back(card);
	}

	return s_hand;

}

/* *********************************************************************
 Function Name: canGoOut
 Purpose: see if player can go out
 Parameters:

 Return Value: bool
 Local Variables:
	
 Algorithm:
	1: get the number of wildcards and jokers
	2: get the score of the current cards in the players hand
	3: set the string representation of the players hand into m_string_hand
	4: call best combo to get the best book run combo the player has
	5: if handScore is 0 return true that the player can go out else return false
 Assistance Received:
 ********************************************************************* */
bool Player::canGoOut()
{
	numWildCards();
	numJokers();
	handScore = scoreOfHand(m_hand);
	m_string_hand = handToString(m_hand);

	bestHandCombo(m_hand);

	if (handScore == 0)
	{
		return true;
	}

	return false;
}

/* *********************************************************************
 Function Name: getHandScore
 Purpose: get score of cards in players hand
 Parameters:

 Return Value: int
 Local Variables:

 Algorithm:
	return handScore
 Assistance Received:
 ********************************************************************* */
int Player :: getHandScore()
{
	return handScore;
}

/* *********************************************************************
 Function Name: printBestCombo
 Purpose: print players best book run combo
 Parameters:

 Return Value:
 Local Variables:
	
 Algorithm:
	1: cout all the cards in bestCombo Player variable since they are strings
 Assistance Received:
 ********************************************************************* */
void Player::printBestCombo()
{
	for (int i = 0; i < bestCombo.size(); i++)
	{
		cout << bestCombo[i] << " ";
	}
}

/* *********************************************************************
 Function Name: bestHandCombo
 Purpose: get best combo in players hand
 Parameters:
	vector<Card> p_hand : players hand in card objects
 Return Value: int
 Local Variables:
	vector<string> stringHandCopy : string representation of players hand
	vector<vector<Card>> books_runs_in_hand : all book run combos in players hand
	vector<vector<string>> booksRuns : all book run combos in players hand in string form
	vector<Card> recursiveHand : hand without a book/run combo to be used to call back bestHandCombo
 Algorithm:
	1: send the string version of the player hand to possible combo to get all book/run combos
	2: if books_runs_in_hand is 0 then get the score of the hand
	3: if its less than the current best hand score then set the bestCombo to the current combo and set handScore to score
	4: else remove the current book/run combo and call bestHandCombo again
 Assistance Received:
 ********************************************************************* */
int Player::bestHandCombo(vector <Card> p_hand)
{	
	//m_string_hand = handToString(p_hand);
	vector<string> stringHandCopy;
	stringHandCopy = handToString(p_hand);
	vector<vector<Card>> books_runs_in_hand = possibleCombo(stringHandCopy);

	if (books_runs_in_hand.size() == 0)
	{
		int score = scoreOfHand(p_hand);

		if (score <= handScore)
		{
			vector<vector<string>> booksRuns;
			booksRuns.push_back(stringHandCopy);
			vector<string> temp;

			for (int i =0;i<m_string_hand.size();i++)
			{
				string currentString = m_string_hand[i];
				if (!(find(stringHandCopy.begin(), stringHandCopy.end(), currentString) != stringHandCopy.end()))
				{
					temp.push_back(currentString);
				}
			}
			if (score < handScore)
			{
				bestCombo = temp;
			}

			handScore = score;
		}
		return handScore;
	}

	for (auto i = books_runs_in_hand.begin(); i<books_runs_in_hand.end(); i++)
	{
		vector<Card> recursiveHand;
		vector<string> temp = stringHandCopy;

		for (auto j=i->begin();j<i->end();j++)
		{
			//Card card = currentBookRun[j];
			temp.erase(remove(temp.begin(), temp.end(), j->stringCard()), temp.end());
		}

		vector<string>::iterator iter;

		for (auto iter = temp.begin(); iter < temp.end(); iter++)
		{
			string face(1, (*iter)[0]);
			string suit(1, (*iter)[1]);

			Card tempCard = Card(face, suit);
			recursiveHand.push_back(tempCard);
		}

		bestHandCombo(recursiveHand);
	}

}

/* *********************************************************************
 Function Name: scoreOfHand
 Purpose: get score of Players hand
 Parameters:
	vector <Card> p_hand
 Return Value: int
 Local Variables:
	int score : total score of cards
 Algorithm:
	1: based on face value of the card add it to the running total of score to send back
 Assistance Received:
 ********************************************************************* */
int Player::scoreOfHand(vector<Card> p_hand)
{
	int score = 0;

	for (int i = 0; i < p_hand.size(); i++)
	{
		string card = p_hand[i].stringCard();
		char face = card.at(0);


		if (stringWild(card))
		{
			score += 20;
			continue;
		}
		if (stringJoker(card))
		{
			score += 50;
			continue;
		}		

		if (face == 'X')
		{
			score += 10;
		}
		else if (face == 'J')
		{
			score += 11;
		}
		else if (face == 'Q')
		{
			score += 12;
		}
		else if (face == 'K')
		{
			score += 13;
		}
		else
		{
			int intFace = stoi(p_hand[i].getNumFace());
			score += intFace;
		}

	}

	return score;
}

/* *********************************************************************
 Function Name: possibleCombo
 Purpose: get a book run combo from the current hand
 Parameters:
	vector <string> s_hand : hand of player in string form
 Return Value: vector<vector<Card>>
 Local Variables:
	vector<vector<string>> possibleCombo : all possible book run combos
	int minCombo : lowest number of cards that can be in a combo
	vector<string> wildAndJokers : all wildcards and jokers from the hand
	vector<string>::iterator it : iterator
	int maxCombo : max number of cards in a combo
	int numInCombo : number of cards in the current combo we are looking for
	int comboIndex : index in combo vector
	vector<string> suits : vector of all possible suits
	int possibleComboSize : size of possibleCombo
	vector<vector<Card>> allBooksRuns : all book and runs from players hand
 Algorithm:
	1: sort the hand and remove all wildcards and jokers
	2: put the cards in specific groupings of combo lengths we are looking for and put that into possibleCombo
	3: put cards with the same suit in the specific combo length into possibleCombo
	4: send that vector of possibleCombos to see if any are books or runs
	5: all valid books and runs are saved into allBooksRuns
 Assistance Received:
 ********************************************************************* */
vector<vector<Card>> Player::possibleCombo(vector <string> s_hand)
{
	sortHand(s_hand);
	vector<vector<string>> possibleCombo;

	int minCombo = 3;


	vector<string> wildAndJokers;
	vector<string>::iterator it;
	for (it = s_hand.begin(); it != s_hand.end();)
	{
		string currentCard = *it;

		if (stringWild(currentCard))
		{
			wildAndJokers.push_back(currentCard);
			it = s_hand.erase(it);
		}
		else if (stringJoker(currentCard))
		{
			wildAndJokers.push_back(currentCard);
			it = s_hand.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (wildAndJokers.size() == 1)
	{
		minCombo--;
	}
	else if(wildAndJokers.size() >=2)
	{
		minCombo = minCombo - 2;
	}

	int maxCombo = s_hand.size();
	int numInCombo = minCombo;
	int comboIndex;

	while (numInCombo <= maxCombo)
	{
		comboIndex = 0;

		while (comboIndex <= (maxCombo - numInCombo)) {
			vector<string> currentCombo;
			for (int i = comboIndex; i < (numInCombo + comboIndex); i++) {
				if (i < s_hand.size()) {
					currentCombo.push_back(s_hand[i]);
				}
			}
			possibleCombo.push_back(currentCombo);
			comboIndex++;
		}
		numInCombo++;
	}

	vector<string> suits = { "s", "c", "d", "h", "t" };

	for (int i = 0; i < suits.size(); i++)
	{
		string cSuit = suits[i];
		char cChar = suits[i].at(0);
		vector<string> cCard;

		for (int i = 0; i < s_hand.size(); i++)
		{
			char s_handChar = s_hand[i].at(0);
			if (s_handChar == cChar)
			{
				cCard.push_back(s_hand[i]);
			}
		}

		int numInCombo = minCombo;
		int comboIndex;

		while (numInCombo <= maxCombo)
		{
			comboIndex = 0;

			while (comboIndex <= (maxCombo - numInCombo)) {
				vector<string> currentCombo;
				for (int i = comboIndex; i < (numInCombo + comboIndex); i++) {
					if (i < s_hand.size()) {
						currentCombo.push_back(s_hand[i]);
					}
				}
				if (!(find(possibleCombo.begin(),possibleCombo.end(),currentCombo) != possibleCombo.end()))
				{
					possibleCombo.push_back(currentCombo);
				}
				comboIndex++;
			}
			numInCombo++;
		}

	}

	int possibleComboSize = possibleCombo.size();
	for (int i =0;i<possibleComboSize;i++)
	{
		vector<string> tempCombo = possibleCombo[i];
		for (int j = 0; j < wildAndJokers.size(); j++)
		{
			tempCombo.push_back(wildAndJokers[j]);
			possibleCombo.push_back(tempCombo);
		}
	}

	vector<vector<Card>> allBooksRuns = findValidBooksRuns(possibleCombo);

	return allBooksRuns;
}

/* *********************************************************************
 Function Name: findValidBooksRuns
 Purpose: find books and runs that are in possibleCombo
 Parameters:
	vector<vector<string>> possibleCombo : possible book and run combos
 Return Value: vector<vector<Card>>
 Local Variables:
	string face : face of a specific card
	string suit : suit of a specific card
	vector<vector<Card>> validBooksRuns : all valid books or runs
 Algorithm:
	1: make the combo in possibleCombo a vector of cards
	2: send that to be checked if its a book or run
	3: if yes then save it in validBooksRuns
 Assistance Received:
 ********************************************************************* */
vector<vector<Card>> Player::findValidBooksRuns(vector<vector<string>> possibleCombo)
{
	string face;
	string suit;
	vector<vector<Card>> validBooksRuns;

	for (int i = 0;i<possibleCombo.size();i++)
	{
		vector<Card> combo;
		for (int j=0;j<possibleCombo[i].size();j++)
		{
			face = possibleCombo[i][j].at(0);
			suit = possibleCombo[i][j].at(1);

			Card temp = Card(face,suit);
			combo.push_back(temp);
		}


		if (checkBook(combo) || checkRun(combo))
		{
			validBooksRuns.push_back(combo);
		}
	}

	return validBooksRuns;
}

/* *********************************************************************
 Function Name: checkBook
 Purpose: check of cards are a book
 Parameters:
	vector<Card> possibleCombo : possible book combo
 Return Value: bool
 Local Variables:
	bool isBook : true of cards are a book false otherwise
	vector <string> stringCombo : string representation of cards
 Algorithm:
	1: if size of possible combo is < 3 return false
	2: remove wildcards and jokers
	3: see if every card has the same face as the one next to it
	4: if that is true then return true
 Assistance Received:
 ********************************************************************* */
bool Player::checkBook(vector<Card> possibleCombo)
{
	bool isBook = false;
	if (possibleCombo.size() < 3) {
		return false;
	}

	vector<string> stringCombo = handToString(possibleCombo);
	stringCombo = noWildAndJoker(stringCombo);

	if (stringCombo.size() == 1) {
		return true;
	}

	for (int i =0;i<stringCombo.size()-1;i++)
	{
		char cCardFace = stringCombo[i].at(0);
		for (int j = i+1;j<stringCombo.size();j++)
		{
			char nCardFace = stringCombo[j].at(0);

			if (nCardFace != cCardFace)
			{
				return isBook;
			}
		}
	
	}

	isBook = true;

	return isBook;
}

/* *********************************************************************
 Function Name: checkRun
 Purpose: see if combo is a run
 Parameters:
	vector<Card> possibleCombo : possible book combo
 Return Value: bool
 Local Variables:
	bool isRun : true if cards are a run
	int total_applicable_wildcards : number of wildCards and jokers that can be used
	vector<int> face_values : vector of all the face values of the cards
	int vec_size : size of face_values
	int start : index of lowest card in hand
	int end : index of highest card in hand
	int m_diff : difference between start and end
 Algorithm: 
	1: if size of possible combo is < 3 return false
	2: remove wildcards and jokers
	3: sort the hand
	4: make sure all the cards are the same suit
	5: get the difference between the min and max numbers
	6: minus that with the number of cards between the max and min
	7: if that is less then or equal too the number of wildCards and jokers + 1 return true
 Assistance Received:
 ********************************************************************* */
bool Player::checkRun(vector<Card> possibleCombo)
{
	bool isRun = false;
	if (possibleCombo.size() < 3) {
		return false;
	}
	vector<string> stringCombo = handToString(possibleCombo);
	stringCombo = noWildAndJoker(stringCombo);
	int total_applicable_wildcards = possibleCombo.size() - stringCombo.size();
	sortHand(stringCombo);

	if (stringCombo.size() == 1) {
		return true;
	}

	//checks to see if all cards are same suit
	for (int i = 0; i < stringCombo.size()-1; i++)
	{
		string cCardSuit(1, stringCombo[i].at(1));
		for (int j = i + 1; j < stringCombo.size(); j++)
		{
			string nCardSuit(1, stringCombo[j].at(1));

			if (nCardSuit != cCardSuit)
			{
				return isRun;
			}
		}

	}


	vector<int> face_values;
	vector<string>::iterator i;
	for (i = stringCombo.begin(); i != stringCombo.end(); ++i) {
		string current_tempandsuit = *i;
		string face(1, current_tempandsuit[0]);

		if (face == "x" || face == "X")
		{
			face = "10";
		}
		else if (face == "j" || face == "J")
		{
			face = "11";
		}
		else if (face == "q" || face == "Q")
		{
			face = "12";
		}
		else if (face == "k" || face == "K")
		{
			face  = "13";
		}

		int intFace = stoi(face);

		if (!(find(face_values.begin(), face_values.end(), intFace) != face_values.end())) {
			face_values.push_back(intFace);
		}
	}

	sort(face_values.begin(), face_values.end());

	if (face_values.size() == 1) {
		return false;
	}

	int vec_size = face_values.size();
	int start = -5;
	int end = -5;
	int m_diff = face_values[1] - face_values[0];
	for (int i = 0; i < vec_size; i++) {
		for (int j = i + 1; j < vec_size; j++) {
			if (face_values[j] - face_values[i] > m_diff) {
				m_diff = face_values[j] - face_values[i];
				end = face_values[j];
				start = face_values[i];
			}
		}
	}

	for (int i = 0; i < vec_size; i++) {
		if (face_values[i] > start&& face_values[i] < end) {
			m_diff--;
		}
	}
	
	if (m_diff <= (total_applicable_wildcards + 1)) {
		isRun = true;
	}

	return isRun;
}

/* *********************************************************************
 Function Name: faceToInt
 Purpose: convert the string face value to an int
 Parameters:
	string Face : face of the card to be converted to int
 Return Value: int
 Local Variables:
	
 Algorithm:
	1: read in the face value and return the respected int associated with it
 Assistance Received:
 ********************************************************************* */
int Player::faceToInt(string Face)
{
	if (Face == "X")
	{
		return 10;
	}
	else if (Face == "J")
	{
		return 11;
	}
	else if (Face == "Q")
	{
		return 12;
	}
	else if (Face == "K")
	{
		return 13;
	}
	else
	{
		return stoi(Face);
	}
}

/* *********************************************************************
 Function Name: noWildAndJoker
 Purpose: remove wildcards and jokers from hand
 Parameters:
	vector<string> possibleCombo : string combo to have the wildcards and jokers removed
 Return Value:
 Local Variables:
	vector<string> temp : this is the new string without wildcards and jokers to be sent back
 Algorithm:
	1: check each card and see if its a wildcard or joker
	2: if its not a wildcard or joker push the card onto temp
	3: return temp
 Assistance Received:
 ********************************************************************* */
vector<string> Player::noWildAndJoker(vector<string> possibleCombo)
{
	vector<string> temp;
	for (int i = 0; i < possibleCombo.size(); i++)
	{
		string card = possibleCombo[i];
		if ( stringWild(card))
		{
			continue;
		}
		else if (stringJoker(card))
		{
			continue;
		}
		else
		{
			temp.push_back(card);
		}

	}

	return temp;
}

/* *********************************************************************
 Function Name: getRoundNumber
 Purpose: get the round number
 Parameters:

 Return Value: int
 Local Variables:

 Algorithm:
 Assistance Received:
 ********************************************************************* */
int Player::getRoundNumber()
{
	return m_roundNum;
}

/* *********************************************************************
 Function Name: stringWild
 Purpose: see if a string card is wild
 Parameters:
	string card : card to be checked if wild
 Return Value: bool
 Local Variables:
	int temp : face vaue of the card
 Algorithm:
	1: see if the card at index 0 is an int
	2: if it is then see if that number is 2 + the round number and if so return true
	3: else check to see if it matches any of the hard coded conditions for wildcards
 Assistance Received:
 ********************************************************************* */
bool Player::stringWild(string card)
{
	if (isdigit(card.at(0))) {
		int temp = card.at(0) - '0';
		if (temp == (m_roundNum + 2)) {
			return true;
		}
	}
	else if (m_roundNum == 8 && card.at(0) == 'X') {
		return true;
	}
	else if (m_roundNum == 9 && card.at(0) == 'J' ) {
		return true;
	}
	else if (m_roundNum == 10 && card.at(0) == 'Q') {
		return true;
	}
	else if (m_roundNum == 11 && card.at(0) == 'K') {
		return true;
	}

	return false;
}

/* *********************************************************************
 Function Name: stringJoker
 Purpose: see if a string card is a joker
 Parameters:
	string card : card to be checked if its a joker
 Return Value: bool
 Local Variables:
	int number : "suit" value of the joker to see if it equals 1 2 or 3
 Algorithm:
	1: see if the face value of the card is a 'j' and the suit is a number
	2: make sure the suit is 1 2 or 3
	3: if so then return true
 Assistance Received:
 ********************************************************************* */
bool Player::stringJoker(string card)
{
	if ((card.at(0) == 'j') && isdigit(card.at(1))) {
		int number = card.at(1)-'0';

		if (number == 1 || number == 2 || number == 3) {
			return true;
		}
	}

	return false;
}

/* *********************************************************************
 Function Name: sortHand
 Purpose: sort the hand that is given
 Parameters:
	vector <string> & s_hand : hand to be sorted
 Return Value: 
 Local Variables:
	vector<string> tens : vector of all tens in the players hand
	vector<string> kings : vector of all kings in players hand
	vector<string>::iterator it : vector iterator 
	int first_j_q : index of the first jack or queen
 Algorithm:
	1: call the vector sort function on the whole hand
	2: remove all tens and kings since they wont properly sort in the vector sort function and save them in their own vector
	3: find the first instance of a jack or queen
	4: insert the elements of the tens vector into the hand before the first jack or queen
	5: push the elements of the kings vector to the back
 Assistance Received:
 ********************************************************************* */
void Player::sortHand(vector <string> & s_hand)
{
	sort(s_hand.begin(), s_hand.end());

	vector<string> tens;
	vector<string> kings;
	vector<string>::iterator it;

	for (it = s_hand.begin(); it != s_hand.end();)
	{
		string currentCard = *it;

			if (currentCard.at(0) == 'X') {
				tens.push_back(currentCard);
				it = s_hand.erase(it);
			}

			else if (currentCard.at(0) == 'K') {
				kings.push_back(currentCard);
				it = s_hand.erase(it);
			}
			else
			{
				++it;
			}
	}

	sort(tens.begin(), tens.end());
	sort(kings.begin(), kings.end());

	int first_j_q = 100000;

	for (int i = 0; i < s_hand.size(); i++)
	{
		string currentCard = s_hand[i];
		if (currentCard.at(0) == 'J' || currentCard.at(0) == 'Q')
		{
			auto findCard = find(s_hand.begin(),s_hand.end(),currentCard);
			auto x_index = distance(s_hand.begin(), findCard);

			if (x_index < first_j_q)
			{
				first_j_q = x_index;
			}
		}
	}

	for (int i = 0; i < tens.size(); i++)
	{
		string tenCard = tens[i];
		if (first_j_q == 100000)
		{
			s_hand.push_back(tenCard);
		}
		else
		{
			s_hand.insert(s_hand.begin() + first_j_q, tenCard);
			first_j_q++;
		}
	}

	for (int i = 0; i < kings.size(); i++)
	{
		string kingCard = kings[i];

		s_hand.push_back(kingCard);

	}
}

/* *********************************************************************
 Function Name: numWildCards
 Purpose: update m_totalWild member variable and to check the number of wildCards in a vector of cards (players hand)
 Parameters:

 Return Value:
 Local Variables:
	int intFace : int value of the face of a card to use for checking
 Algorithm:
	1: get face value of card and see if it is 2 + the round number or matches any of the hard coded checks
	2: if so increment m_totalWild
 Assistance Received:
 ********************************************************************* */
void Player::numWildCards()
{

	for (int i = 0; i < m_hand.size(); i++)
	{
		if (m_hand[i].getFace() != "j")
		{
			int intFace = stoi(m_hand[i].getNumFace());

			if (intFace == (m_roundNum + 2)) {
				m_totalWild++;
			}
		}

		if (m_roundNum == 8 && m_hand[i].getFace() == "X") {
			m_totalWild++;
		}
		else if (m_roundNum == 9 && m_hand[i].getFace() == "J") {
			m_totalWild++;
		}
		else if (m_roundNum == 10 && m_hand[i].getFace() == "Q") {
			m_totalWild++;
		}
		else if (m_roundNum == 11 && m_hand[i].getFace() == "K") {
			m_totalWild++;
		}

	}

}

/* *********************************************************************
 Function Name: numJokers
 Purpose: update m_totalJokers
 Parameters:

 Return Value:
 Local Variables:

 Algorithm:
	1: if the face value is a lowercase j then increment m_totalJokers (I have all the faces of the jokers be lowercase)
 Assistance Received:
 ********************************************************************* */
void Player::numJokers()
{
	for (int i=0; i<m_hand.size();i++)
	{
		if (m_hand[i].getFace() == "j")
		{
			m_totalJoker++;
		}
	}
}

/* *********************************************************************
Function Name: getScore
Purpose: get the score of the player
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	return score of the player
Assistance Received: none
********************************************************************* */
int Player::getScore() {
	return m_playerScore;
}

/* *********************************************************************
Function Name: setScore
Purpose: set the players score
Parameters:
	int score, given score for m_playerScore to be set to
Return Value: none
Local Variables: none
Algorithm:
	set m_playerScore to score
Assistance Received: none
********************************************************************* */
void Player::setScore(int score) {
	m_playerScore = score;
}

/* *********************************************************************
 Function Name:
 Purpose:
 Parameters:

 Return Value:
 Local Variables:

 Algorithm:
 Assistance Received:
 ********************************************************************* */
void Player::setStringHand(vector<string> inHand)
{
	m_string_hand = inHand;
}

/* *********************************************************************
Function Name: setHand
Purpose: set the players hand
Parameters:
	vector<Card*>, given hand for m_hand to be set to
Return Value: none
Local Variables: none
Algorithm:
	set m_hand to hand
Assistance Received: none
********************************************************************* */
void Player::setHand(vector<Card> hand) {
	m_hand = hand;
}

/* *********************************************************************
Function Name: addToHand
Purpose: add a card to the players hand
Parameters:
	Card* addCard, card to be added to the hand
Return Value: none
Local Variables: none
Algorithm:
	add addCard to players hand with .push_back
Assistance Received: none
********************************************************************* */
void Player::addToHand(Card addCard)
{
	m_hand.push_back(addCard);
}

/* *********************************************************************
Function Name: printHand
Purpose: print players hand
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	cout every card in players hand with printCard
Assistance Received: none
********************************************************************* */
void Player::printHand()
{
	for (int i = 0; i < m_hand.size(); i++)
	{
		m_hand[i].printCard();
	}
}

/* *********************************************************************
Function Name: removeFromHand
Purpose: remove a card from the players hand
Parameters:
	int index, index of the card to be removed in hand
Return Value: none
Local Variables: none
Algorithm:
	erace a card from the vector using .erase
Assistance Received: none
********************************************************************* */
void Player::removeFromHand(int index)
{
	while (index < 0 || index > m_hand.size())
	{
		cout << "Invalid index" << endl;
		return;
	}

	m_hand.erase(m_hand.begin() + index);
}

/* *********************************************************************
Function Name: getCard
Purpose: get a single card from the hand
Parameters:
	int index, card index of the card to be returned in hand
Return Value: none
Local Variables:
	tempCard, card to be returned from hand
Algorithm:
	get the corresponding card at index in hand and return it
Assistance Received: none
********************************************************************* */
Card Player::getCard(int index) {
	Card tempCard;
	tempCard = m_hand[index];
	return tempCard; 
}

/* *********************************************************************
Function Name: playerScore
Purpose: print player score to screen
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	cout m_playerScore
Assistance Received: none
********************************************************************* */
void Player::printScore()
{
	cout << m_playerScore;

}

/* *********************************************************************
Function Name: printPlayer
Purpose: print player info to screen
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
	cout the players score and then players hand with printHand() function
Assistance Received: none
********************************************************************* */
void Player::printPlayer()
{
	cout << "Score: " << m_playerScore;
	cout << "Hand: ";
	printHand();
}
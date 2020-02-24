#include "pch.h"
#include "Game.h"

using namespace std;

/* *********************************************************************
Function Name: Game
Purpose: constructor for this class
Parameters:
	a_mainDeck, a_discardPile, a_drawPile, a_computer, a_human,
	a_roundNum
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
Game::Game(Deck a_mainDeck, Deck a_discardPile, Deck a_drawPile, Player* a_computer, Player* a_human, int a_roundNum) {
	m_mainDeck = a_mainDeck;
	m_discardPile = a_discardPile;
	m_drawPile = a_drawPile;
	m_computer = a_computer;
	m_human = a_human;
	m_roundNum = a_roundNum;
}

/* *********************************************************************
Function Name: shuffleDecks
Purpose: shuffle the decks
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Game::shuffleDecks() {
	m_deck1.shuffleDeck();
	m_deck2.shuffleDeck();
	m_mainDeck = m_deck1;
	m_mainDeck.addDeck(m_deck2.getDeck());
	m_mainDeck.shuffleDeck();
}

/* *********************************************************************
Function Name: loadGame
Purpose: load game from the text file
Parameters:
	a_fileName - name of file we wish to load from
Return Value:
Local Variables:
	roundNum, computer, human, drawPile, discardPile, card, nextplayer
	file, line, word, isHuman, isComputer, id
Algorithm:
	Read from each line of the text file and initialize appropriate
	members based on what is being read in
	
Assistance Received: None
********************************************************************* */
void Game::loadGame(string a_fileName)
{
	int roundNum;
	Player* computer = new Computer();
	Player* human = new Human();
	Deck drawPile;
	Deck discardPile;
	Card card;
	string nextPlayer = "";

	ifstream file;
	file.open(a_fileName);
	string line = "";
	bool isHuman = false;
	bool isComputer = false;
	int id = 0;

	while (!file.eof()) {
		string word = "";
		getline(file, line);
		istringstream ins(line);

		while (1) {
			ins >> word;
			if (word.length() == 0) {
				break;
			}
			if (word.compare("Round:") == 0) {
				ins >> word;
				roundNum = stoi(word);
				break;
			}
			else if (word.compare("Computer:") == 0) {
				isHuman = false;
				isComputer = true;
				break;
			}
			else if (word.compare("Human:") == 0) {
				isHuman = true;
				isComputer = false;
				break;
			}
			else if (word.compare("Score:") == 0) {
				if (isHuman) {
					ins >> word;
					int humanScore = stoi(word);
					human->setScore(humanScore);
				}
				else if (isComputer) {
					ins >> word;
					int computerScore = stoi(word);
					computer->setScore(computerScore);
				}
				break;
			}
			else if (word.compare("Hand:") == 0) {
				if (isHuman) {
					while (ins >> word) {
						if (word.length() > 0) {
							card = createCard(word, id);
							human->giveCard(card);
							id++;
						}
					}
				}
				else if (isComputer) {
					while (ins >> word) {
						if (word.length() > 0) {
							card = createCard(word, id);
							computer->giveCard(card);
							id++;
						}
					}
				}
				break;
			}
			else if (word.compare("Draw") == 0) {
				while (ins >> word)
				{
					while (ins >> word) {
						if (word.length() > 0) {
							if (!word.compare("Pile:") == 0) {
								card = createCard(word, id);
								drawPile.giveCardFront(card);
								id++;
							}
						}
					}
				}
				break;
			}

			else if (word.compare("Discard") == 0) {
				while (ins >> word)
				{
					if (word.length() > 0) {
						if (!word.compare("Pile:") == 0) {
							card = createCard(word, id);
							discardPile.giveCardFront(card);
							id++;
						}
					}
				}
				break;
			}
			else if (word.compare("Next") == 0) {
				ins >> word;
				ins >> word;
				if (word.compare("Human") == 0) {
					human->setGoesFirst(true);
					computer->setGoesFirst(false);
				}
				else if (word.compare("Computer") == 0) {
					human->setGoesFirst(false);
					computer->setGoesFirst(true);
				}
				break;
			}
		}
	}
	m_roundNum = roundNum;
	m_computer = computer;
	m_human = human;
	m_discardPile = discardPile;
	m_drawPile = drawPile;
	m_deck1 = m_discardPile;
	m_deck2.addDeck(m_drawPile);
	m_deck1.addDeck(m_computer->returnHand());
	m_deck2.addDeck(m_human->returnHand());

	m_mainDeck = m_deck1;
	m_mainDeck.addDeck(m_deck2);

	/*
	vector<Card>::const_iterator deck1First = m_mainDeck.getDeck().begin();
	vector<Card>::const_iterator deck1Last = m_mainDeck.getDeck().begin() + 57;
	vector<Card> deck1(deck1First, deck1Last);
	m_deck1.setDeck(deck1);
	vector<Card>::const_iterator deck2First = m_mainDeck.getDeck().begin() + 58;
	vector<Card>::const_iterator deck2Last = m_mainDeck.getDeck().end();
	vector<Card> deck2(deck2First, deck2Last);
	m_deck2.setDeck(deck2);
	*/
}

/* *********************************************************************
Function Name: createCard
Purpose: create a card from a card name and id
Parameters:
	a_cardName - name of card we create
	a_id - id of card we create
Return Value: carrd we have created
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
Card Game::createCard(string a_cardName, int a_id)
{
	int val = 0;
	Card card;
	//switch for values
	switch (a_cardName[0])
	{
		case 'X':
			val = 10;
			break;
		case 'J':
			val = 11;
			break;
		case 'Q':
			val = 12;
			break;
		case 'K':
			val = 13;
			break;
		case 'A':
			val = 14;
			break;
		default:
			val = (a_cardName[0] - '0');
			break;
	}
	//switch for ranks
	switch (a_cardName[0])
	{
		case 'K':
			card.setRank(King);
			break;
		case 'Q':
			card.setRank(Queen);
			break;
		case 'J':
			if (a_cardName[1] == '1' || a_cardName[1] == '2' || a_cardName[1] == '3') {
				card.setRank(Joker);
				card.setSuit(Joke);
				val = 50;
				break;
			}
			card.setRank(Jack);
			break;
		case 'X':
			card.setRank(Ten);
			break;
		case '9':
			card.setRank(Nine);
			break;
		case '8':
			card.setRank(Eight);
			break;
		case '7':
			card.setRank(Seven);
			break;
		case '6':
			card.setRank(Six);
			break;
		case '5':
			card.setRank(Five);
			break;
		case '4':
			card.setRank(Four);
			break;
		case '3':
			card.setRank(Three);
			break;
		default:
			break;
	}
	//switch for suits
	switch (a_cardName[1])
	{
		case 'S':
			card.setSuit(Spades);
			break;
		case 'D':
			card.setSuit(Diamonds);
			break;
		case 'C':
			card.setSuit(Clubs);
			break;
		case 'H':
			card.setSuit(Hearts);
			break;
		case 'T':
			card.setSuit(Tridents);
			break;
		default:
			break;
	}

	card.setName(a_cardName);
	card.setValue(val);
	card.setId(a_id);
	return card;
}




/* *********************************************************************
Function Name: endGame
Purpose: called when the game has ended
Parameters:
Return Value:
Local Variables:
Algorithm:
	1) find which player has the lower score and prints which player
	won
Assistance Received: None
********************************************************************* */
void Game::endGame()
{
	cout << "\nGame Over\n" << endl;
	cout << "Human Score: " << m_human->returnScore() << endl;
	cout << "Computer Score: " << m_computer->returnScore() << endl;
	if (m_human->returnScore() < m_computer->returnScore()) {
		cout << "\nHuman wins!\n" << endl;
	}
	else if (m_human->returnScore() > m_computer->returnScore()) {
		cout << "\Computer wins!\n" << endl;
	}
}

/* *********************************************************************
Function Name: initializeGame
Purpose: begin the game and create all members
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Game::initializeGame() {
	m_roundNum = 1;
	m_computer = new Computer();
	m_human = new Human();
	m_computer->setScore(0);
	m_human->setScore(0);
	m_deck1.createDeck();
	m_deck2.createDeck();
	m_mainDeck = m_deck1;
	m_mainDeck.addDeck(m_deck2.getDeck());
	shuffleDecks();
}
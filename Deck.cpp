#include "pch.h"
#include "Deck.h"

using namespace std;

/* *********************************************************************
Function Name: createDeck
Purpose: creates a deck
Parameters:
Return Value:
Local Variables:
	file, count, id, cal, line, word, file, val
Algorithm:
	1) Read from CardNames.txt which holds our card names
	2) based on the name of the card we create a new card and set the
	card with appropriate values based on card name
Assistance Received: None
********************************************************************* */
void Deck::createDeck() {
	m_deck.resize(58);
	ifstream file;
	int count = 0;
	int id = 0;
	//int mod = 0;
	int val = 0;
	file.open("CardNames.txt");

	while (!file.eof()) {
		string line;
		string word;
		getline(file, line);
		istringstream ins(line);

		while (1)
		{
			ins >> word;
			if (word.empty()) break;
			//switch for values
			switch (word[0])
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
				val = (word[0] - '0');
				break;
			}
			//switch for ranks
			switch (word[0])
			{
			case 'K':
				m_deck[count].setRank(King);
				break;
			case 'Q':
				m_deck[count].setRank(Queen);
				break;
			case 'J':
				if (word[1] == '1' || word[1] == '2' || word[1] == '3') {
					m_deck[count].setRank(Joker);
					m_deck[count].setSuit(Joke);
					val = 50;
					break;
				}
				m_deck[count].setRank(Jack);
				break;
			case 'X':
				m_deck[count].setRank(Ten);
				break;
			case '9':
				m_deck[count].setRank(Nine);
				break;
			case '8':
				m_deck[count].setRank(Eight);
				break;
			case '7':
				m_deck[count].setRank(Seven);
				break;
			case '6':
				m_deck[count].setRank(Six);
				break;
			case '5':
				m_deck[count].setRank(Five);
				break;
			case '4':
				m_deck[count].setRank(Four);
				break;
			case '3':
				m_deck[count].setRank(Three);
				break;
			default:
				break;
			}
			//switch for suits
			switch (word[1])
			{
			case 'S':
				m_deck[count].setSuit(Spades);
				break;
			case 'D':
				m_deck[count].setSuit(Diamonds);
				break;
			case 'C':
				m_deck[count].setSuit(Clubs);
				break;
			case 'H':
				m_deck[count].setSuit(Hearts);
				break;
			case 'T':
				m_deck[count].setSuit(Tridents);
				break;
			default:
				break;
			}

			m_deck[count].setName(word);
			m_deck[count].setValue(val);
			m_deck[count].setId(id);
			id++;
			word.clear();
			count++;
		}
	}
}

/* *********************************************************************
Function Name: shuffleDeck
Purpose: shuffle this deck
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Deck::shuffleDeck() {
	srand(time(NULL));
	auto first = m_deck.begin();
	auto last = m_deck.end();
	random_shuffle(first, last);
}

/* *********************************************************************
Function Name: returnDeckString
Purpose: return this deck in string form
Parameters:
Return Value: string representing this deck
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
string Deck::returnDeckString() {
	string deckString = "";
	for (int i = m_deck.size() - 1; i >= 0; i--) {
		deckString += m_deck[i].getName() + " ";
	}
	return deckString;
}

/* *********************************************************************
Function Name: addDeck
Purpose: add a vector of cards to this deck
Parameters:
	a_deck - the cards we want to add to this deck
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Deck::addDeck(vector<Card> a_deck) {
	if (a_deck.size() > 0) {
		m_deck.insert(m_deck.end(), a_deck.begin(), a_deck.end());
	}
}

/* *********************************************************************
Function Name: addDeck
Purpose: add a deck to this deck
Parameters:
	a_deck - the deck we want to add to this deck
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Deck::addDeck(Deck a_deck)
{
	vector<Card> deck = a_deck.getDeck();
	if (deck.size() > 0) {
		m_deck.insert(m_deck.end(), deck.begin(), deck.end());
	}
	
}

//Checking if the name entered equals a card's name in deck
/* *********************************************************************
Function Name: checkIfNameEqualsCard
Purpose: return true if the name passed in equals a card in this deck
Parameters: 
	a_cardName - name we check for
Return Value: true if name equals a card
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
bool Deck::checkIfNameEqualsCard(string a_cardName)
{
	for (Card c : m_deck) {
		if (c.getName().compare(a_cardName) == 0) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: assignIds
Purpose: assigns ids to each card
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Deck::assignIds() {
	int id = 0;
	for (Card c : m_deck) {
		c.setId(id);
		id++;
	}
}
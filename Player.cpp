#include "pch.h"
#include "Player.h"

using namespace std;

/* *********************************************************************
Function Name: returnHandString
Purpose: returns the hand of this player in the form of a string
Parameters:
Return Value: The hand of the player as a string
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
string Player::returnHandString() {
	std::string handString = "";
	for (Card c : m_hand) {
		handString += c.getName() + " ";
	}
	return handString;
}

/* *********************************************************************
Function Name: printhand
Purpose: prints the hand of the player
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Player::printHand() {
	for (Card c : m_hand) {
		std::cout << c.getName() << " " << std::endl;
	}
}





//Probably going to want to change this but I think it works for now
/* *********************************************************************
Function Name: removeCard
Purpose: remove the card from the player that is passed in 
Parameters:
	a_card - card to remove
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Player::removeCard(Card a_card) {
	int count = 0;
	for (Card c : m_hand) {
		if (c.getName().compare(a_card.getName()) == 0) {
			m_hand.erase(m_hand.begin() + count);
			return;
		}
		count++;
	}
}

/* *********************************************************************
Function Name: removeCardbyName
Purpose: removes card that matches the string
Parameters:
	a_cardName - name of card we want to remove
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Player::removeCardByName(string a_cardName) {
	int count = 0;
	for (Card c : m_hand) {
		if (c.getName().compare(a_cardName) == 0) {
			m_hand.erase(m_hand.begin() + count);
			return;
		}
		count++;
	}
}

/* *********************************************************************
Function Name: checkIfNameEqualsCard
Purpose: if the string passed in equals the card name then return true
Parameters:
	a_cardName - name of card we check for
Return Value: true if equals a card name
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
bool Player::checkIfNameEqualsCard(string a_cardName)
{
	for (Card c : m_hand) {
		if (c.getName().compare(a_cardName) == 0) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: returnCardbyName
Purpose: returns the card that matches the string passed in 
Parameters:
	a_cardName - name of the card we want to get
Return Value: the card that matches the name passed in 
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
Card Player::returnCardByName(string a_cardName) {
	for (Card c : m_hand) {
		if (c.getName().compare(a_cardName) == 0) {
			return c;
		}
	}
}

/* *********************************************************************
Function Name: canGoOut
Purpose: Finding if the player can go out
Parameters: 
	a_wildCardNum - the number of the wild card
Return Value: returns true if the player can go out
Local Variables:
	cards, books, bookString, potentialRun, runString
Algorithm:
	1) sorts the hand
	2) if hand is a book return true
	3) if hand is a run then return true
	4) if hand is all books then return true
	5) if hand is all books and one run then return true
	6) return false if no conditions are satisfied
Assistance Received: None
********************************************************************* */
bool Player::canGoOut(int a_wildCardNum)
{
	vector<Card> cards = this->returnHand();
	sort(cards.begin(), cards.end(), compareValues);

	//If true then your hand is a book
	if (isBook(cards, a_wildCardNum)) {
		m_goOutHand = "Book: " + returnHandString();
		return true;
	}
	else if (isRun(cards, a_wildCardNum)) {
		m_goOutHand = "Run: " + returnHandString();
		return true;
	}
	else if (hasMultipleBooks(cards, a_wildCardNum)) {
		vector<vector<Card>> books = findBooks(cards, a_wildCardNum);
		string booksString = "Books: \n";
		for (vector<Card> book : books) {
			booksString += "\t";
			for (Card c : book) {
				booksString += c.getName() + " ";
			}
			booksString += "\n";
		}
		m_goOutHand = booksString;
		return true;
	}
	else if(hasBooksAndRun(cards, a_wildCardNum)) {
		vector<vector<Card>> books = findBooks(cards, a_wildCardNum);
		vector<Card> potentialRun = findRun(cards, a_wildCardNum);
		if (isRun(potentialRun, a_wildCardNum)) {
			string booksString = "Books: \n";
			for (vector<Card> book : books) {
				booksString += "\t";
				for (Card c : book) {
					booksString += c.getName() + " ";
				}
				booksString += "\n";
			}
			m_goOutHand = booksString;

			string runString = "Run: \n\t";
			for (Card myCard : potentialRun) {
				runString += myCard.getName() + " ";
			}
			runString += "\n";
			m_goOutHand += runString;
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: findRun
Purpose: find the run in the hand
Parameters: 
	a_cards - hand of player
	a_wildCardNum - wild card number
Return Value: the run in the hand
Local Variables:
	books, iBook, potentialRun
Algorithm:
	1) Find all books in hand
	2) finds any cards that are not in books
	3) Check if the cards not in books are runs
	4) return the potentialRun
Assistance Received: None
********************************************************************* */
vector<Card> Player::findRun(vector<Card> a_cards, int a_wildCardNum) {
	vector<vector<Card>> books = findBooks(a_cards, a_wildCardNum);
	bool inBook = false;
	vector<Card> potentialRun;
	for (Card card : returnHand()) {
		inBook = false;
		for (vector<Card> book : books) {
			for (Card c : book) {
				if (card.getId() == c.getId()) {
					inBook = true;
					break;
				}
			}
		}
		if (!inBook) {
			potentialRun.push_back(card);
		}
	}
	return potentialRun;
}

/* *********************************************************************
Function Name: hasBooksAndRun
Purpose: Finds if the player can go out because it has all books and
one run in the hand. I explained when I presented that this game 
will check if your hand is a book, run, has all books or has all books
and one run when going out.
Parameters:
	a_cards, a_wildCardNum
Return Value: true if the player can go out with its books and run
Local Variables:
	books, inBook, potentialRun
Algorithm:
	1) find all books in hand
	2) finds if the rest of the cards are in a run
	3) if they are the return true else return false
Assistance Received: None
********************************************************************* */
bool Player::hasBooksAndRun(std::vector<Card> a_cards, int a_wildCardNum) {
	vector<vector<Card>> books = findBooks(a_cards, a_wildCardNum);
	bool inBook = false;
	vector<Card> potentialRun = findRun(a_cards, a_wildCardNum);
	if (isRun(potentialRun, a_wildCardNum)) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: hasMultipleBooks
Purpose: if the player can arrange its hand into all books then returns
true
Parameters:
	a_cards - hand of player
	a_wildCardNum - number of the wild card
Return Value: true if player can go out with all books
Local Variables:
	books, count
Algorithm:
	1) finds all books
	2) if each card is in a book then returns true else false
Assistance Received: None
********************************************************************* */
bool Player::hasMultipleBooks(vector<Card> a_cards, int a_wildCardNum) {
	vector<vector<Card>> books = findBooks(a_cards, a_wildCardNum);
	int count = 0;
	for (vector<Card> book : books) {
		for (Card c : book) {
			count++;
		}
	}
	if (count == returnHand().size()) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: isRun
Purpose: Finds if the cards passed in are a run
Parameters:
	a_cards - the cards we want to see if they are a run
	a_wildCardNum - the wild card number
Return Value: true if these cards form a run
Local Variables:
	jokersAndWilds, normalCards, jokersAndWildsUsed
Algorithm:
	1) if there arent at least three cards then return false
	2) separate the jokers and wild cards into a separate vector
	3) if the other cards are not the same suit then it is false
	4) sort the cards from least to greatest
	5) if any card does not equal the value of the last card + 1
	then we use a joker or wild card
	6) if there are no more to use then not true
	7) if everything matches then true
Assistance Received: None
********************************************************************* */
bool Player::isRun(vector<Card> a_cards, int a_wildCardNum)
{
	//Need at least three cards for a run
	if (a_cards.size() < 3) {
		return false;
	}
	vector<Card> jokersAndWilds;
	vector<Card> normalCards;
	int jokersAndWildsUsed = 0;
	for (Card c : a_cards) {
		if (c.getRank() == Joker) {
			jokersAndWilds.push_back(c);
		}
		else if (c.getValue() == a_wildCardNum) {
			jokersAndWilds.push_back(c);
		}
		else {
			normalCards.push_back(c);
		}
	}
	//Because this means that everything else is wild or joker and this is therefore a run
	if (normalCards.size() == 0 || normalCards.size() == 1) {
		return true;
	}

	Suit suit = normalCards[0].getSuit();
	//If all the suits don't match then it's false
	if (!(all_of(normalCards.begin(), normalCards.end(), [&](Card c) {return c.getSuit() == suit; }))) {
		return false;
	}

	//Sorting based on values
	sort(normalCards.begin(), normalCards.end(), compareValues);

	int compValue = normalCards[0].getValue();

	//If any card does not equal the previous card's value plus 1 then not true
	for (int i = 1; i < normalCards.size(); i++) {
		if (normalCards[i].getValue() != (compValue + 1)) {
			int difference = normalCards[i].getValue() - compValue;
			if (jokersAndWildsUsed < jokersAndWilds.size()) {
				jokersAndWildsUsed += difference - 1;
				compValue = normalCards[i].getValue();
				if (jokersAndWildsUsed > jokersAndWilds.size()) {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			compValue++;
		}
	}

	return true;
}

/* *********************************************************************
Function Name: isBook
Purpose: find if the cards passed in are a book
Parameters:
	a_cards - cards we are checking for a book
	a_wildCardNum - number for wild card
Return Value: true if a_cards is a book
Local Variables:
	compVal
Algorithm:
	1) sort cards from least to greatest
	2) if the min value equals the max value then it is true
	3) else if we have jokers or wilds then we check if they help
	us form a book
	4) if there are not enough for a book then return false
Assistance Received: None
********************************************************************* */
bool Player::isBook(vector<Card> a_cards, int a_wildCardNum)
{
	//Need at least three cards for a book
	if (a_cards.size() < 3) {
		return false;
	}
	//Sorting based on values
	sort(a_cards.begin(), a_cards.end(), compareValues);

	//If the min element equals the max then true
	if (a_cards[0].getValue() == a_cards[a_cards.size() - 1].getValue()) {
		return true;
	}
	else if (any_of(a_cards.begin(), a_cards.end(), [&](Card c) {return c.getValue() == a_wildCardNum || c.getRank() == Joker; })) {
		int compVal = 0;
		for (Card c : a_cards) {
			if (!(c.getValue() == a_wildCardNum || c.getRank() == Joker)) {
				compVal = c.getValue();
			}
		}
		for (Card c : a_cards) {
			if (!(c.getValue() == compVal || c.getValue() == a_wildCardNum || c.getRank() == Joker)) {
				return false;
			}
		}
		return true;
	}

	return false;
}




/* *********************************************************************
Function Name: findBooks
Purpose: assemble all books in our hand that is passed as a_cards
Parameters:
	a_cards - our hand
	a_wildCardNum - wild card number
Return Value: All books in our hand
Local Variables:
	possibleBooks, books, book, jokersAndWilds, normalCards, 
	jokersAndWildsUsed
Algorithm:
	1) separate the wild cards and jokers
	2) for each value a card could have we see if we have a card
	that equals that value. If we do we put any cards with that 
	value into their own vector
	3) We then use our wildCards and jokers on any possible books
	that are not books
	4) Return the books we have made
Assistance Received: None
********************************************************************* */
vector<vector<Card>> Player::findBooks(vector<Card> a_cards, int a_wildCardNum) {
	vector<vector<Card>> possibleBooks;
	vector<vector<Card>> books;
	vector<Card> book;
	vector<Card> jokersAndWilds;
	vector<Card> normalCards;
	int jokersAndWildsUsed = 0;
	sort(a_cards.begin(), a_cards.end(), compareValues);

	for (Card c : a_cards) {
		if (c.getRank() == Joker) {
			jokersAndWilds.push_back(c);
		}
		else if (c.getValue() == a_wildCardNum) {
			jokersAndWilds.push_back(c);
		}
		else {
			normalCards.push_back(c);
		}
	}

	int compValue = normalCards[0].getValue();

	for (int i = 3; i <= 13; i++) {
		book.clear();
		if (i == a_wildCardNum) {
			continue;
		}

		if (any_of(normalCards.begin(), normalCards.end(), [&](Card c) {return c.getValue() == i; })) {
			for (Card c : normalCards) {
				if (c.getValue() == i) {
					book.push_back(c);
				}
				else if (c.getValue() > i) {
					break;
				}
			}
			possibleBooks.push_back(book);
		}
	}

	for (vector<Card> b : possibleBooks) {
		if (b.size() >= 3) {
			books.push_back(b);
		}
		else {
			int jokersAndWildsUsedForBook = 0;
			if (jokersAndWildsUsed < jokersAndWilds.size()) {
				for (int i = jokersAndWildsUsed; i < jokersAndWilds.size(); i++) {
					b.push_back(jokersAndWilds[i]);
					jokersAndWildsUsed++;
					jokersAndWildsUsedForBook++;
					if (b.size() == 3) {
						break;
					}
				}
				if (b.size() >= 3) {
					books.push_back(b);
				}
				else {
					jokersAndWildsUsed--;
				}
			}
		}
	}
	if (jokersAndWildsUsed < jokersAndWilds.size() && books.size() > 0) {
		for (int i = jokersAndWildsUsed; i < jokersAndWilds.size(); i++) {
			books[0].push_back(jokersAndWilds[i]);
		}
	}
	return books;
}



/* *********************************************************************
Function Name: loseRound
Purpose: Called when opponent has gone out and this player can't
Parameters:	
	a_cards - hand of the player
	a_wildCardNum - wild card number
Return Value: The number being added to the players score
Local Variables:
	sum
Algorithm:
	1) for each card in a_cards we add their value to sum
	2) we then try to assemble the hand into books
	3) anything in a book is subtracted from sum
	4) we look for a run and if there is a run we subtract
	those cards from the score
Assistance Received: None
********************************************************************* */
int Player::loseRound(std::vector<Card> a_cards, int a_wildCardNum) {
	int sum = 0;
	for (Card c : a_cards) {
		if (c.getValue() == a_wildCardNum) {
			sum += 20;
		}
		else {
			sum += c.getValue();
		}
	}

	vector<vector<Card>> books = findBooks(a_cards, a_wildCardNum);
	for (vector<Card> book : books) {
		for (Card c : book) {
			if (c.getValue() == a_wildCardNum) {
				sum -= 20;
			}
			else {
				sum -= c.getValue();
			}
		}
	}

	vector<Card> run = findRun(a_cards, a_wildCardNum);
	if (isRun(run, a_wildCardNum)) {
		for (Card c : run) {
			if (c.getValue() == a_wildCardNum) {
				sum -= 20;
			}
			else {
				sum -= c.getValue();
			}
		}
	}

	return sum;
}

/* *********************************************************************
Function Name: findBestCardToTake
Purpose: find the best card to take in the discard pile
Parameters:
	a_cards - hand we have
	a_discardPile - discard pile
	a_drawPile - draw pile
	a_wildCardNum - number of wild card
Return Value: The best card to take
Local Variables:
	hand, c
Algorithm:
	1) First we take the top card from discard pile
	2) If it can help us go out then we take it
	3) If it is a joker or a wild card we take it
	4) If it doesn't help us we take from draw pile
Assistance Received: None
********************************************************************* */
Card Player::findBestCardToTake(std::vector<Card> a_cards, Deck a_discardPile, Deck a_drawPile, int a_wildCardNum) {
	vector<Card> hand = a_cards;

	if (a_discardPile.getDeck().size() > 0) {
		Card c = a_discardPile.returnTopCard();
		//a_player->giveCard(a_deck.returnTopCard());
		hand.push_back(c);
		//a_deck.removeTopCard();
		for (int i = 0; i < a_cards.size(); i++) {
			hand.erase(hand.begin() + i);
			if (isBook(hand, a_wildCardNum)) {
				m_reasonForPick = "To build a book";
				return c;
			}
			else if (isRun(hand, a_wildCardNum)) {
				m_reasonForPick = "To build a run";
				return c;
			}
			else if (hasMultipleBooks(hand, a_wildCardNum)) {
				m_reasonForPick = "To build enough books to go out";
				return c;
			}
			else if (hasBooksAndRun(hand, a_wildCardNum)) {
				m_reasonForPick = "To build books and run";
				return c;
			}
			hand.insert(hand.begin() + i, a_cards[i]);
		}

		if (c.getValue() == a_wildCardNum) {
			m_reasonForPick = c.getName() + " is a wild card";
			return c;
		}

		else if (c.getRank() == Joker) {
			m_reasonForPick = c.getName() + " is a Joker";
			return c;
		}
	}

	m_reasonForPick = "The top card of the discard pile has no use";
	return a_drawPile.returnTopCard();
}

/* *********************************************************************
Function Name: findBestCardToDrop
Purpose: finding the best card to drop
Parameters:
	a_cards - hand we have
	a_discardPile - discard pile
	a_drawPile - draw pile
	a_wildCardNum - number of wild card
Return Value: The best card to drop
Local Variables:
	hand
Algorithm:
	1) We go through each card in hand and drop it
	2) We check if when we drop this card can we go out
	3) If yes then we drop it
	4) else we drop card with highest value that isn't a joker or wild card
Assistance Received: None
********************************************************************* */
Card Player::findBestCardToDrop(std::vector<Card> a_cards, int a_wildCardNum, bool a_opponentOut) {
	vector<Card> hand = a_cards;

	for (int i = 0; i < a_cards.size(); i++) {
		hand.erase(hand.begin() + i);
		if (isBook(hand, a_wildCardNum)) {
			m_reasonForDrop = "To build a book";
			return a_cards[i];
		}
		else if (isRun(hand, a_wildCardNum)) {
			m_reasonForDrop = "To build a run";
			return a_cards[i];
		}
		else if (hasMultipleBooks(hand, a_wildCardNum)) {
			m_reasonForDrop = "To build enough books to go out";
			return a_cards[i];
		}
		else if (hasBooksAndRun(hand, a_wildCardNum)) {
			m_reasonForDrop = "To build books and run";
			return a_cards[i];
		}
		hand.insert(hand.begin() + i, a_cards[i]);
	}

	Card highest = a_cards[0];
	for (Card c : a_cards) {
		if (c.getValue() > highest.getValue() && c.getValue() != a_wildCardNum && c.getRank() != Joker && !a_opponentOut) {
			highest = c;
		}
		else if (c.getValue() > highest.getValue()) {
			highest = c;
		}
	}
	if (a_opponentOut) {
		m_reasonForDrop = highest.getName() + " had the highest value and opponent has just gone out";
		return highest;
	}
	else {
		m_reasonForDrop = highest.getName() + " had the highest value and wasn't a joker or wild card";
		return highest;
	}
	
	m_reasonForDrop = "There were no good options";
	return a_cards[0];
}
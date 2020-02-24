#include "pch.h"
#include "Computer.h"

using namespace std;

/* *********************************************************************
Function Name: pickCard
Purpose: function for the computer to pick a card
Parameters:
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	&a_wildCardNum - the number of the wild card
Return Value:
Local Variables:
	c - best card to take
Algorithm:
	1) Finds best card to take
	2) Takes that card
Assistance Received: None
********************************************************************* */
void Computer::pickCard(Deck& a_discardPile, Deck& a_drawPile, int a_wildCardNum) {
	//Take from draw pile
	//giveCard(a_drawPile.returnTopCard()); //Giving top card of draw pile to computer
	Card c = findBestCardToTake(returnHand(), a_discardPile, a_drawPile, a_wildCardNum);
	cout << "\nPick: The computer chose to take " << c.getName() << "\nReason: " << getReasonToPick() << "\n\n";
	
	//cout << "The computer chose to take " << a_drawPile.returnTopCard().getName() << " because I don't know yet." << endl;

	if (c.getName().compare(a_discardPile.returnTopCard().getName()) == 0) {
		giveCard(a_discardPile.returnTopCard());
		a_discardPile.removeTopCard();
	}
	else {
		giveCard(a_drawPile.returnTopCard());
		a_drawPile.removeTopCard();
	}
	//a_drawPile.removeTopCard(); //Removing top card of draw pile
	

	//Take from discard pile
	//giveCard(a_discardPile.returnTopCard()); //Giving top card of discard pile to computer
	//a_discardPile.removeTopCard(); //Removing top card of discard pile
}

/* *********************************************************************
Function Name: dropCard
Purpose: function for computer to discard a card to discard pile
Parameters:
	a_discardPile - discard pile
	a_wildCardNum - wild card number
	a_opponentOut - true if opponent has gone out
Return Value:
Local Variables:
	c - card to drop
Algorithm:
	1) Find best card from discard pile and take it
Assistance Received: None
********************************************************************* */
void Computer::dropCard(Deck& a_discardPile, int a_wildCardNum, bool a_opponentOut) {
	Card c = findBestCardToDrop(returnHand(), a_wildCardNum, a_opponentOut);
	cout << "Drop: The computer chose to drop " << c.getName() << "\nReason: " << getReasonToDrop() << "\n\n";
	int index = 0;
	for (int i = 0; i < returnHand().size(); i++) {
		if (c.getName().compare(returnHand()[i].getName()) == 0) {
			index = i;
		}
	}
	a_discardPile.addCard(getCardAt(index));
	removeCardAt(index);

	//a_discardPile.addCard(getCardAt(0)); //Giving card to discard pile
	//cout << "The computer chose to drop " << getCardAt(0).getName() << " because I don't know yet." << endl;
	//removeCardAt(0); //Removing card in pile
}

/* *********************************************************************
Function Name: goOut
Purpose: Called when the computer has gone out
Parameters:
Return Value:
Local Variables:
Algorithm:
	1) sets to true that player has gone out
Assistance Received: None
********************************************************************* */
void Computer::goOut() {
	cout << "Computer Player has gone out!" << endl;
	cout << getGoOutHand() << endl;
	//clearHand();
	setWentOut(true);
	//system("PAUSE");
}

/* *********************************************************************
Function Name: makeMove
Purpose: makes a move for the computer
Parameters:
	a_opponent - opponent playerr
	&a_deck - main deck for game
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	a_wildCardNum - wild card number
Return Value:
Local Variables:
	sum - sum added to score
Algorithm:
	1) picks a card
	2) drops a card
	3) if can go out then goes out
	4) if opponent has gone out then displays cards
Assistance Received: None
********************************************************************* */
void Computer::makeMove(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum)
{
	pickCard(a_discardPile, a_drawPile, a_wildCardNum);
	dropCard(a_discardPile, a_wildCardNum, a_opponent->returnWentOut());
	if (canGoOut(a_wildCardNum)) {
		goOut();
		if (!a_opponent->returnWentOut()) {
			setGoesFirst(true);
		}
	}
	else if (a_opponent->returnWentOut()) {
		int sum = 0;
		/*
		for (Card c : returnHand()) {
			if (c.getValue() == a_wildCardNum) {
				sum += 20;
			}
			else {
				sum += c.getValue();
			}
		}
		*/
		sum = loseRound(returnHand(), a_wildCardNum);
		addToScore(sum);
		cout << "Computer player has lost the round and has " << sum << " points added to their score" << endl;
		vector<vector<Card>> books = findBooks(returnHand(), a_wildCardNum);
		if (books.size() > 0) {
			string booksString = "Books: \n";
			for (vector<Card> book : books) {
				booksString += "\t";
				for (Card c : book) {
					booksString += c.getName() + " ";
				}
				booksString += "\n";
			}
			cout << booksString << endl;
		}
		bool inBook = false;
		vector<Card> potentialRun = findRun(returnHand(), a_wildCardNum);
		if (isRun(potentialRun, a_wildCardNum)) {
			string runString = "Run: \n\t";
			for (Card myCard : potentialRun) {
				runString += myCard.getName() + " ";
			}
			runString += "\n";
			cout << runString << endl;
		}

		bool inBookOrRun = false;
		cout << "Remaining Cards: ";
		
		for (Card card : returnHand()) {
			inBookOrRun = false;
			if (books.size() > 0) {
				for (vector<Card> book : books) {
					for (Card c : book) {
						if (card.getId() == c.getId()) {
							inBookOrRun = true;
							break;
						}
					}
				}
			}
			if (isRun(potentialRun, a_wildCardNum)) {
				for (Card c : potentialRun) {
					if (card.getId() == c.getId()) {
						inBookOrRun = true;
						break;
					}
				}
			}
			if (!inBookOrRun) {
				cout << card.getName() << " ";
			}
		}
		cout << endl;
		setWentOut(true);
	}
}

/* *********************************************************************
Function Name: chooseOption
Purpose: Asks if the player wants to save the game
Parameters:
	a_opponent - opponent playerr
	&a_deck - main deck for game
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	a_wildCardNum - wild card number
Return Value:
Local Variables:
	choice - y if the player wants to save
Algorithm:
Assistance Received: None
********************************************************************* */
void Computer::chooseOption(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum)
{
	char choice;
	cout << "Would you like to save the game? Yes (y) No (n)" << endl;
	cin >> choice;
	if (choice == 'y') {
		saveGame(a_opponent, a_deck, a_discardPile, a_drawPile, a_wildCardNum);
	}
	makeMove(a_opponent, a_deck, a_discardPile, a_drawPile, a_wildCardNum);
}

/* *********************************************************************
Function Name: saveGame
Purpose: Saves the game to SavedGame.txt
Parameters:
	a_opponent - opponent playerr
	&a_deck - main deck for game
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	a_wildCardNum - wild card number
Return Value:
Local Variables:
	str - string of saved game
	file - saved game file
Algorithm:
Assistance Received: None
********************************************************************* */
void Computer::saveGame(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum)
{
	string str = "";
	ofstream file("SavedGame.txt");

	str += "Round: " + to_string(a_wildCardNum - 2) + "\n\n";

	str += "Computer:\n";
	str += "\tScore: " + to_string(returnScore()) + "\n";
	str += "\tHand: " + returnHandString() + "\n\n";

	str += "Human:\n";
	str += "\tScore: " + to_string(a_opponent->returnScore()) + "\n";
	str += "\tHand: " + a_opponent->returnHandString() + "\n\n";

	str += "Draw Pile: " + a_drawPile.returnDeckString() + "\n\n";

	str += "Discard Pile: " + a_discardPile.returnDeckString() + "\n\n";

	str += "Next Player: Computer";

	file << str;
}
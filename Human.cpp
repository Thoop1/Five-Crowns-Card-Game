#include "pch.h"
#include "Human.h"

using namespace std;

/* *********************************************************************
Function Name: pickCard
Purpose: function for the human to pick a card
Parameters:
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	&a_wildCardNum - the number of the wild card
Return Value:
Local Variables:
	choice - choice for discard or draw pile
Algorithm:
	1) Ask if you want to take from discard or draw pile
	2) Takes that card
Assistance Received: None
********************************************************************* */
void Human::pickCard(Deck& a_discardPile, Deck& a_drawPile, int a_wildCardNum) {
	int choice = 0;

	do {
		cout << "Take the top card from the draw pile (1) or top card from the discard pile (2): ";
		cin >> choice;
	} while (!(choice == 1 || choice == 2));
	//Take from draw pile
	if (choice == 1) {
		giveCard(a_drawPile.returnTopCard()); //Giving top card of draw pile to human
		a_drawPile.removeTopCard(); //Removing top card of draw pile
	}
	//Take from discard pile
	else if (choice == 2) {
		giveCard(a_discardPile.returnTopCard()); //Giving top card of discard pile to human
		a_discardPile.removeTopCard(); //Removing top card of discard pile
	}
}

/* *********************************************************************
Function Name: dropCard
Purpose: function for human to discard a card to discard pile
Parameters:
	a_discardPile - discard pile
	a_wildCardNum - wild card number
	a_opponentOut - true if opponent has gone out
Return Value:
Local Variables:
Algorithm:
	1) Choose a card from hand to drop
Assistance Received: None
********************************************************************* */
void Human::dropCard(Deck& a_discardPile, int a_wildCardNum, bool a_opponentOut) {
	string cardName = "";
	do {
		cout << "Choose a card to drop: ";
		cin.ignore();
		getline(cin, cardName);
	} while (!checkIfNameEqualsCard(cardName));
	a_discardPile.addCard(returnCardByName(cardName));//Giving card to discard pile
	removeCardByName(cardName);//Removing card in pile
}

/* *********************************************************************
Function Name: goOut
Purpose: Called when the human has gone out
Parameters:
Return Value:
Local Variables:
Algorithm:
	1) sets to true that player has gone out
Assistance Received: None
********************************************************************* */
void Human::goOut() {
	/*
	char choice;
	do {
		cout << "Would you like to go out? (y/n)" << endl;
		cin >> choice;
	} while (!(choice == 'y' || choice == 'n'));
	if (choice == 'y') {
		
	}
	else if (choice == 'n') {

	}
	*/
	cout << "Human Player has gone out!" << endl;
	cout << getGoOutHand() << endl;
	//clearHand();
	setWentOut(true);
	//system("PAUSE");
}

/* *********************************************************************
Function Name: makeMove
Purpose: Called when human makes a move
Parameters:
	a_opponent - opponent player
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
void Human::makeMove(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum) {
	pickCard(a_discardPile, a_drawPile, a_wildCardNum);
	dropCard(a_discardPile, a_wildCardNum, a_opponent->returnWentOut());
	if (canGoOut(a_wildCardNum)) { 
		char choice;
		cout << "Would you like to go out? Yes (y) or No (n)" << endl;
		cin >> choice;
		if (choice == 'y') {
			goOut();
			if (!a_opponent->returnWentOut()) {
				setGoesFirst(true);
			}
		}
		else {
			if (a_opponent->returnWentOut()) {
				goOut();
			}
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
		cout << "Human player has lost the round and has " << sum << " points added to their score" << endl;
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
Purpose: Asks if the player wants to save the game, make a move, ask for
help or quit
Parameters:
	a_opponent - opponent playerr
	&a_deck - main deck for game
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	a_wildCardNum - wild card number
Return Value:
Local Variables:
	choice - choice the player makes
Algorithm:
Assistance Received: None
********************************************************************* */
void Human::chooseOption(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum)
{
	char choice;
	cout << "Choose An Option" << endl;
	cout << "1. Save Game\n2. Make a move\n3. Ask for help\n4. Quit the game" << endl;
	do {
		cin >> choice;
		switch (choice) {
		case '1':
			saveGame(a_opponent, a_deck, a_discardPile, a_drawPile, a_wildCardNum);
			cout << "Game Saved!\n";
			break;

		case '2':
			makeMove(a_opponent, a_deck, a_discardPile, a_drawPile, a_wildCardNum);
			break;

		case'3':
			getHelp(a_discardPile, a_drawPile, a_wildCardNum, a_opponent->returnWentOut());
			break;

		case '4':
			//quit
			cout << "Quitting Game" << endl;
			exit(0);
			break;
		default:
			break;
		}
	} while (choice != '2');
}

/* *********************************************************************
Function Name: saveGame
Purpose: Saves the game to SavedGame.txt
Parameters:
	a_opponent - opponent player
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
void Human::saveGame(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum)
{
	string str = "";
	ofstream file("SavedGame.txt");

	str += "Round: " + to_string(a_wildCardNum - 2) + "\n\n";

	str += "Computer:\n";
	str += "\tScore: " + to_string(a_opponent->returnScore()) + "\n";
	str += "\tHand: " + a_opponent->returnHandString() + "\n\n";

	str += "Human:\n";
	str += "\tScore: " + to_string(returnScore()) + "\n";
	str += "\tHand: " + returnHandString() + "\n\n";

	str += "Draw Pile: " + a_drawPile.returnDeckString() + "\n\n";

	str += "Discard Pile: " + a_discardPile.returnDeckString() + "\n\n";

	str += "Next Player: Human";

	file << str;
}

/* *********************************************************************
Function Name: gethelp
Purpose: gets help from the computer
Parameters:
	&a_discardPile - discard pile
	&a_drawPile - draw pile
	a_wildCardNum - wild card number
	a_opponentOut - true if opponent has gone out
Return Value:
Local Variables:
	pick - card recommended to take
	drop - card recommended to drop
Algorithm:
Assistance Received: None
********************************************************************* */
void Human::getHelp(Deck a_discardPile, Deck a_drawPile, int a_wildCardNum, bool a_opponentOut) {
	Card pick = findBestCardToTake(returnHand(), a_discardPile, a_drawPile, a_wildCardNum);
	Card drop = findBestCardToDrop(returnHand(), a_wildCardNum, a_opponentOut);
	cout << "Pick: The computer recommends you take " << pick.getName() << "\nReason: " << getReasonToPick() << "\n\n";
	cout << "Drop: The computer recommends you drop " << drop.getName() << "\nReason: " << getReasonToDrop() << "\n\n";
}
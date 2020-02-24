#include "pch.h"
#include "Round.h"

using namespace std;






/* *********************************************************************
Function Name: displayRound
Purpose: displays the current round
Parameters:
	a_human - human player
	a_comp - computer player
	a_deck - main deck
	a_discardPile - discard pile
	a_drawPile - draw pile
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Round::displayRound(Player* a_human, Player* a_comp, Deck a_deck, Deck a_discardPile, Deck a_drawPile)
{
	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Round: " << m_roundNum << endl;
	cout << "Computer:\n\tScore: " << a_comp->returnScore() << endl;
	cout << "\tHand: " << a_comp->returnHandString() << endl;
	cout << "\nHuman:\n\tScore: " << a_human->returnScore() << endl;
	cout << "\tHand: " << a_human->returnHandString() << endl;
	cout << "\nDraw Pile: " << a_drawPile.returnDeckString() << endl;
	cout << "\nDiscard Pile: " << a_discardPile.returnDeckString() << endl;
	cout << "\nNext Player: " << getNextPlayer() << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
}

/* *********************************************************************
Function Name: playRound
Purpose: plays the current round
Parameters:
	a_human - human player
	a_comp - computer player
	a_deck - main deck
	a_discardPile - discard pile
	a_drawPile - draw pile
	a_loaded - true if the game was loaded from a text file
Return Value:
Local Variables:
Algorithm:
	1) First it checks if the human has a hand
	2) If it does then this means this is not from a save file
	and we have normal set up for game
	3) If it is the first round then we have a coin toss and the
	player who wons goes first
	4) else the player who went out first on the previous round
	goes first
	5) gives cards to each player based on what round number it is
	6) puts remaining cards in draw pile and puts top card of draw pile
	into discard pile
	7) We set next player as player who goes first
	8) while both players have not gone out we playRound
	9) When round is over we call endRound
Assistance Received: None
********************************************************************* */
void Round::playRound(Player* a_human, Player* a_comp, Deck &a_deck, Deck& a_discardPile, Deck& a_drawPile, bool a_loaded)
{
	if (!a_human->returnHand().size() > 0) {
		a_human->setWentOut(false);
		a_comp->setWentOut(false);

		//if this is the first round then a coin toss determines first player
		if (m_roundNum == 1 && !a_loaded) {
			coinToss(a_human, a_comp);
		}

		//Shuffling our deck. This is done in Game though
		//a_deck.shuffleDeck();

		//Dealing Cards at the beginning of the turn
		for (int i = 0; i < m_roundNum + 2; i++) {
			giveCardToPlayer(a_human, a_deck);
			giveCardToPlayer(a_comp, a_deck);
		}

		//Putting remaining cards in draw pile
		a_drawPile = a_deck;

		//Giving top card of draw pile to discard pile
		giveCardToPile(a_drawPile, a_discardPile);

		//Setting string for next player
		if (a_human->getGoesFirst()) {
			setNextPlayer("Human");
		}
		else if (a_comp->getGoesFirst()) {
			setNextPlayer("Computer");
		}
	}
	
	if (a_human->getGoesFirst()) {
		setNextPlayer("Human");
	}
	else if (a_comp->getGoesFirst()) {
		setNextPlayer("Computer");
	}
	//Print the round to the screen
	displayRound(a_human, a_comp, a_deck, a_discardPile, a_drawPile);

	while (!(a_human->returnWentOut() && a_comp->returnWentOut())) {
		playTurns(a_human, a_comp, a_deck, a_discardPile, a_drawPile);
	}
	endRound(a_human, a_comp, a_deck, a_discardPile, a_drawPile);
}

/* *********************************************************************
Function Name: giveCardToPlayer
Purpose: Gives a card from top of deck passed in to the player 
passed in
Parameters:
	a_player - player getting the card
	&a_deck - deck we take from
Return Value:
Local Variables:
	c - card at top of deck
Algorithm:
	1) Get card from top of deck
	2) give it to player
	3) remove the card from deck passed in 
Assistance Received: None
********************************************************************* */
void Round::giveCardToPlayer(Player* a_player, Deck &a_deck) {
	Card c = a_deck.returnTopCard();
	//a_player->giveCard(a_deck.returnTopCard());
	a_player->giveCard(c);
	a_deck.removeTopCard();
}



//Gives the top card of givingDeck to receivingDeck
/* *********************************************************************
Function Name: giveCardToPile
Purpose: Gives a card from top of deck passed in to the deck
passed in
Parameters:
	&a_givingDeck - deck giving the card
	&a_receivingDeck - deck getting card
Return Value:
Local Variables:
Algorithm:
	1) Get card from top of deck
	2) give it to other deck
	3) remove the card from deck passed in
Assistance Received: None********************************************************************* */
void Round::giveCardToPile(Deck &a_givingDeck, Deck &a_receivingDeck)
{
	a_receivingDeck.addCard(a_givingDeck.returnTopCard());
	a_givingDeck.removeTopCard();
}

/* *********************************************************************
Function Name: coinToss
Purpose: Coin toss to begin game
Parameters:
	a_human
	a_computer
Return Value:
Local Variables:
	randNum - for coin toss
	coinSide - h or t
Algorithm:
	1) Generate random number for coin toss
	2) if human guesses correctly then we set a_human to go first
	3) if incorrect we set a_comp to go first
Assistance Received: None
********************************************************************* */
void Round::coinToss(Player* a_human, Player* a_computer) {
	srand(time(NULL));
	int randNum = (rand() % 10) + 1;
	char coinSide;
	cout << "Enter Heads (h) or Tails (t): ";
	cin >> coinSide;
	if (randNum > 5) {
		if (coinSide == 'h') {
			cout << "Human Goes First" << endl;
			a_human->setGoesFirst(true);
			a_computer->setGoesFirst(false);
		}
		else if (coinSide == 't') {
			cout << "Computer Goes First" << endl;
			a_human->setGoesFirst(false);
			a_computer->setGoesFirst(true);
		}
	}
	else {
		if (coinSide == 'h') {
			cout << "Computer Goes First" << endl;
			a_human->setGoesFirst(false);
			a_computer->setGoesFirst(true);
		}
		else if (coinSide == 't') {
			cout << "Human Goes First" << endl;
			a_human->setGoesFirst(true);
			a_computer->setGoesFirst(false);
		}
	}
}


/* *********************************************************************
Function Name: playTurns
Purpose: play the turns for each player
Parameters:
	a_human - human player
	a_comp - computer player
	a_deck - main deck
	a_discardPile - discard pile
	a_drawPile - draw pile
Return Value:
Local Variables:
Algorithm:
	Play the turns for each player depending on who goes first
Assistance Received: None
********************************************************************* */
void Round::playTurns(Player* a_player1, Player* a_player2, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile) {
	if (a_player1->getGoesFirst() && !a_player1->returnWentOut()) {
		setNextPlayer("Human");
		playTurn(a_player1, a_player2, a_deck, a_discardPile, a_drawPile);
		if (a_player1->returnWentOut() && a_player2->returnWentOut()) {
			return;
		}
		if (a_drawPile.getDeck().size() == 0) {
			reshuffleDecks(a_discardPile, a_drawPile);
		}
		setNextPlayer("Computer");
		displayRound(a_player1, a_player2, a_deck, a_discardPile, a_drawPile);
		playTurn(a_player2, a_player1, a_deck, a_discardPile, a_drawPile);
		if (a_player1->returnWentOut() && a_player2->returnWentOut()) {
			return;
		}
		if (a_drawPile.getDeck().size() == 0) {
			reshuffleDecks(a_discardPile, a_drawPile);
		}
		setNextPlayer("Human");
		displayRound(a_player1, a_player2, a_deck, a_discardPile, a_drawPile);
	}

	else if (a_player2->getGoesFirst() && !a_player2->returnWentOut()) {
		setNextPlayer("Computer");
		playTurn(a_player2, a_player1, a_deck, a_discardPile, a_drawPile);
		if (a_player1->returnWentOut() && a_player2->returnWentOut()) {
			return;
		}
		if (a_drawPile.getDeck().size() == 0) {
			reshuffleDecks(a_discardPile, a_drawPile);
		}
		setNextPlayer("Human");
		displayRound(a_player1, a_player2, a_deck, a_discardPile, a_drawPile);
		playTurn(a_player1, a_player2, a_deck, a_discardPile, a_drawPile);
		if (a_player1->returnWentOut() && a_player2->returnWentOut()) {
			return;
		}
		if (a_drawPile.getDeck().size() == 0) {
			reshuffleDecks(a_discardPile, a_drawPile);
		}
		setNextPlayer("Computer");
		displayRound(a_player1, a_player2, a_deck, a_discardPile, a_drawPile);
	}
}

/* *********************************************************************
Function Name: playTurn
Purpose: calls chooseOption for the player
Parameters:
	a_human - human player
	a_comp - computer player
	a_deck - main deck
	a_discardPile - discard pile
	a_drawPile - draw pile
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Round::playTurn(Player * a_player, Player* a_player2, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile)
{
	/*
	//draw card from discard pile of draw pile
	a_player->pickCard(a_discardPile, a_drawPile);

	//Tries to assemble the cards in hand as runs and books:

	//Discard one card on to the discard pile.
	a_player->dropCard(a_discardPile);

	//If all the remaining cards in the player's hand can be arranged in runs and/or books, the player will go out by 
	//displaying the runs and books.
	if (a_player->canGoOut()) {
		a_player->goOut();
		m_playerOut == true;
		a_player->setWentOut(true);
	}

	//If the other player has just gone out, the player will display all the runs and books in her / his hand.
	//The sum of the values of the remaining cards in the player's hand will be the points awarded to the player.
	else if (a_player2->returnWentOut()) {
		a_player->goOut();
		m_playerOut == true;
		a_player->setWentOut(true);
	}
	*/
	
	a_player->chooseOption(a_player2, a_deck, a_discardPile, a_drawPile, m_roundNum + 2);
}

/* *********************************************************************
Function Name: endRound
Purpose: called when a round has ended
Parameters:
	a_human - human player
	a_comp - computer player
	a_deck - main deck
	a_discardPile - discard pile
	a_drawPile - draw pile
Return Value:
Local Variables:
Algorithm:
	1) Print the score of each player
	2) Clear the hands and decks
Assistance Received: None
********************************************************************* */
void Round::endRound(Player * a_player, Player * a_player2, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile)
{
	cout << "\nRound " << m_roundNum << " has ended" << endl;
	cout << "Human Score: " << a_player->returnScore() << endl;
	cout << "Computer Score: " << a_player2->returnScore() << endl;
	returnCardsToDeck(a_player, a_player2, a_deck, a_discardPile, a_drawPile);
}


//Return cards to deck
/* *********************************************************************
Function Name: returnCardsToDeck
Purpose: clear the hands and decks
Parameters:
	a_human - human player
	a_comp - computer player
	a_deck - main deck
	a_discardPile - discard pile
	a_drawPile - draw pile
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Round::returnCardsToDeck(Player* a_player, Player* a_player2, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile) {
	//a_deck = a_discardPile;
	//a_deck.addDeck(a_drawPile);
	//a_deck.addDeck(a_player->returnHand());
	//a_deck.addDeck(a_player2->returnHand());
	a_discardPile.clearDeck();
	a_drawPile.clearDeck();
	a_player->clearHand();
	a_player2->clearHand();
}

/* *********************************************************************
Function Name: reshuffleDecks
Purpose: reshuffle the discard pile into the draw pile if the draw pile
has run out of cards
Parameters:
	&a_discardPile, &a_drawPile
Return Value:
Local Variables:
Algorithm:
Assistance Received: None
********************************************************************* */
void Round::reshuffleDecks(Deck & a_discardPile, Deck & a_drawPile)
{
	a_drawPile = a_discardPile;
	a_discardPile.clearDeck();
	a_drawPile.shuffleDeck();
}
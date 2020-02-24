#pragma once
#include "pch.h"
#include "Deck.h"
#include "Book.h"
#include "Run.h"

class Player {
private:
	std::vector<Card> m_hand;
	int m_score;
	bool m_goesFirst;
	bool m_wentOut = false;
	std::string m_reasonForDrop;
	std::string m_reasonForPick;
	std::string m_goOutHand;


public:
	Player() {}
	~Player() {}

	/* *********************************************************************
	Function Name: Player
	Purpose: Constructor for this class
	Parameters:
	Return Value:
		a_hand - hand we give to player
		a_score - score we give to player
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	Player(std::vector<Card> a_hand, int a_score) {
		m_hand = a_hand;
		m_score = a_score;
	}

	/* *********************************************************************
	Function Name: setGoOutHand
	Purpose: setting the string that represents our hand when we go out
	Parameters:	
		a_outHand - the string that represents our hand when we go out
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setGoOutHand(std::string a_outHand) { m_goOutHand = a_outHand; }
	
	/* *********************************************************************
	Function Name: getGoOutHand
	Purpose: getting the string that represents our hand when we go out
	Parameters:	
	Return Value: the string that represents our hand when we go out
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	std::string getGoOutHand() { return m_goOutHand; }

	/* *********************************************************************
	Function Name: addToScore
	Purpose: add a number to our score
	Parameters:
		a_num - number added to score
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void addToScore(int a_num) { m_score += a_num; }

	virtual void pickCard(Deck& a_discardPile, Deck& a_drawPile, int a_wildCardNum) = 0;

	virtual void dropCard(Deck& a_discardPile, int a_wildCardNum, bool a_opponentOut) = 0;

	virtual void goOut() = 0;

	virtual void makeMove(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum) = 0;

	virtual void chooseOption(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum) = 0;

	bool canGoOut(int a_wildCardNum);

	std::string returnHandString();

	void printHand();

	/* *********************************************************************
	Function Name: returnHand
	Purpose: return the hand of the player
	Parameters:
	Return Value: the hand of the player
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	std::vector<Card> returnHand() { return m_hand; }
	
	/* *********************************************************************
	Function Name: setHand
	Purpose: set the hand of the player
	Parameters:	
		a_hand - set the hand of this player
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setHand(std::vector<Card> a_hand) { m_hand = a_hand; }

	/* *********************************************************************
	Function Name: getCardAt
	Purpose: get the card of this player at specified index
	Parameters:	a_index = the index of the card we want
	Return Value: the card at the specified index
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	Card getCardAt(int a_index) { return m_hand.at(a_index); }
	
	/* *********************************************************************
	Function Name: removeCardAt
	Purpose: removes card at the specified index
	Parameters:
		a_index - index of the card we remove
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void removeCardAt(int a_index) { m_hand.erase(m_hand.begin() + a_index); }

	/* *********************************************************************
	Function Name: returnScore
	Purpose: return the score of player
	Parameters:
	Return Value: score of player
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	int returnScore() { return m_score; }
	
	/* *********************************************************************
	Function Name: setScore
	Purpose: set the score of the player
	Parameters:
		a_score - score of player
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setScore(int a_score) { m_score = a_score; }

	/* *********************************************************************
	Function Name: returnWentOut
	Purpose: returns true if the player has gone out
	Parameters:
	Return Value: bool that tells us if player has gone out
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	bool returnWentOut() { return m_wentOut; }
	
	/* *********************************************************************
	Function Name: setWentOut
	Purpose: set if the player has gone out
	Parameters:
		a_wentOut - sets true if the player has gone out
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setWentOut(bool a_wentOut) { m_wentOut = a_wentOut; }

	/* *********************************************************************
	Function Name: giveCard
	Purpose: gives a card to the player
	Parameters:
		a_card - the card we are giving to the player
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void giveCard(Card a_card) { m_hand.push_back(a_card); }

	/* *********************************************************************
	Function Name: removeCard
	Purpose: remove the specified card from the player
	Parameters: 
		a_card - the card we want to remove
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void removeCard(Card a_card);

	void removeCardByName(std::string a_cardName);

	/* *********************************************************************
	Function Name: setGoesFirst
	Purpose: set if the player goes first
	Parameters:
		a_goesFirst
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setGoesFirst(bool a_goesFirst) { m_goesFirst = a_goesFirst; }

	/* *********************************************************************
	Function Name: getGoesFirst
	Purpose: returns true if we go first
	Parameters:
	Return Value: bool representing if player goes first
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	int getGoesFirst() { return m_goesFirst; }

	//Checking if the name entered equals a card's name in hand
	bool checkIfNameEqualsCard(std::string a_cardName);

	Card returnCardByName(std::string a_cardName);

	/* *********************************************************************
	Function Name: compareValues
	Purpose: used for sorting cards from least to greatest values
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	static bool compareValues(Card a_card1, Card a_card2){ return (a_card1.getValue() < a_card2.getValue()); }

	/* *********************************************************************
	Function Name: clearHand
	Purpose: clears the hand of player
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	void clearHand() { m_hand.clear(); }

	void hasBooksAndRuns(std::vector<Card> a_cards, int a_wildCardNum);

	bool isRun(std::vector<Card> a_cards, int a_wildCardNum);
	bool isBook(std::vector<Card> a_cards, int a_wildCardNum);

	bool isRun(std::vector<Card> a_cards, std::vector<Card> a_jokersAndWilds, int a_wildCardNum);
	bool isBook(std::vector<Card> a_cards, std::vector<Card> a_jokersAndWilds, int a_wildCardNum);

	std::string getBookString(std::vector<Card> a_cards, int a_wildCardNum);
	std::string getRunString(std::vector<Card> a_cards, int a_wildCardNum);

	std::vector<std::vector<Card>> assembleBooksAndRuns(std::vector<Card> a_cards, int a_wildCardNum);

	std::vector<std::vector<Card>> findBooks(std::vector<Card> a_cards, int a_wildCardNum);
	std::vector<std::vector<Card>> findRuns(std::vector<Card> a_cards, int a_wildCardNum);

	std::vector<Card> findRun(std::vector<Card> a_cards, int a_wildCardNum);

	bool hasBooksAndRun(std::vector<Card> a_cards, int a_wildCardNum);

	int loseRound(std::vector<Card> a_cards, int a_wildCardNum);

	Card findBestCardToTake(std::vector<Card> a_cards, Deck a_discardPile, Deck a_drawPile, int a_wildCardNum);

	Card findBestCardToDrop(std::vector<Card> a_cards, int a_wildCardNum, bool a_opponentOut);

	/* *********************************************************************
	Function Name: getReasonToDrop
	Purpose: returns the reason player has dropped card
	Parameters:
	Return Value: reason player has dropped card
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	std::string getReasonToDrop() { return m_reasonForDrop; }
	
	/* *********************************************************************
	Function Name: getReasonToPick
	Purpose: gets the reason player has picked card
	Parameters:
	Return Value: reason player has picked card
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	std::string getReasonToPick() { return m_reasonForPick; }

	bool hasMultipleBooks(std::vector<Card> a_cards, int a_wildCardNum);
};
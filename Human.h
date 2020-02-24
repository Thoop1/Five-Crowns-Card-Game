#pragma once
#include "pch.h"
#include "Player.h"

class Human : public Player {
public:
	Human(){}
	~Human() {}


	/* *********************************************************************
	Function Name: Human
	Purpose: Constructor for the Human class
	Parameters:
		a_hand - hand we initialize human with
		a_score - score we initalize human with
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	Human(std::vector<Card> a_hand, int a_score) {
		this->setHand(a_hand);
		this->setScore(a_score);
	}
	
	void pickCard(Deck& a_discardPile, Deck& a_drawPile, int a_wildCardNum);

	void dropCard(Deck& a_discardPile, int a_wildCardNum, bool a_opponentOut);

	void goOut();

	void makeMove(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum);

	void chooseOption(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum);

	void saveGame(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum);

	void getHelp(Deck a_discardPile, Deck a_drawPile, int a_wildCardNum, bool a_opponentOut);
};
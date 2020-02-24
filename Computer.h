#pragma once
#include "pch.h"
#include "Player.h"

class Computer : public Player {
public:
	Computer() {}
	~Computer() {}


	/* *********************************************************************
	Function Name: Computer
	Purpose: Constructor for this class
	Parameters:
		a_hand - hand of computer
		a_score - score of computer
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	Computer(std::vector<Card> a_hand, int a_score) {
		this->setHand(a_hand);
		this->setScore(a_score);
	}

	void pickCard(Deck& a_discardPile, Deck& a_drawPile, int a_wildCardNum);

	void dropCard(Deck& a_discardPile, int a_wildCardNum, bool a_opponentOut);

	void goOut();

	void makeMove(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum);

	void chooseOption(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum);

	void saveGame(Player * a_opponent, Deck & a_deck, Deck & a_discardPile, Deck & a_drawPile, int a_wildCardNum);
};
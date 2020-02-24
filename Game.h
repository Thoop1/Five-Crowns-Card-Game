#pragma once
#include "pch.h"
#include "Deck.h"
#include "Computer.h"
#include "Human.h"
#include "Round.h"


class Game {

private:
	Player* m_computer;
	Player* m_human;
	Deck m_deck1;

	Deck m_deck2;
	Deck m_mainDeck;
	Deck m_discardPile;
	Deck m_drawPile;
	std::vector<Round> m_rounds;
	Round m_currentRound;
	int m_roundNum;
	bool m_loaded = false;
	
public:
	Game(){}

	Game(Deck a_mainDeck, Deck a_discardPile, Deck a_drawPile, Player* a_computer, Player* a_human, int a_roundNum);

	void initializeGame();

	/* *********************************************************************
	Function Name: playGame
	Purpose: Plays the entire game
	Parameters: 
		a_loaded - if true then the game has been loaded from a text file
	Return Value:
	Local Variables:
	Algorithm:
	1) Until the round number is 11 we call playRound
	Assistance Received: None
	********************************************************************* */
	void playGame(bool a_loaded) {
		for (int i = m_roundNum; i <= 11; i++) {
			Round r(i);
			r.playRound(m_human, m_computer, m_mainDeck, m_discardPile, m_drawPile, a_loaded);
			shuffleDecks();
		}
	}

	void shuffleDecks();

	void loadGame(std::string a_fileName);

	Card createCard(std::string a_cardName, int a_id);

	void endGame();

	void assignCardIds(Deck& a_deck);
};
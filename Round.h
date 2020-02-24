#pragma once
#include "pch.h"
#include "Deck.h"
#include "Computer.h"
#include "Human.h"

class Round {
private:
	int m_roundNum;
	bool m_playerOut = false;
	std::string m_next;
	
public:

	Round() {}

	Round(int a_roundNum) { m_roundNum = a_roundNum; }

	void playRound(Player* a_human, Player* a_comp, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile, bool a_loaded);

	void displayRound(Player* a_human, Player* a_comp, Deck a_deck, Deck a_discardPile, Deck a_drawPile);

	void giveCardToPlayer(Player* a_player, Deck& a_deck);

	void giveCardToPile(Player* a_player, Deck& a_deck);

	void giveCardToPile(Deck& a_givingDeck, Deck& a_receivingDeck);

	void coinToss(Player* a_human, Player* a_computer);

	void playTurns(Player* a_player1, Player* a_player2, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile);

	void playTurn(Player* a_player, Player* a_player2, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile);

	void displayMenu();

	void endRound(Player* a_player, Player* a_player2, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile);

	void returnCardsToDeck(Player* a_player, Player* a_player2, Deck& a_deck, Deck& a_discardPile, Deck& a_drawPile);

	std::string getNextPlayer() { return m_next; }

	void setNextPlayer(std::string a_next) { m_next = a_next; }

	void reshuffleDecks(Deck& a_discardPile, Deck& a_drawPile);
};
#pragma once
#include "pch.h"
#include "Card.h"

class Deck {

private:
	std::vector<Card> m_deck;

public:




	/* *********************************************************************
	Function Name: getDeck
	Purpose: get the cards of this deck
	Parameters:
	Return Value: the cards of this deck
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	std::vector<Card> getDeck() {
		return m_deck;
	}

	/* *********************************************************************
	Function Name: setDeck
	Purpose: set cards of deck
	Parameters: 
		a_deck - cards of deck
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setDeck(std::vector<Card> a_deck) {
		m_deck = a_deck;
	}

	/* *********************************************************************
	Function Name: addCard
	Purpose: add a card to the deck
	Parameters:
		a_card - card we add to this deck
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void addCard(Card a_card) {
		m_deck.push_back(a_card);
	}

	/* *********************************************************************
	Function Name: giveCardFront
	Purpose: add a card to the front of the deck
	Parameters: 
		a_card - card we are adding to the front of the deck
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void giveCardFront(Card a_card) {
		m_deck.insert(m_deck.begin(), a_card);
	}

	/* *********************************************************************
	Function Name: returnTopCard
	Purpose: return the top card of the deck
	Parameters:
	Return Value: card at the top of the deck
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	Card returnTopCard() {
		return m_deck.back();
	}

	/* *********************************************************************
	Function Name: removeTopCard
	Purpose: remove the top card from the deck
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void removeTopCard() {
		m_deck.pop_back();
	}

	/* *********************************************************************
	Function Name: returnCardAt
	Purpose: return the card at the specified index
	Parameters:	
		a_index - index of card we return
	Return Value: card at specified index
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	Card returnCardAt(int a_index) {
		return m_deck[a_index];
	}

	void createDeck();

	void shuffleDeck();

	std::string returnDeckString();

	/* *********************************************************************
	Function Name: printDeck
	Purpose: print our deck
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void printDeck() {
		for (Card c : m_deck) {
			std::cout << c.getName() << " " << std::endl;
		}
	}

	void addDeck(std::vector<Card> a_deck);

	void addDeck(Deck a_deck);

	/* *********************************************************************
	Function Name: clearDeck
	Purpose: clear our deck
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void clearDeck() { m_deck.clear(); }

	bool checkIfNameEqualsCard(std::string a_cardName);

	void assignIds();
};
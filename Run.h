#pragma once
#include "pch.h"
#include "Card.h"

class Run {
private:
	std::vector<Card> m_cards;

public:
	Run(){}

	/* *********************************************************************
	Function Name:
	Purpose:
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	Run(std::vector<Card> a_cards) {
		m_cards = a_cards;
	}
	static bool compareValues(Card a_card1, Card a_card2);

	bool compareSuits(Card a_card, Suit a_suit);

	/* *********************************************************************
	Function Name:
	Purpose:
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	std::vector<Card> getCards() { return m_cards; }

	/* *********************************************************************
	Function Name:
	Purpose:
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	std::vector<Card> setCards(std::vector<Card> a_cards) { m_cards = a_cards; }

	/* *********************************************************************
	Function Name:
	Purpose:
	Parameters:
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	void addCard(Card a_card) {	m_cards.push_back(a_card); }

	static bool isRun(std::vector<Card> a_cards);

	static bool hasRuns(std::vector<Card> a_hand);

	static std::vector<Run> returnRuns(std::vector<Card> a_hand);
};
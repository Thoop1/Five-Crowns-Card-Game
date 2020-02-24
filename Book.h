#pragma once
#include "pch.h"
#include "Card.h"

class Book {
private:
	std::vector<Card> m_cards;

public:
	Book(){}

	Book(std::vector<Card> a_cards) {
		m_cards = a_cards;
	}

	std::vector<Card> getCards() { return m_cards; }

	std::vector<Card> setCards(std::vector<Card> a_cards) { m_cards = a_cards; }

	void addCard(Card a_card) { m_cards.push_back(a_card); }

	static bool isBook(std::vector<Card> a_cards);

	static bool hasBooks(std::vector<Card> a_hand);

	static std::vector<Book> returnBooks(std::vector<Card> a_hand);

	static bool compareValues(Card a_card1, Card a_card2);
};
#include "pch.h"
#include "Book.h"

using namespace std;

bool Book::compareValues(Card a_card1, Card a_card2)
{
	return (a_card1.getValue() < a_card2.getValue());
}


bool Book::isBook(std::vector<Card> a_cards)
{
	//Need at least three cards for a book
	if (a_cards.size() < 3) {
		return false;
	}
	//Sorting based on values
	sort(a_cards.begin(), a_cards.end(), compareValues);

	//If the min element equals the max then true
	if (a_cards[0].getValue() == a_cards[a_cards.size() - 1].getValue()) {
		return true;
	}
	
	return false;
}

bool Book::hasBooks(std::vector<Card> a_hand)
{
	//Need at least three cards for a book
	if (a_hand.size() < 3) {
		return false;
	}

	sort(a_hand.begin(), a_hand.end(), compareValues);
	
	int compValue = compValue = a_hand[0].getValue();
	int count = 0;

	//If card's value equals previous card's value then increment count
	//Else compValue equals the new value of the card and next loop we check if the
	//next card's value is equal to this card's value
	for (Card c : a_hand) {
		if (c.getValue() == compValue)
		{
			count++;
		}
		else {
			compValue = c.getValue();
			count = 0;
		}
		if (count == 3) {
			return true;
		}
	}
	return false;
}


//Unifinished
vector<Book> Book::returnBooks(std::vector<Card> a_hand)
{
	vector<Book> books;
	if (a_hand.size() < 3) {
		return books;
	}

	sort(a_hand.begin(), a_hand.end(), compareValues);

	Book book;
	for (Card c : a_hand) {
		
	}
	
	return books;
}

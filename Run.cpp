#include "pch.h"
#include "Run.h"

using namespace std;


bool Run::compareValues(Card a_card1, Card a_card2)
{
	return (a_card1.getValue() < a_card2.getValue());
}

//Not used
bool Run::compareSuits(Card a_card, Suit a_suit)
{
	return (a_card.getSuit() == a_suit);
}


bool Run::isRun(std::vector<Card> a_cards)
{
	//Need at least three cards for a run
	if (a_cards.size() < 3) {
		return false;
	}

	Suit suit = a_cards[0].getSuit();
	//If all the suits don't match then it's false
	if (!(all_of(a_cards.begin(), a_cards.end(), [&](Card c) {return c.getSuit() == suit;}))) {
		return false;
	}
	//Sorting based on values
	sort(a_cards.begin(), a_cards.end(), compareValues);

	int compValue = a_cards[0].getValue();

	//If any card does not equal the previous card's value plus 1 then not true
	for (int i = 1; i < a_cards.size(); i++) {
		if (a_cards[i].getValue() != (compValue + 1)) {
			return false;
		}
		compValue = a_cards[i].getValue();
	}

	return true;
}

bool Run::hasRuns(std::vector<Card> a_hand)
{
	//Need at least three cards for a run
	if (a_hand.size() < 3) {
		return false;
	}

	//Sorting based on values
	sort(a_hand.begin(), a_hand.end(), compareValues);

	vector<vector<Card>> possibleRuns;
	vector<Card> run(a_hand.size());

	#pragma region Splitting Cards By Suit
	auto it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Tridents); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Spades); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Clubs); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Diamonds); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Hearts); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);
	#pragma endregion

	for (vector<Card> possibleRun : possibleRuns) {
		sort(possibleRun.begin(), possibleRun.end(), compareValues);
		int count = 0;
		if (possibleRun.size() >= 3) {
			int count = 0;
			int compValue = possibleRun[0].getValue();
			for (Card c : possibleRun) {
				if (c.getValue() == (compValue + 1)) {
					count++;
				}
				else {
					count = 0;
				}
				compValue = c.getValue();
				if (count == 3) {
					return true;
				}
			}
		}
	}

	return false;
}
//Way unfinished
std::vector<Run> Run::returnRuns(std::vector<Card> a_hand)
{
	vector<vector<Card>> possibleRuns;
	//Need at least three cards for a run
	if (a_hand.size() < 3) {
		return vector<Run>();
	}
	//Sorting based on values
	sort(a_hand.begin(), a_hand.end(), compareValues);
	
	vector<Card> run(a_hand.size());

	#pragma region Splitting Cards By Suit
	auto it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Tridents); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Spades); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Clubs); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Diamonds); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);

	run.clear();
	run.resize(a_hand.size());
	it = copy_if(a_hand.begin(), a_hand.end(), run.begin(), [](Card c) {return (c.getSuit() == Hearts); });
	run.resize(distance(run.begin(), it));
	possibleRuns.push_back(run);
	#pragma endregion Splitting Cards By Suit

	for (vector<Card> possibleRun : possibleRuns) {
		sort(possibleRun.begin(), possibleRun.end(), compareValues);
		int count = 0;
		if (possibleRun.size() >= 3) {
			int count = 0;
			int compValue = possibleRun[0].getValue();
			for (Card c : possibleRun) {
				if (c.getValue() == (compValue + 1)) {
					count++;
				}
				else {
					count = 0;
				}
				compValue = c.getValue();
			}
		}
	}
}

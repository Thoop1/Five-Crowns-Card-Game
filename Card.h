#pragma once
#include "pch.h"
#include "Enums.h"

class Card {
private:
	Suit m_suit;
	Rank m_rank;
	std::string m_name;
	int m_value;
	int m_id;


public:
	Card() {}

	/* *********************************************************************
	Function Name: Card
	Purpose: Constructor for Card class
	Parameters: a_suit, a_rank, a_name, a_value
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	Card(Suit a_suit, Rank a_rank, std::string a_name, int a_value) {
		m_suit = a_suit;
		m_rank = a_rank;
		m_name = a_name;
		m_value = a_value;
	}



	#pragma region Mutators
	/* *********************************************************************
	Function Name: getSuit
	Purpose: Returns the suit of this card
	Parameters:
	Return Value: The suit of this card
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	Suit getSuit() {
		return m_suit;
	}

	/* *********************************************************************
	Function Name: setSuit
	Purpose: Set the suit of this card
	Parameters: 
		a_suit
	Return Value:
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	void setSuit(Suit a_suit) {
		m_suit = a_suit;
	}

	/* *********************************************************************
	Function Name: getRank
	Purpose: Return the rank of the card
	Parameters:
	Return Value: The rank of this card
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	Rank getRank() {
		return m_rank;
	}

	/* *********************************************************************
	Function Name: setRank
	Purpose: Set the rank of card
	Parameters:
		a_rank - rank for the card
	Return Value: 
	Local Variables:
	Algorithm:
	Assistance Received: None
	********************************************************************* */
	void setRank(Rank a_rank) {
		m_rank = a_rank;
	}

	/* *********************************************************************
	Function Name: getName
	Purpose: Get the name of the card
	Parameters:
	Return Value: Name of the card
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	std::string getName() {
		return m_name;
	}

	/* *********************************************************************
	Function Name: setName
	Purpose: Set the name of the card
	Parameters:
		a_name - name we name the card
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setName(std::string a_name) {
		m_name = a_name;
	}


	/* *********************************************************************
	Function Name: getValue
	Purpose: Get the value of the card
	Parameters: 
	Return Value: Value of the card
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	int getValue() {
		return m_value;
	}

	/* *********************************************************************
	Function Name: setValue
	Purpose: set the value of the card
	Parameters:
		a_value - value we set
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setValue(int a_value) {
		m_value = a_value;
	}

	/* *********************************************************************
	Function Name: getId
	Purpose: get id of the card
	Parameters:
	Return Value: id of the card
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	int getId() { return m_id; }

	/* *********************************************************************
	Function Name: setId
	Purpose: set id of the card
	Parameters:
		a_id = id of the card
	Return Value:
	Local Variables:
	Algorithm:
	1)
	Assistance Received: None
	********************************************************************* */
	void setId(int a_id) { m_id = a_id; }
	#pragma endregion Mutators
};
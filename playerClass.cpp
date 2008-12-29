#include "playerClass.h"
#include <iostream>

using namespace std;

playerClass::playerClass(string name)
{
    playerName = name;
    skipStatus = false;
}

const string playerClass::getplayerName()
{
    return playerName;
}

const bool playerClass::getStatus()
{
    bool status = skipStatus;
	if(skipStatus = true)
		skipStatus = false;
	return status;
}

void playerClass::displayHand()
{
    list<unoCard>::iterator card = playerHand.begin();

	cout << playerName << "'s Hand:\n";

    while(card != playerHand.end())
    {
        cout << card->getCardNumber() << " " << card->getCardColor() << endl;
        card++;
    }
}

void playerClass::addCard(unoCard newCard)
{
    playerHand.push_front(newCard);
}

bool playerClass::removeCard(unoCard cardToRemove)
{
	list<unoCard>::iterator card = findCard(cardToRemove);
	bool removed = true;

	if(card != playerHand.end())
		playerHand.erase(card);
	else
		removed = false;

	return removed;
}

/*Precondition: List exists
  Postcondidtion: The players hand has been travered. An iterator has been
                  returned. Iterator returned whether card was found or not.
  */
list<unoCard>::iterator playerClass::findCard(unoCard cardToFind)
{
	list<unoCard>::iterator card = playerHand.begin();
	bool found = false;

	do
	{
		if(card->getCardColor() == cardToFind.getCardColor() &&
			card->getCardNumber() == cardToFind.getCardNumber())

			found = true;
		else
			card++;
	}while(card != playerHand.end() && !found);

	return card;
}

int playerClass::getHandSize()
{
	return playerHand.size();
}


/*
void displayHand()                                                         
{                                                                          
    typename playerClass::iterator card = playerHand.begin()               
                                                                           
    while(hand != playerHand.end())                                        
    {                                                                      
        cout << card << endl;                                              
        ++hand;                                                            
    }                                                                      
}                                                                          
                                                                           
bool playerClass::iterator::operator !=(const iterator &iter2) const       
{                                                                          
    return cardPtr != iter2.cardPtr;                                       
}                                                                          
                                                                           
iterator playerClass::iterator::operator ++()                              
{                                                                          
    cardPtr = cardPtr->next;                                               
    return *this;                                                          
}                                                                          
                                                                           
ostream& playerClass::iterator::operator<<(ostream &stream, iterator &card)
{                                                                          
    cout << card.cardColor << " " << card.cardNumber << endl;              
    return stream;                                                         
}                                                                          
                                                                           
iterator playerClass::begin()                                              
{                                                                          
    typename playerClass::iterator iter = head;                            
    return iter;                                                           
}                                                                          
                                                                           
iterator playerClass::end()                                                
{                                                                          
    typename playerClass::iterator iter = 0;                               
    return iter;                                                           
}                                                                          
*/

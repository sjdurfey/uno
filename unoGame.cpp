#include "unoGame.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

unoGame::unoGame(ifstream & inCard, string names[], int numPlayers)
{
    short cNumber;
    string caColor;

    if(inCard)
    {
        while(inCard)
        {
            inCard >> cNumber >> caColor;
            gameDeck.push_back(unoCard(cNumber, caColor));
        }
    }
    else
    {
        cout << "File failed to open, now exiting" << endl;
        exit(1);
    }

    for(int i = 0; i < 10; ++i)
        shuffleDeck(gameDeck);

    
    addPlayers(names, numPlayers);
	cout << "Size: " << gameDeck.size() << endl;
    
}

//This function simply shuffles the deck by using the STL algorithm 
//random_shuffle. It is called 
void unoGame::shuffleDeck(vector<unoCard>& gameDeck)
{
    vector<unoCard>::iterator beginning, end;
    beginning = gameDeck.begin();
    end = gameDeck.end();
    random_shuffle(beginning, end);
}

void unoGame::createCard(short cardNumber, string cardColor, unoCard &playedCard)
{
	playedCard.setCardColor(cardColor);
	playedCard.setCardNumber(cardNumber);
}

void unoGame::displayDeck()
{
    vector<unoCard>::iterator position = gameDeck.begin();

    while(position != gameDeck.end())
    {
        cout << position->getCardColor() << " " << position->getCardNumber() << endl;
        position++;
    }
}
//the default value of 5 is used here to disseminate between a function call
//from the main program to add a card to the discard from a players hand, and
//adding a card to the discard when the game object is initialized. this initial
//card will act as the first "upcard".
bool unoGame::addToDiscard(unoCard discard, short playerNum = 5)
{
	if(playerNum != 5)
	{
		if(players[playerNum].removeCard(discard))
		{
			discardPile.push_back(discard);
			return true;
		}
		else
			return false;
	}
	else
	{
		discardPile.push_back(gameDeck.pop_back());
	}
}

bool unoGame::isThereAWinner(short playerNumber)
{
	return players[playerNumber].getHandSize() == 0;
}

bool unoGame::wasReverseCardUsed(unoCard playedCard)
{
	return playedCard.getCardNumber() == REVERSE;
}

const bool unoGame::shouldPlayerBeSkipped(short playerNum)
{
	return players[playerNum].getStatus();
}

void unoGame::displayPlayerHand(short playerNumber)
{
	players[playerNumber].displayHand();
}

void unoGame::removeCardFromDeckAddToPlayer(short playerNum)
{
	if(!gameDeck.empty())
	{
		vector<unoCard>::iterator removeCard = gameDeck.begin();
		unoCard addCard = gameDeck.front();
		gameDeck.erase(removeCard);
		players[playerNum].addCard(addCard);
	}
	else
	{
		if(discardPile.empty())
		{
			cerr << "No more cards left to play, game over\n";
			exit(1);
		}
		else
		{
			gameDeck = discardPile;
			discardPile.clear();
			for(int i = 0; i < 10; ++i)
				shuffleDeck(gameDeck);
		}
	}
}


void unoGame::addPlayers(string names[], int numPlayers)    
{                                                           
    const short NUM_START_CARDS = 7;                        
                                                            
    for(int i = 0; i < numPlayers; ++i)                     
    {                                                       
        players.push_back(playerClass(names[i]));           
    }                                                       
                                                            
    for(int j = 0; j < NUM_START_CARDS; ++j)                
    {                                                       
        for(int i = 0; i < numPlayers; ++i)                 
        {                                                   
            unoCard temp(gameDeck.front());
			vector<unoCard>::iterator removeCard = gameDeck.begin();
            gameDeck.erase(removeCard);                      
            players[i].addCard(temp);
        }                                                   
    }                                                       
}    




#ifndef UNO_GAME_H
#define UNO_GAME_H

#include <vector>
#include "cardClass.h"
#include "playerClass.h"


const short SKIP      = 10;
const short DRAW_TWO  = 11;
const short REVERSE   = 12;
const short WILD      = 13;
const short DRAW_FOUR = 14;

//To-Do -- correct the skip player algorithm

class unoGame
{
    private:
        vector<unoCard>     gameDeck;
        vector<unoCard>     discardPile;
        vector<playerClass> players;
        void shuffleDeck(vector<unoCard>& gameDeck);

    public:
        
        unoGame(ifstream & inCard, string names[], int numPlayers);
        bool isDeckEmpty();
		bool addToDiscard(unoCard discard, short playerNum = 5);
		bool isThereAWinner(short playerNumber);
		bool wasReverseCardUsed(unoCard playedCard);
		const bool shouldPlayerBeSkipped(short playerNum);
        void createDeck();
		void createCard(short cardNumber, string cardColor, unoCard &playedCard);
        void displayDeck(); 
		void displayPlayerHand(short playerNumber);
        void addPlayers(string names[], int numPlayers);
		void removeCardFromDeckAddToPlayer(short playerNum);
};

#endif

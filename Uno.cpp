#include <iostream>
#include <fstream>

#include "unoGame.h"


using namespace std;

void buildCardsFile(ofstream &outData);

int main (int argc, char *argv[])
{
    ofstream  outData("unoCard.txt");
    ifstream  inData;
    string    playerNames[4] = {"","","",""};
    const int MAX_PLAYERS = 4;
	const int MIN_PLAYERS = 2;
    int       numberOfPlayers;
	short     cardNumber;
	string    cardColor;
	bool      forward = true;   //controls direction of the game. only changes to false if a reverse card is used.
	bool	  winner = false;
	bool      playedCardFound = true;
	bool      drawnCard;
	short     playerTurn = 0;
	unoCard   playedCard;
	char      playAnswer;

    buildCardsFile(outData);
	outData.close();
    inData.open("unoCard.txt");

    cout << "Welcome to Uno!\n\n";

    do
    {
        cout << "How many players do you wish to play with (max of 4, min of 2)? ";
        cin >> numberOfPlayers;
    }while(numberOfPlayers > MAX_PLAYERS || numberOfPlayers < MIN_PLAYERS);

    for(int index = 0; index < numberOfPlayers; index++)
    {
        cout << "Enter the name of Player " << index + 1 << ":  ";
        cin >> playerNames[index];
        cout << endl;
    }

    unoGame gameBoard(inData, playerNames, numberOfPlayers);

	do
	{
		do
		{
			playedCardFound = true;
			gameBoard.displayPlayerHand(playerTurn);
			cout << "Press D to draw card or P to play card: ";
			cin  >> playAnswer; 

			if(playAnswer == 'P' || playAnswer == 'p')
			{
				cout << "Select a card to discard (num then color): ";
				cin  >> cardNumber >> cardColor;
				gameBoard.createCard(cardNumber, cardColor, playedCard);
				playedCardFound = gameBoard.addToDiscard(playedCard, playerTurn);
				if(playedCardFound == false)
				{
					cout << "Card was not found in your hand, try again\n";
				}
				else
				{
					if(gameBoard.shouldPlayerBeSkipped(playerTurn))
						playerTurn++;
				}
			}
			else if(playAnswer == 'D' || playAnswer == 'd')
			{
				gameBoard.removeCardFromDeckAddToPlayer(playerTurn);
				drawnCard = true;
			}
		
			
		}while(!playedCardFound || !drawnCard);

		forward = gameBoard.wasReverseCardUsed(playedCard);
		winner = gameBoard.isThereAWinner(playerTurn);

		if(!winner && forward)
		{
			if(gameBoard.shouldPlayerBeSkipped(playerTurn))
			{
				if((numberOfPlayers - playerTurn) == 1)
					playerTurn = 0;
				else
					playerTurn = ((playerTurn + 1) % numberOfPlayers) + 1;
			}
			else
				playerTurn = (playerTurn + 1) % numberOfPlayers;
		}
		else if(!winner && !forward)
		{
			if(playerTurn == 0)
				playerTurn = (numberOfPlayers - 1);
			else
				playerTurn--;
		}

	}while(!winner);

	
	gameBoard.displayPlayerHand(0);

    //gameBoard.displayDeck();

    
    return(0);
}

/* this function takes in a file descriptor, and creates the list
   of cards that are to be used for this game. Cards 0-9 are normal
   cards, while cards 10-12 are designated as wild cards.
   Cards 13 & 14 are the special wild cards, 'Wild' and 'Draw Four'*/
void buildCardsFile(ofstream &outData)
{
    for(int k = 0; k < 2; ++k) //create two copies of each card
    {
        for(int i = 0; i < 4; ++i) //4 colors 
        {
            string color;
            switch (i)
            {
            case 0: color = "Red";
                break;
            case 1: color = "Blue";
                break;
            case 2: color = "Yellow";
                break;
            case 3: color = "Green";
                break;
            }
            for(int j = 0; j < 13; ++j) //cards 10-12 are wild cards
            {
                if(k == 0 || (k == 1 && j != 0)) //only one zero allowed per color
                {
                    outData << j << " " << color << " ";
                }
            }
            if(k < 1) //only 4 of each Wild card
            {
                for(int index = 13; index < 15; index++)
                {
                    outData << index << " Wild ";
                }
            }
        }
    }
}


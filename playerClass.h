#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include <list>
#include <string>
#include "cardClass.h"

using namespace std;

class playerClass
{
    private:
        string playerName;
        list<unoCard> playerHand;
        bool skipStatus;
        
    public:
        playerClass(string);
        const string getplayerName();
        const bool getStatus();
        void setStatus(bool status);
        void displayHand();
        void addCard(unoCard); 
		list<unoCard>::iterator findCard(unoCard cardToFind);
		bool removeCard(unoCard cardToRemove);
		int  getHandSize();
        
/*
        class iterator                                                      
        {                                                                   
            public:                                                         
                unoCard* cardPtr;                                           
                iterator operator++();                                      
                bool operator!=(const iterator &iter2) const;               
                friend ostream &operator<<(ostream &stream, iterator &card);
                                                                            
        };                                                                  
                                                                            
        iterator begin();                                                   
        iterator end();                                                     
*/
};

#endif

#ifndef CARD_CLASS_H
#define CARD_CLASS_H
#include <string>

using namespace std;

class unoCard
{
    private:
        short cardNumber;
        string cardColor;
        unoCard* next;

    public:
        short getCardNumber(); 
        string getCardColor(); 
		void setCardNumber(short cNum);
		void setCardColor(string cColor);
        unoCard(short cNum, string cColor); 
		unoCard() {}
};

#endif

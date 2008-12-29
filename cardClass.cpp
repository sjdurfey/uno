#include "cardClass.h"

using namespace std;

unoCard::unoCard(short cNum, string cColor)
{
    cardNumber = cNum;
    cardColor = cColor;
    next = NULL;
}

short unoCard::getCardNumber() 
{
    return cardNumber;
}

string unoCard::getCardColor() 
{
    return cardColor;
}

void unoCard::setCardColor(string cColor)
{
	cardColor = cColor;
}

void unoCard::setCardNumber(short cNum)
{
	cardNumber = cNum;
}

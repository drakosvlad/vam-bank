#include "ICard.h"

ICard::~ICard()
{

}

void ICard::changePin(const std::array<unsigned char, 4> & pass)
{
    do_changePin(pass);
}
const std::array<unsigned char, 4> & ICard::pin() const
{
    return do_pin();
}
bool ICard::verifyPin(const std::array<unsigned char, 4> & pin) const
{
    return do_verifyPin(pin);
}
const std::array<unsigned char, 7> ICard::getCardId() const
{
    return do_getCardId();
}
const IAccount* ICard::getAccount() const
{
    return do_getAccount();
}
const DueDate ICard::getDueDate() const
{
    return do_getDueDate();
}

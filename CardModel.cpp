#include "CardModel.h"

CardModel::CardModel(
        const std::array<unsigned char, 16>& cardNumber,
        const std::array<unsigned char, 7>& cardId,
        const std::array<unsigned char, 4>& pin,
        const DueDate& dueDate,
        const IAccount& bindedAccount
    ) :
    _cardNumber(cardNumber),
    _cardId(cardId),
    _pin(pin),
    _dueDate(dueDate),
    _boundAccount(bindedAccount)
{

}

CardModel::~CardModel()
{

}

void CardModel::changePin(const std::array<unsigned char, 4> &pin)
{
    _pin = pin;
}

bool CardModel::verifyPin(const std::array<unsigned char, 4> &pin) const
{
    return _pin == pin;
}

const std::array<unsigned char, 16> CardModel::getCardNumber() const
{
    return _cardNumber;
}

const std::array<unsigned char,7> CardModel::getCardId() const
{
    return _cardId;
}

const IAccount* CardModel::getAccount() const
{
    return &_boundAccount;
}

const DueDate CardModel::getDueDate() const
{
    return _dueDate;
}

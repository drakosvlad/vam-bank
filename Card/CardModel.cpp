#include "CardModel.h"

CardModel::CardModel(
        const std::array<unsigned char, 7>& cardId,
        const std::array<unsigned char, 4>& pin,
        const DueDate& dueDate,
        const IAccount& bindedAccount
    ) :
    _cardId(cardId),
    _pin(pin),
    _dueDate(dueDate),
    _boundAccount(bindedAccount)
{

}

CardModel::~CardModel()
{

}

void CardModel::do_changePin(const std::array<unsigned char, 4> &pin)
{
    _pin = pin;
}

bool CardModel::do_verifyPin(const std::array<unsigned char, 4> &pin) const
{
    return _pin == pin;
}

const std::array<unsigned char,7> CardModel::do_getCardId() const
{
    return _cardId;
}

const IAccount* CardModel::do_getAccount() const
{
    return &_boundAccount;
}

const DueDate CardModel::do_getDueDate() const
{
    return _dueDate;
}

const std::array<unsigned char, 4> & CardModel::do_pin() const
{
    return _pin;
}

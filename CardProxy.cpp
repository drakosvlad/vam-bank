#include "CardProxy.h"

void CardProxy::changePin(const std::array<unsigned char, 4> &pin)
{
    // TODO db update
    _model.changePin(pin);
}

bool CardProxy::verifyPin(const std::array<unsigned char, 4> &pin) const
{
    return _model.verifyPin(pin);
}

const std::array<unsigned char, 7> CardProxy::getCardId() const
{
    return _model.getCardId();
}

const IAccount* CardProxy::getAccount() const
{
    return _model.getAccount();
}

const DueDate CardProxy::getDueDate() const
{
    return _model.getDueDate();
}


#include "CardProxy.h"
#include "Storage.h"

void CardProxy::changePin(const std::array<unsigned char, 4> &pin)
{
    _model.changePin(pin);
    Storage::getInstance().commitCard(&_model);
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

const std::array<unsigned char, 4> & CardProxy::pin() const
{
    return _model.pin();
}

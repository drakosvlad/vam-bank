#include "CardProxy.h"
#include <Database/Storage.h>
#include <Account/AccountProxy.h>

void CardProxy::do_changePin(const std::array<unsigned char, 4> &pin)
{
    _model.changePin(pin);
    Storage::getInstance().commitCard(&_model);
}

bool CardProxy::do_verifyPin(const std::array<unsigned char, 4> &pin) const
{
    return _model.verifyPin(pin);
}

const std::array<unsigned char, 7> CardProxy::do_getCardId() const
{
    return _model.getCardId();
}

const IAccount* CardProxy::do_getAccount() const
{
    return new AccountProxy(const_cast<IAccount*>(_model.getAccount()));
}

const DueDate CardProxy::do_getDueDate() const
{
    return _model.getDueDate();
}

const std::array<unsigned char, 4> & CardProxy::do_pin() const
{
    return _model.pin();
}

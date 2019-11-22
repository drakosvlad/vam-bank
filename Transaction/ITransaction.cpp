#include "ITransaction.h"

ITransaction::~ITransaction()
{

}

const IAccount& ITransaction::getSender() const
{
    return do_getSender();
}
const IAccount& ITransaction::getReciever() const
{
    return do_getReciever();
}
const QDateTime ITransaction::getTimeSent() const
{
    return do_getTimeSent();
}
const QDateTime ITransaction::getTimeRecieved() const
{
    return do_getTimeRecieved();
}
int ITransaction::getAmount() const
{
    return do_getAmount();
}
bool ITransaction::getSuccess() const
{
    return do_getSuccess();
}
size_t ITransaction::getId() const
{
    return do_getId();
}

#include "TransactionModel.h"

TransactionModel::TransactionModel(const IAccount &from,
                                   const IAccount &to,
                                   const int amount,
                                   const bool success,
                                   const QDateTime& timeSent,
                                   const QDateTime& timeReceived)
    : _from(from),
      _to(to),
      _amount(amount),
      _success(success),
      _timeSent(timeSent),
      _timeReceived(timeReceived)
{

}

TransactionModel::~TransactionModel()
{

}

TransactionModel::TransactionModel(const TransactionModel& m)
    : _from(m._from),
      _to(m._to),
      _amount(m._amount),
      _success(m._success),
      _timeSent(m._timeSent),
      _timeReceived(m._timeReceived)
{

}

const IAccount& TransactionModel::getSender() const
{
    return _from;
}

const IAccount& TransactionModel::getReciever() const
{
    return _to;
}

const QDateTime TransactionModel::getTimeSent() const
{
    return _timeSent;
}

const QDateTime TransactionModel::getTimeRecieved() const
{
    return _timeReceived;
}

int TransactionModel::getAmount() const
{
    return _amount;
}

bool TransactionModel::getSuccess() const
{
    return _success;
}

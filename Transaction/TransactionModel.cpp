#include "TransactionModel.h"

TransactionModel::TransactionModel(const size_t id,
                                   const IAccount &from,
                                   const IAccount &to,
                                   const int amount,
                                   const bool success,
                                   const QDateTime& timeSent,
                                   const QDateTime& timeReceived)
    : _id(id),
      _from(from),
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
    : _id(m._id),
      _from(m._from),
      _to(m._to),
      _amount(m._amount),
      _success(m._success),
      _timeSent(m._timeSent),
      _timeReceived(m._timeReceived)
{

}

const IAccount& TransactionModel::do_getSender() const
{
    return _from;
}

const IAccount& TransactionModel::do_getReciever() const
{
    return _to;
}

const QDateTime TransactionModel::do_getTimeSent() const
{
    return _timeSent;
}

const QDateTime TransactionModel::do_getTimeRecieved() const
{
    return _timeReceived;
}

int TransactionModel::do_getAmount() const
{
    return _amount;
}

bool TransactionModel::do_getSuccess() const
{
    return _success;
}

size_t TransactionModel::do_getId() const
{
    return _id;
}

#pragma once

#include <QDateTime>

#include "ITransaction.h"
#include <Account/IAccount.h>

/**
 * @brief Represents a finished transaction between two accounts
 *
 * Transaction is an immutable entity, therefore we allow
 * its copying and deny the assignment
 */
class TransactionModel final: public ITransaction
{
private:
    const size_t _id;
    const IAccount& _from;
    const IAccount& _to;
    const int _amount;
    const bool _success;
    const QDateTime _timeSent;
    const QDateTime _timeReceived;

    const IAccount& do_getSender() const override;
    const IAccount& do_getReciever() const override;
    const QDateTime do_getTimeSent() const override;
    const QDateTime do_getTimeRecieved() const override;
    int do_getAmount() const override;
    bool do_getSuccess() const override;
    size_t do_getId() const override;
public:
    TransactionModel(const size_t id,
                     const IAccount &from,
                     const IAccount &to,
                     const int amount,
                     const bool success,
                     const QDateTime& timeSent,
                     const QDateTime& timeReceived);
    ~TransactionModel() override;
    TransactionModel(const TransactionModel &);
    TransactionModel& operator=(const TransactionModel &) = delete;

};

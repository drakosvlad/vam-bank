#pragma once

#include "ITransaction.h"
#include "IAccount.h"

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
    const IAccount& getSender() const override;
    const IAccount& getReciever() const override;
    const QDateTime getTimeSent() const override;
    const QDateTime getTimeRecieved() const override;
    int getAmount() const override;
    bool getSuccess() const override;
    size_t getId() const override;
};

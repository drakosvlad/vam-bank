#pragma once
#include "ITransaction.h"

/**
 * @brief Class representing Transaction model
 */
class Transaction : public ITransaction
{
private:
    IAccount* _reciever, *_sender;
    time_t _timeRecieved, _timeSent;
    int _amount;

public:
    Transaction(
            const IAccount* _reciever,
            const IAccount*_sender,
            const time_t _timeRecieved,
            const time_t _timeSent,int
        );
    ~Transaction() override;

    const IAccount* getSender() const override;
    const IAccount* getReciever() const override;
    time_t getTimeSent() const override;
    time_t getTimeRecieved() const override;
    int getAmount() const override;
};

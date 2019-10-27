#pragma once
#include "ITransaction.h"

class Transaction : public ITransaction
{
private:
    IAccount* _reciever, *_sender;
    time_t _timeRecieved, _timeSent;
    int _amount;
public:
    Transaction(const IAccount* _reciever, const IAccount*_sender, const time_t _timeRecieved, const time_t _timeSent,int);
    ~Transaction();
        const IAccount* getSender() const;
        const IAccount* getReciever() const;
        time_t getTimeSent() const;
        time_t getTimeRecieved() const;
        int getAmount() const;
};

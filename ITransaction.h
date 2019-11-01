#pragma once
#include <ctime>
#include "IAccount.h"

/**
 * @brief Bank transaction interface
 */
class ITransaction
{
public:
    virtual ~ITransaction()=0;
    virtual const IAccount* getSender() const = 0;
    virtual const IAccount* getReciever() const = 0;
    virtual time_t getTimeSent() const = 0;
    virtual time_t getTimeRecieved() const = 0;
    virtual int getAmount() const = 0;
};

#pragma once

#include <QDateTime>
#include "IAccount.h"

/**
 * @brief Bank transaction interface
 */
class ITransaction
{
public:
    virtual ~ITransaction() = 0;
    virtual const IAccount& getSender() const = 0;
    virtual const IAccount& getReciever() const = 0;
    virtual const QDateTime getTimeSent() const = 0;
    virtual const QDateTime getTimeRecieved() const = 0;
    virtual int getAmount() const = 0;
    virtual bool getSuccess() const = 0;
};

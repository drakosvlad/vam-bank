#pragma once

#include <QDateTime>

class IAccount;

/**
 * @brief Bank transaction interface
 */
class ITransaction
{
private:
    virtual const IAccount& do_getSender() const = 0;
    virtual const IAccount& do_getReciever() const = 0;
    virtual const QDateTime do_getTimeSent() const = 0;
    virtual const QDateTime do_getTimeRecieved() const = 0;
    virtual int do_getAmount() const = 0;
    virtual bool do_getSuccess() const = 0;
    virtual size_t do_getId() const = 0;
public:
    virtual ~ITransaction();
    const IAccount& getSender() const;
    const IAccount& getReciever() const;
    const QDateTime getTimeSent() const;
    const QDateTime getTimeRecieved() const;
    int getAmount() const;
    bool getSuccess() const;
    size_t getId() const;
};

#pragma once
#include <array>
#include <ostream>
#include <vector>
#include <QDebug>
class IUser;
class ICard;
class ITransaction;

/**
 * @brief Interface for bank account
 */
class IAccount
{
public:
    virtual ~IAccount();
    /**
     * Adds the amount of received money to the account, including the fee
     */
    virtual void acceptTransfer(const int amount) = 0;
    virtual void transfer(IAccount& acc, const int amount) = 0;
    virtual int balance() const = 0;
    virtual size_t id() const = 0;
    virtual bool isPaymentAccount() const = 0;
    virtual short accountType() const =0;
    virtual void addCard(ICard* card) = 0;
    virtual const IUser* getBoundUser() const =0;
    virtual const QString getAccountName() const = 0;
    virtual ICard* getCard(const std::array<unsigned char, 7> & id) = 0;
    virtual const ICard* getCard(const std::array<unsigned char, 7> & id) const = 0;
    virtual void removeCard(const std::array<unsigned char, 7> & cardNum) = 0;
    virtual const std::vector<ICard*> cards() const = 0;
    virtual const std::vector<const ITransaction*> transactions() const = 0;
    virtual void addTransaction(const ITransaction *) = 0;
    virtual const ITransaction* getTransaction(const size_t id) const = 0;
};

std::ostream& operator<<(std::ostream& out, const IAccount& account);

/**
 * Class for handling Transfer errors
 */
class TransferError
{
private:
    const char * _message;
public:
    TransferError(const char * message) : _message(message) {  }
    TransferError(const TransferError & err) : _message(err._message) {  }
    TransferError& operator=(const TransferError & err)
    {
        this->_message = err.message();
        return *this;
    }

    const char * message() const { return _message; }
};

std::ostream& operator<<(std::ostream& out, const TransferError& error);

QDebug operator<<(QDebug debug, const TransferError& error);

Q_DECLARE_METATYPE(IAccount*);
Q_DECLARE_METATYPE(size_t);

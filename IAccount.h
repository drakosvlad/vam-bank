#pragma once
#include <array>
#include <ostream>
#include <vector>
#include <QDebug>

class ICard;
class ITransaction;

/**
 * @brief Interface for bank account
 */
class IAccount
{
protected:
    /**
   * Adds the amount of received money to the account, including the fee
   */
    virtual void acceptTransfer(int amount) = 0;
public:
    virtual ~IAccount() = 0;
    virtual void transfer(IAccount& acc, int amount) = 0;
    virtual int balance() const = 0;
    virtual size_t id() const = 0;
    virtual bool isPaymentAccount() const = 0;
    virtual void addCard(ICard & card) = 0;
    virtual ICard* getCard(const std::array<unsigned char, 16> & cardNum) const = 0;
    virtual void removeCard(const std::array<unsigned char, 16> & cardNum) = 0;
    virtual const std::vector<ICard*>& cards() = 0;
    virtual const std::vector<const ITransaction*>& transactions() const = 0;
};

template <typename Policy>
std::ostream& operator<<(std::ostream& out, const IAccount& account)
{
    out << "Account #" << account.id() << " with the balance of UAH" << account.balance();
    return out;
}

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

std::ostream& operator<<(std::ostream& out, const TransferError& error)
{
    out << "TRANSFER ERROR: " << error.message() << std::endl;
    return out;
}

QDebug operator<<(QDebug debug, const TransferError& error)
{
    debug << error.message();
    return debug;
}


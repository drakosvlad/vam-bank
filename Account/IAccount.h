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
private:
    virtual void do_acceptTransfer(const int amount) = 0;
    virtual void do_transfer(IAccount& acc, const int amount) = 0;
    virtual int do_balance() const = 0;
    virtual size_t do_id() const = 0;
    virtual bool do_isPaymentAccount() const = 0;
    virtual short do_accountType() const =0;
    virtual void do_addCard(ICard* card) = 0;
    virtual const IUser* do_getBoundUser() const =0;
    virtual const QString do_getAccountName() const = 0;
    virtual ICard* do_getCard(const std::array<unsigned char, 7> & id) = 0;
    virtual const ICard* do_getCard(const std::array<unsigned char, 7> & id) const = 0;
    virtual void do_removeCard(const std::array<unsigned char, 7> & cardNum) = 0;
    virtual const std::vector<ICard*> do_cards() const = 0;
    virtual const std::vector<const ITransaction*> do_transactions() const = 0;
    virtual void do_addTransaction(const ITransaction *) = 0;
    virtual const ITransaction* do_getTransaction(const size_t id) const = 0;
    virtual const QDate do_creationDate() const = 0;
    virtual const QDate do_payrollDate() const = 0;
    virtual int do_creditLimit() const = 0;

    virtual int do_payroll() = 0;
public:
    virtual ~IAccount();
    /**
     * Adds the amount of received money to the account, including the fee
    */
    void acceptTransfer(const int amount);
    void transfer(IAccount& acc, const int amount);
    int balance() const;
    size_t id() const;
    bool isPaymentAccount() const;
    short accountType() const;
    void addCard(ICard* card);
    const IUser* getBoundUser() const;
    const QString getAccountName() const;
    ICard* getCard(const std::array<unsigned char, 7> & id);
    const ICard* getCard(const std::array<unsigned char, 7> & id) const;
    void removeCard(const std::array<unsigned char, 7> & cardNum);
    const std::vector<ICard*> cards() const;
    const std::vector<const ITransaction*> transactions() const;
    void addTransaction(const ITransaction *);
    const ITransaction* getTransaction(const size_t id) const;
    const QDate creationDate() const;
    const QDate payrollDate() const;
    int creditLimit() const;
    int payroll();
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

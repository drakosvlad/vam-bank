#pragma once

#include <vector>
#include <ostream>
#include <QString>
#include <QDate>

#include "IAccount.h"
#include <Card/ICard.h>
#include <Transaction/ITransaction.h>

/**
 * Class representing bank account
 */
template <typename Policy>
class AccountModel final: public IAccount
{
private:
    const IUser& _owner;
    int _balance = 0;
    size_t _id;
    QDate _creationDate;
    QDate _payrollDate;
    int _creditLimit;
    std::vector<ICard*> _cards;
    std::vector<const ITransaction*> _transactions;
    void do_transfer(IAccount& acc, const int amount) override;
    void do_acceptTransfer(const int amount) override;
    int do_balance() const override { return this->_balance; }
    size_t do_id() const override { return this->_id; }
    const QString do_getAccountName() const override;
    bool do_isPaymentAccount() const override { return Policy::_isPaymentAccount; }
    short do_accountType() const override {return Policy::_accountType;}
    void do_addCard(ICard* card) override;

    ICard* do_getCard(const std::array<unsigned char, 7> & id) override;
    const ICard* do_getCard(const std::array<unsigned char, 7> & id) const override;
    const IUser* do_getBoundUser() const override {return &_owner;}
    void do_removeCard(const std::array<unsigned char, 7> & cardNum) override;
    const std::vector<ICard*> do_cards() const override;
    const std::vector<const ITransaction*> do_transactions() const override;
    void do_addTransaction(const ITransaction *) override;
    const ITransaction* do_getTransaction(const size_t id) const override;
    const QDate do_creationDate() const override;
    const QDate do_payrollDate() const override;
    int do_creditLimit() const override;

    int do_payroll() override;
public:
    AccountModel(const IUser* owner, const int balance, const QDate& creationDate, const QDate& payrollDate, int creditLimit, size_t id);
    ~AccountModel(){  }
    AccountModel(const AccountModel & am) = delete;
    AccountModel& operator=(const AccountModel & am) = delete;
};

template <typename Policy>
AccountModel<Policy>::AccountModel(const IUser* owner, int balance, const QDate& creationDate, const QDate& payrollDate, int creditLimit, size_t id)
    : _owner(*owner),_balance(balance), _id(id), _creationDate(creationDate), _payrollDate(payrollDate), _creditLimit(creditLimit)  {  }

template <typename Policy>
void AccountModel<Policy>::do_acceptTransfer(const int amount)
{
    int actualAmount = amount - Policy::acceptFee(amount);
    this->_balance += actualAmount;
}

template <typename Policy>
void AccountModel<Policy>::do_transfer(IAccount& acc, const int amount)
{
    if (amount <= 0)
        throw TransferError("Invalid transfer amount");

    if (this->_id == acc.id()) // Transaction to the account itself is automatically accepted with no fees
        return;

    int actualAmount = amount + (acc.isPaymentAccount() ?
                Policy::paymentFee(amount) :
                Policy::transferFee(amount));

    if (actualAmount > this->_balance)
        throw TransferError("Dayte denyak");

    this->_balance -= actualAmount;
    acc.acceptTransfer(amount);
}

template <typename Policy>
void AccountModel<Policy>::do_addCard(ICard* card)
{
    this->_cards.push_back(card);
}

template <typename Policy>
const QString AccountModel<Policy>::do_getAccountName() const
{
    QString tpl = QString("%1 (%2)").arg(QString::number(_id));
    switch (accountType()) {
    case 0:
        return tpl.arg("Debit");
    case 1:
        return tpl.arg("Credit");
    case 2:
        return tpl.arg("Saving");
    case 3:
        return tpl.arg("Payment");
    case 4:
        return tpl.arg("Maintenance");
    default:
        return tpl.arg("Account");
    }
}

template <typename Policy>
ICard* AccountModel<Policy>::do_getCard(const std::array<unsigned char, 7> & id)
{
    for (std::vector<ICard*>::iterator itor = _cards.begin(); itor != _cards.end(); ++itor)
    {
        if ((*itor)->getCardId() == id)
            return *itor;
    }
    return nullptr;
}

template <typename Policy>
const ICard* AccountModel<Policy>::do_getCard(const std::array<unsigned char, 7> & id) const
{
    return const_cast<AccountModel<Policy>*>(this)->getCard(id);
}

template <typename Policy>
void AccountModel<Policy>::do_removeCard(const std::array<unsigned char, 7> & cardNum)
{
    for (std::vector<ICard*>::iterator itor = _cards.begin(); itor != _cards.end(); ++itor)
    {
        if ((*itor)->getCardId() == cardNum)
        {
            _cards.erase(itor);
            return;
        }
    }
}

template <typename Policy>
const std::vector<ICard*> AccountModel<Policy>::do_cards() const
{
    return _cards;
}

template <typename Policy>
const std::vector<const ITransaction*> AccountModel<Policy>::do_transactions() const
{
    return _transactions;
}

template <typename Policy>
const ITransaction* AccountModel<Policy>::do_getTransaction(const size_t id) const
{
    for (std::vector<const ITransaction*>::const_iterator itor = _transactions.begin(); itor != _transactions.end(); ++itor)
    {
        if ((*itor)->getId() == id)
        {
            return *itor;
        }
    }

    return nullptr;
}

template <typename Policy>
void AccountModel<Policy>::do_addTransaction(const ITransaction *tr)
{
    _transactions.push_back(tr);
}

template <typename Policy>
const QDate AccountModel<Policy>::do_creationDate() const
{
    return _creationDate;
}

template <typename Policy>
const QDate AccountModel<Policy>::do_payrollDate() const
{
    return _payrollDate;
}

template <typename Policy>
int AccountModel<Policy>::do_creditLimit() const
{
    return _creditLimit;
}

template <typename Policy>
int AccountModel<Policy>::do_payroll()
{
    return 0;
}

#pragma once
#include <vector>
#include <ostream>
#include "IAccount.h"
#include "IUser.h"
#include "ICard.h"
#include "ITransaction.h"

/**
 * Class representing bank account
 */
template <typename Policy>
class AccountModel : public IAccount 
{
private:
    const IUser& _owner;
    int _balance = 0;
    size_t _id;
    std::vector<ICard*> _cards;
    std::vector<const ITransaction*> _transactions;

public:
    AccountModel(const IUser* owner, const int balance, size_t id);
    ~AccountModel(){  }
    AccountModel(const AccountModel & am) = delete;
    AccountModel& operator=(const AccountModel & am) = delete;

    void transfer(IAccount& acc, const int amount) override;
    void acceptTransfer(const int amount) override;
    int balance() const override { return this->_balance; }
    size_t id() const override { return this->_id; }
    bool isPaymentAccount() const override { return Policy::_isPaymentAccount; }
    short accountType() const override {return Policy::_accountType;}
    void addCard(ICard* card) override;

    ICard* getCard(const std::array<unsigned char, 7> & id) override;
    const ICard* getCard(const std::array<unsigned char, 7> & id) const override;
    const IUser* getBoundUser() const override {return &_owner;}
    void removeCard(const std::array<unsigned char, 7> & cardNum) override;
    const std::vector<ICard*> cards() const override;
    const std::vector<const ITransaction*> transactions() const override;
    void addTransaction(const ITransaction *) override;
    const ITransaction* getTransaction(const size_t id) const override;
};

template <typename Policy>
AccountModel<Policy>::AccountModel(const IUser* owner, int balance, size_t id)
    : _owner(*owner), _balance(balance), _id(id) {  }

template <typename Policy>
void AccountModel<Policy>::acceptTransfer(const int amount)
{
    int actualAmount = amount - Policy::acceptFee(amount);
    this->_balance += actualAmount;
}

template <typename Policy>
void AccountModel<Policy>::transfer(IAccount& acc, const int amount)
{
    if (amount <= 0)
        throw TransferError("Invalid transfer amount");

    int actualAmount = amount + (acc.isPaymentAccount() ?
                Policy::transferFee(amount) :
                Policy::paymentFee(amount));

    if (actualAmount > this->_balance)
        throw TransferError("Dayte denyak");

    this->_balance -= actualAmount;
    acc.acceptTransfer(amount);
}

template <typename Policy>
void AccountModel<Policy>::addCard(ICard* card)
{
    this->_cards.push_back(card);
}

template <typename Policy>
ICard* AccountModel<Policy>::getCard(const std::array<unsigned char, 7> & id)
{
    for (std::vector<ICard*>::iterator itor = _cards.begin(); itor != _cards.end(); ++itor)
    {
        if ((*itor)->getCardId() == id)
            return *itor;
    }
    return nullptr;
}

template <typename Policy>
const ICard* AccountModel<Policy>::getCard(const std::array<unsigned char, 7> & id) const
{
    return const_cast<AccountModel<Policy>*>(this)->getCard(id);
}

template <typename Policy>
void AccountModel<Policy>::removeCard(const std::array<unsigned char, 7> & cardNum)
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
const std::vector<ICard*> AccountModel<Policy>::cards() const
{
    return _cards;
}

template <typename Policy>
const std::vector<const ITransaction*> AccountModel<Policy>::transactions() const
{
    return _transactions;
}

template <typename Policy>
const ITransaction* AccountModel<Policy>::getTransaction(const size_t id) const
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
void AccountModel<Policy>::addTransaction(const ITransaction *tr)
{
    _transactions.push_back(tr);
}

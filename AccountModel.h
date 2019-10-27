#pragma once
#include <vector>
#include <ostream>
#include "IAccount.h"

/**
 * Class representing bank account
 */
template <typename Policy>
class AccountModel : public IAccount 
{
private:
    int _balance = 0;
    size_t _id;
    std::vector<ICard*> _cards;

protected:
    void acceptTransfer(int amount) override;

public:
    class TransferError;

    AccountModel(int balance, size_t id);
    ~AccountModel(){  }
    AccountModel(const AccountModel & am);
    AccountModel& operator=(const AccountModel & am);

    void transfer(IAccount& acc, int amount) override;
    int balance() const override { return this->_balance; }
    size_t id() const override { return this->_id; }
    bool isPaymentAccount() const override { return Policy::_isPaymentAccount; }
    void addCard(ICard & card) override;
    ICard* getCard(const std::array<unsigned char, 16> & cardNum) const override;
    void removeCard(const std::array<unsigned char, 16> & cardNum) override;
    const std::vector<ICard*>& cards() override;
    const std::vector<const ITransaction*>& transactions() const override;
};

template <typename Policy>
AccountModel<Policy>::AccountModel(int balance, size_t id)
    : _balance(balance), _id(id) {  }

template <typename Policy>
AccountModel<Policy>::AccountModel(const AccountModel<Policy> & am) 
    : _balance(am.balance()), _id(am.id()) {  }

template <typename Policy>
AccountModel<Policy>& AccountModel<Policy>::operator=(const AccountModel & am)
{
    this->_balance = am.balance();
    this->_id = am.id();
}

template <typename Policy>
void AccountModel<Policy>::acceptTransfer(int amount)
{
    int actualAmount = amount - Policy::acceptFee(amount);
    this->_balance += actualAmount;
}

template <typename Policy>
void AccountModel<Policy>::transfer(IAccount& acc, int amount)
{
    if (amount <= 0)
        throw TransferError("Invalid transfer amount");

    int actualAmount = amount + (acc.isPaymentAccount() ?
                Policy::transferFee(amount) :
                Policy::paymentFee(amount));

    if (actualAmount > this->_balance)
        throw TransferError("Dayte denyak");

    this->_balance -= actualAmount;
}

template <typename Policy>
void AccountModel<Policy>::addCard(ICard & card)
{
    this->_cards.push_back(&card);
}

/**
 * Class for handling Transfer errors
 */
template <typename Policy>
class AccountModel<Policy>::TransferError
{
private:
    const char * _message;
public:
    TransferError(const char * message) : _message(message) {  }
    TransferError(const TransferError & err) : _message(err._message) {  }
    TransferError& operator=(const TransferError & err)
    {
        this->_message = err.message();
    }

    const char * message() { return _message; }
};

template <typename Policy>
std::ostream& operator<<(std::ostream & out, const typename AccountModel<Policy>::TransferError error)
{
    out << "TRANSFER ERROR: " << error.message() << std::endl;
}

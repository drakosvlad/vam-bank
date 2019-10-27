#pragma once
#include <iostream>
#include "IAccount.h"

template <typename Policy>
class AccountModel : public IAccount 
{
private:
  int _balance = 0;
  size_t _id;

protected:
  void acceptTransfer(int amount) {
    int actualAmount = amount - Policy::acceptFee(amount);
    this->_balance += actualAmount;
  }

public:
  class TransferError;

  AccountModel(int, size_t);
  ~AccountModel(){  }
  AccountModel(const AccountModel & am);
  AccountModel& operator=(const AccountModel & am);

  void transfer(IAccount& acc, int amount)
  {
    if (amount <= 0)
      throw TransferError("Invalid transfer amount");

    int actualAmount = amount + acc.isPaymentAccount() ?
      Policy::transferFee(amount) :
      Policy::paymentFee(amount);

    if (actualAmount > this->_balance)
      throw TransferError("Dayte denyak");

    this->_balance -= actualAmount;
  }

  int balance() const
  {
    return this->_balance;
  }

  size_t id() const
  {
    return this->_id;
  }

  bool isPaymentAccount() const
  {
    return Policy::_isPaymentAccount;
  }
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

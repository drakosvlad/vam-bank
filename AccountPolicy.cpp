#include "AccountPolicy.h"

AccountPolicy::AccountPolicy(int transferFee, int paymentFee, int acceptFee, bool isPaymentAccount) :
  _transferFee(transferFee), _paymentFee(paymentFee), _acceptFee(acceptFee), _isPaymentAccount(isPaymentAccount)
{  }

AccountPolicy::AccountPolicy(const AccountPolicy & policy) :
  _transferFee(policy._transferFee), _paymentFee(policy._paymentFee),
  _acceptFee(policy._acceptFee), _isPaymentAccount(policy._isPaymentAccount)
{  }

AccountPolicy& AccountPolicy::operator=(const AccountPolicy & policy)
{
  this->_transferFee = policy._transferFee;
  this->_paymentFee = policy._paymentFee;
  this->_acceptFee = policy._acceptFee;
}
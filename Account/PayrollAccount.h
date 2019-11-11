#pragma once

#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<0, 0, 0, false, 4> PayrollAccountPolicy;
typedef AccountModel<PayrollAccountPolicy> PayrollAccount;

template<>
void AccountModel<PayrollAccountPolicy>::transfer(IAccount& acc, const int amount)
{
    acc.acceptTransfer(amount);
}

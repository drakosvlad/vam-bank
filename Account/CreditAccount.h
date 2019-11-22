#pragma once

#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<0, 5, 0, false, 1> CreditAccountPolicy;
typedef AccountModel<CreditAccountPolicy> CreditAccount;

template<>
int AccountModel<CreditAccountPolicy>::do_payroll();

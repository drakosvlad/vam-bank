#pragma once
#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<0, 10, 5, false, 2> SavingsAccountPolicy;
typedef AccountModel<SavingsAccountPolicy> SavingsAccount;

template<>
int AccountModel<SavingsAccountPolicy>::payroll()
{
    _payrollDate = QDate::currentDate();
    return - _balance / 50;
}

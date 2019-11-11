#include "SavingsAccount.h"

template<>
int AccountModel<SavingsAccountPolicy>::payroll()
{
    _payrollDate = QDate::currentDate();
    return - _balance / 50;
}

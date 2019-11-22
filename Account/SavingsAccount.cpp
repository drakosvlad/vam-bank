#include "SavingsAccount.h"

template<>
int AccountModel<SavingsAccountPolicy>::do_payroll()
{
    _payrollDate = QDate::currentDate();
    return - _balance / 50;
}

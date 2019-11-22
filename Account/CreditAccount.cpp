#include "CreditAccount.h"

template<>
int AccountModel<CreditAccountPolicy>::do_payroll()
{
    _payrollDate = QDate::currentDate();
    if (_balance < _creditLimit)
    {
        int fee =  (_creditLimit - _balance) / 33;
        qDebug() << QString("Credit account fee: %1").arg(QString::number(fee));
        return fee;
    }

    return 0;
}

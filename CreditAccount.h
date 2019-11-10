#pragma once
#include "AccountModel.h"
#include "AccountPolicy.h"

typedef AccountPolicy<5, 0, 0, false, 1> CreditAccountPolicy;
typedef AccountModel<CreditAccountPolicy> CreditAccount;

template<>
int AccountModel<CreditAccountPolicy>::payroll()
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

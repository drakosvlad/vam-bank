#include "PayrollAccount.h"

template<>
void AccountModel<PayrollAccountPolicy>::transfer(IAccount& acc, const int amount)
{
    acc.acceptTransfer(amount);
}

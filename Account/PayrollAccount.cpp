#include "PayrollAccount.h"

template<>
void AccountModel<PayrollAccountPolicy>::do_transfer(IAccount& acc, const int amount)
{
    acc.acceptTransfer(amount);
}

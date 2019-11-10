#include "IAccount.h"

IAccount::~IAccount()
{

}

std::ostream& operator<<(std::ostream& out, const IAccount& account)
{
    out << "Account #" << account.id() << " with the balance of UAH" << account.balance();
    return out;
}

std::ostream& operator<<(std::ostream& out, const TransferError& error)
{
    out << "TRANSFER ERROR: " << error.message() << std::endl;
    return out;
}

QDebug operator<<(QDebug debug, const TransferError& error)
{
    debug << error.message();
    return debug;
}

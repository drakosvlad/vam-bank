#include "IAccount.h"
#include <QDate>
IAccount::~IAccount()
{

}
void IAccount::acceptTransfer(const int amount)
{
    do_acceptTransfer(amount);
}
void IAccount::transfer(IAccount& acc, const int amount)
{
    do_transfer(acc,amount);
}
int IAccount::balance() const
{
    return do_balance();
}
size_t IAccount::id() const
{
    return do_id();
}
bool IAccount::isPaymentAccount() const
{
    return do_isPaymentAccount();
}
short IAccount::accountType() const
{
    return do_accountType();
}
void IAccount::addCard(ICard* card)
{
    do_addCard(card);
}
const IUser* IAccount::getBoundUser() const
{
    return do_getBoundUser();
}
const QString IAccount::getAccountName() const
{
    return do_getAccountName();
}
ICard* IAccount::getCard(const std::array<unsigned char, 7> & id)
{
    return do_getCard(id);
}
const ICard* IAccount::getCard(const std::array<unsigned char, 7> & id) const
{
    return do_getCard(id);
}
void IAccount::removeCard(const std::array<unsigned char, 7> & cardNum)
{
    do_removeCard(cardNum);
}
const std::vector<ICard*> IAccount::cards() const
{
    return do_cards();
}
const std::vector<const ITransaction*> IAccount::transactions() const
{
    return do_transactions();
}
void IAccount::addTransaction(const ITransaction * t)
{
    return do_addTransaction(t);
}
const ITransaction* IAccount::getTransaction(const size_t id) const
{
    return do_getTransaction(id);
}
const QDate IAccount::creationDate() const
{
    return do_creationDate();
}
const QDate IAccount::payrollDate() const
{
    return do_payrollDate();
}
int IAccount::creditLimit() const
{
    return do_creditLimit();
}
int IAccount::payroll()
{
    return do_payroll();
}

std::ostream& operator<<(std::ostream& out, const IAccount& account)
{
    out <<account.getAccountName().toStdString()<< "#" << account.id() << " with the balance of UAH" << account.balance();
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

#include "Storage.h"

#include "DatabaseConnect.h"
#include <Account/DebitAccount.h>
#include <Account/PayrollAccount.h>
#include <Card/CardModel.h>
#include <User/UserModel.h>
#include <User/UserProxy.h>

Storage* Storage::_instance = nullptr;

Storage::Storage()
{
}

void Storage::init()
{
    qDebug() << "Database loading";
    std::vector<IUser*> models = DatabaseConnect::getInstance().getUsers();
    UserProxy* admin = new UserProxy(*new UserModel("Admin", "Admin", "admin", "admin"));
    _users.push_back(admin);
    admin->addAccount(new PayrollAccount(admin, 0, QDate::currentDate(), QDate::currentDate(), 0, 0));

    for (IUser* user : models)
    {
        _users.push_back(new UserProxy(*dynamic_cast<UserModel*>(user)));
    }
    for (IUser* user : models)
    {
        std::vector<IAccount*> accounts = DatabaseConnect::getInstance().getUserAccounts(user);
        for (IAccount* account : accounts)
        {
            user->addAccount(account);
        }
    }
    for (IUser* user : models)
    {
        std::vector<IAccount*> accounts = user->accounts();
        for (IAccount* account : accounts)
        {
            std::vector<const ITransaction*> transactions = DatabaseConnect::getInstance().getAccountTransactions(account->id());
            for (const ITransaction* transaction : transactions)
            {
                account->addTransaction(transaction);
            }

            std::vector<ICard*> cards = DatabaseConnect::getInstance().getAccountCards(account);
            for (ICard* card : cards)
            {
                account->addCard(card);
            }
        }
    }
    qDebug() << "Database loaded";
}

Storage& Storage::getInstance()
{
    if (_instance == nullptr)
        _instance = new Storage();

    return *_instance;
}

IUser* Storage::getUser(const std::string login)
{
    for (std::vector<UserProxy*>::iterator itor = _users.begin(); itor != _users.end(); itor++)
    {
        if ((*itor)->getLogin() == login)
            return *itor;
    }

    return nullptr;
}

IAccount* Storage::getAccount(const size_t id)
{
    for (std::vector<UserProxy*>::iterator uItor = _users.begin(); uItor != _users.end(); uItor++)
    {
        auto account = (*uItor)->getAccount(id);
        if (account != nullptr)
            return account;
    }

    return nullptr;
}

ICard* Storage::getCard(const std::array<unsigned char, 7> id)
{
    for (std::vector<UserProxy*>::iterator uItor = _users.begin(); uItor != _users.end(); uItor++)
    {
        std::vector<IAccount*> accounts = (*uItor)->accounts();
        for (std::vector<IAccount*>::iterator aItor = accounts.begin(); aItor != accounts.end(); ++aItor)
        {
            auto card = (*aItor)->getCard(id);
            if (card != nullptr)
                return card;
        }
    }
    return nullptr;
}

const ITransaction* Storage::getTransaction(const size_t id)
{
    for (std::vector<UserProxy*>::iterator uItor = _users.begin(); uItor != _users.end(); uItor++)
    {
        std::vector<IAccount*> accounts = (*uItor)->accounts();
        for (std::vector<IAccount*>::iterator aItor = accounts.begin(); aItor != accounts.end(); ++aItor)
        {
            auto transaction = (*aItor)->getTransaction(id);
            if (transaction != nullptr)
                return transaction;
        }
    }
    return nullptr;
}

void Storage::commitUser(IUser *u)
{
    DatabaseConnect::getInstance().updateUser(u);
}

void Storage::commitAccount(IAccount *a)
{
    DatabaseConnect::getInstance().updateAccount(a);
}

void Storage::commitCard(ICard *c)
{
    DatabaseConnect::getInstance().updateCard(c);
}

size_t Storage::getNextTransactionId()
{
    return DatabaseConnect::getInstance().newTransactionId();
}

size_t Storage::getNextAccountId()
{
    return DatabaseConnect::getInstance().newAccountId();
}

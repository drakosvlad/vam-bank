#include "Storage.h"

#include "DatabaseConnect.h"
#include "DebitAccount.h"
#include "CardModel.h"

Storage* Storage::_instance = nullptr;

Storage::Storage()
{
    // TEMP SEED
    auto user = new UserModel("Lolkek", "Cheburek", "123456", "lolkek");
    auto account1 = new DebitAccount(user, 1000, 123);
    auto account2 = new DebitAccount(user, 2000, 124);
    user->addAccount(account1);
    user->addAccount(account2);

    _users.push_back(new UserProxy(*user));

    std::vector<IUser*> models = DatabaseConnect::getInstance().getUsers();

    for (std::vector<IUser*>::iterator itor = models.begin(); itor != models.end(); itor++)
    {
        std::vector<IAccount*> accounts = DatabaseConnect::getInstance().getUserAccounts(*itor);
        for (std::vector<IAccount*>::iterator aitor = accounts.begin(); aitor != accounts.end(); aitor++)
        {
            std::vector<const ITransaction*> transactions = DatabaseConnect::getInstance().getAccountTransactions((*aitor)->id());
            for (std::vector<const ITransaction*>::const_iterator titor = transactions.begin(); titor != transactions.end(); titor++)
            {
                (*aitor)->addTransaction(*titor);
            }

            std::vector<ICard*> cards = DatabaseConnect::getInstance().getAccountCards(*aitor);
            for (std::vector<ICard*>::iterator citor = cards.begin(); citor != cards.end(); citor++)
            {
                (*aitor)->addCard(*citor);
            }

            (*itor)->addAccount(*aitor);
        }

        _users.push_back(new UserProxy(*dynamic_cast<UserModel*>(*itor)));
    }
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

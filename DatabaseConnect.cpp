#include "DatabaseConnect.h"
#include <QSqlQuery>

#include "StringUtils.h"
#include "IAccount.h"

DatabaseConnect::DatabaseConnect()
{
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName(DatabaseConnect::dbHost);
    _db.setDatabaseName(DatabaseConnect::dbName);
    _db.setUserName(DatabaseConnect::dbUser);
    _db.setPassword(DatabaseConnect::dbPass);
    _db.open();

    (_qrAddUser = new QSqlQuery(_db))->prepare();
    (_qrAddAccount = new QSqlQuery(_db))->prepare();
    (_qrAddTransaction=new QSqlQuery(_db))->prepare();

    (_qrRmUser = new QSqlQuery(_db))->prepare();
    (_qrRmAccount = new QSqlQuery(_db))->prepare();

    (_qrUpdUser = new QSqlQuery(_db))->prepare();
    (_qrUpdAccount = new QSqlQuery(_db))->prepare("UPDATE accounts SET balance = :balance WHERE id = :id");
    (_qrUpdCard = new QSqlQuery(_db))->prepare("UPDATE cards SET pin = :pin WHERE card_id = :id");

    (_qrGetUsers=new QSqlQuery(_db))->prepare("SELECT login, first_name, last_name, password FROM users");
    (_qrGetUserAccounts = new QSqlQuery(_db))->prepare("SELECT id, balance, account_number FROM accounts WHERE user_login = :user_login");
    (_qrGetAccountCards = new QSqlQuery(_db))->prepare("SELECT id, pin, year, month WHERE id_account = :account_id");
    (_qrGetAccountTransactions = new QSqlQuery(_db))->prepare("SELECT id, time_sent, time_received, amount, account_to, account_from WHERE account_to = :account_id OR account_from = :account_id");
}

DatabaseConnect::~DatabaseConnect()
{
    _instance->_db.close();
    delete _instance;
    delete _qrRmUser;
    delete _qrAddUser;
    delete _qrUpdUser;
    delete _qrUpdCard;
    delete _qrGetUsers;
    delete _qrRmAccount;
    delete _qrAddAccount;
    delete _qrUpdAccount;
    delete _qrAddTransaction;
    delete _qrGetAccountCards;
    delete _qrGetUserAccounts;
    delete _qrGetAccountTransactions;
}

DatabaseConnect& DatabaseConnect::getInstance()
{
    if (_instance == nullptr)
        _instance = new DatabaseConnect();
    return * _instance;
}

void DatabaseConnect::addAccount(const IAccount *)
{
    QSqlQuery qr(_db);
    qr.exec()
}

void DatabaseConnect::addUser(const IUser*)
{

}

void DatabaseConnect::addTransaction(const ITransaction*)
{

}


void DatabaseConnect::removeUser(const std::string&)
{

}

void DatabaseConnect::removeAccount(const size_t id)
{

}


void DatabaseConnect::updateUser(const IUser*)
{

}

void DatabaseConnect::updateAccount(const IAccount* acc)
{
    _qrUpdAccount->bindValue(":balance", acc->balance());
    _qrUpdAccount->bindValue(":id", static_cast<unsigned int>(acc->id()));
    _qrUpdAccount->exec();
}

void DatabaseConnect::updateCard(const ICard* card)
{
    _qrUpdCard->bindValue(":pin", card->pin())
}

std::vector<UserProxy*> DatabaseConnect::getUsers()
{

}

std::vector<const ITransaction*> DatabaseConnect::getAccountTransactions(const size_t id)
{

}

std::vector<IAccount*> DatabaseConnect::getUserAccounts(const std::string&)
{

}

std::vector<ICard*> DatabaseConnect::getAccountCards(const size_t id)
{

}


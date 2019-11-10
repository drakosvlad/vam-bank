#include "DatabaseConnect.h"
#include <QSqlQuery>
#include "IAccount.h"
#include "IUser.h"
#include "ICard.h"

#include "ITransaction.h"

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

    (_qrAddUser = new QSqlQuery(_db))->prepare("INSERT INTO users (login, first_name, last_name, password) VALUES (:login, :first_name, :last_name, :password)");
    (_qrAddAccount = new QSqlQuery(_db))->prepare("INSERT INTO users (id, balance, account_number, user_login) VALUES (:id, :balance, :account_number, :user_login)");
    (_qrAddTransaction=new QSqlQuery(_db))->prepare("INSERT INTO users (id, time_sent, time_received, amount, account_from, account_to) VALUES (:id, :time_sent, :time_received, :amount, :account_from, :account_to)");

    (_qrRmUser = new QSqlQuery(_db))->prepare("DELETE FROM users WHERE login=:login");
    (_qrRmAccount = new QSqlQuery(_db))->prepare("DELETE FROM accounts WHERE id=:id");

    (_qrUpdUser = new QSqlQuery(_db))->prepare("UPDATE users SET password = :password WHERE login = :login");
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

void DatabaseConnect::addAccount(const IAccount * acc)
{
    _qrAddAccount->bindValue(":id", static_cast<unsigned int>(acc->id()));
    _qrAddAccount->bindValue(":balance",acc->balance());
    _qrAddAccount->bindValue(":account_number",acc->accountType());
    _qrAddAccount->bindValue(":user_login",QString::fromLocal8Bit(acc->getBoundUser()->getLogin().c_str()));
    _qrAddAccount->exec();

}

void DatabaseConnect::addUser(const IUser* user)
{
    _qrAddUser->bindValue(":login",QString::fromLocal8Bit(user->getLogin().c_str()));
    _qrAddUser->bindValue(":first_name",QString::fromLocal8Bit(user->getFirstName().c_str()));
    _qrAddUser->bindValue(":last_name",QString::fromLocal8Bit(user->getLastName().c_str()));
    _qrAddUser->bindValue(":password",QString::fromLocal8Bit(user->getPassword().c_str()));
    _qrAddUser->exec();
}

void DatabaseConnect::addTransaction(const ITransaction* trans)
{
    _qrAddTransaction->bindValue(":id",static_cast<unsigned int>(trans->getId()));
    _qrAddTransaction->bindValue(":time_sent",trans->getTimeSent());
    _qrAddTransaction->bindValue(":time_recieved",trans->getTimeRecieved());
    _qrAddTransaction->bindValue(":amount",trans->getAmount());
    _qrAddTransaction->bindValue(":account_from",static_cast<unsigned int>(trans->getSender().id()));
    _qrAddTransaction->bindValue(":account_to",static_cast<unsigned int>(trans->getReciever().id()));
    _qrAddTransaction->exec();
}


void DatabaseConnect::removeUser(const std::string& login)
{
    _qrRmUser->bindValue(":login",QString::fromLocal8Bit(login.c_str()));
    _qrRmUser->exec();
}

void DatabaseConnect::removeAccount(const size_t id)
{
    _qrRmAccount->bindValue(":id",static_cast<unsigned int>(id));
    _qrRmAccount->exec();
}


void DatabaseConnect::updateUser(const IUser* user)
{
    _qrUpdUser->bindValue(":password",QString::fromLocal8Bit(user->getPassword().c_str()));
    _qrUpdUser->bindValue(":login",QString::fromLocal8Bit(user->getLogin().c_str()));
    _qrUpdUser->exec();
}

void DatabaseConnect::updateAccount(const IAccount* acc)
{
    _qrUpdAccount->bindValue(":balance", acc->balance());
    _qrUpdAccount->bindValue(":id", static_cast<unsigned int>(acc->id()));
    _qrUpdAccount->exec();
}

void DatabaseConnect::updateCard(const ICard* card)
{
    _qrUpdCard->bindValue(":pin", card->pin());
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


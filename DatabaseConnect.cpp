#include "DatabaseConnect.h"
#include <QSqlQuery>
#include "IAccount.h"
#include "IUser.h"
#include "ICard.h"

#include "ITransaction.h"

#include "StringUtils.h"
#include "IAccount.h"
#include "ICard.h"
#include "UserModel.h"
#include "TransactionModel.h"
#include "Storage.h"
#include "DebitAccount.h"
#include "CreditAccount.h"
#include "SavingsAccount.h"
#include "CardModel.h"
#include "LocalConfig.h"

#include <QSqlError>


QString DatabaseConnect::dbHost = LocalConfig::DB_HOST;
QString DatabaseConnect::dbName = LocalConfig::DB_NAME;
QString DatabaseConnect::dbPass = LocalConfig::DB_PASS;
QString DatabaseConnect::dbUser = LocalConfig::DB_USER;


DatabaseConnect* DatabaseConnect::_instance= nullptr;

DatabaseConnect::DatabaseConnect()
{
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName(DatabaseConnect::dbHost);
    _db.setDatabaseName(DatabaseConnect::dbName);
    _db.setUserName(DatabaseConnect::dbUser);
    _db.setPassword(DatabaseConnect::dbPass);

    if (_db.open())
    {
        qDebug() << "Database opened";
        (_qrAddUser = new QSqlQuery(_db))->prepare("INSERT INTO users (login, first_name, last_name, password) VALUES (:login, :first_name, :last_name, :password)");
        (_qrAddAccount = new QSqlQuery(_db))->prepare("INSERT INTO accounts (id, balance, account_number, user_login) VALUES (:id, :balance, :account_number, :user_login)");
        (_qrAddTransaction=new QSqlQuery(_db))->prepare("INSERT IGNORE INTO transactions (id, time_sent, time_recieved, amount, account_from, account_to, success) VALUES (:id, :time_sent, :time_received, :amount, :account_from, :account_to, :success)");

        (_qrRmUser = new QSqlQuery(_db))->prepare("DELETE FROM users WHERE login=:login");
        (_qrRmAccount = new QSqlQuery(_db))->prepare("DELETE FROM accounts WHERE id=:id");

        (_qrUpdUser = new QSqlQuery(_db))->prepare("UPDATE users SET password = :password WHERE login = :login");
        (_qrUpdAccount = new QSqlQuery(_db))->prepare("UPDATE accounts SET balance = :balance, payroll_date = :payroll_date WHERE id = :id");
        (_qrUpdCard = new QSqlQuery(_db))->prepare("UPDATE cards SET pin = :pin WHERE card_id = :id");

        (_qrGetUsers=new QSqlQuery(_db))->prepare("SELECT login, first_name, last_name, password FROM users");
        (_qrGetUserAccounts = new QSqlQuery(_db))->prepare("SELECT id, balance, account_number, creation_date, payroll_date, credit_limit FROM accounts WHERE user_login = :user_login");
        (_qrGetAccountCards = new QSqlQuery(_db))->prepare("SELECT id, pin, year, month FROM cards WHERE id_account = :account_id");
        (_qrGetAccountTransactions = new QSqlQuery(_db))->prepare("SELECT id, time_sent, time_recieved, amount, account_to, account_from, success FROM transactions WHERE (account_to = :account_id OR account_from = :account_id)");
    }
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
    _qrAddAccount->bindValue(":user_login",QString::fromStdString(acc->getBoundUser()->getLogin().c_str()));
    _qrAddAccount->exec();
}

void DatabaseConnect::addUser(const IUser* user)
{
    _qrAddUser->bindValue(":login",QString::fromStdString(user->getLogin().c_str()));
    _qrAddUser->bindValue(":first_name",QString::fromStdString(user->getFirstName().c_str()));
    _qrAddUser->bindValue(":last_name",QString::fromStdString(user->getLastName().c_str()));
    _qrAddUser->bindValue(":password",QString::fromStdString(user->getPassword().c_str()));
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
    _qrAddTransaction->bindValue(":success",trans->getSuccess());
    _qrAddTransaction->exec();
    qDebug() << _qrAddTransaction->lastError();
}


void DatabaseConnect::removeUser(const std::string& login)
{
    _qrRmUser->bindValue(":login",QString::fromStdString(login.c_str()));
    _qrRmUser->exec();
}

void DatabaseConnect::removeAccount(const size_t id)
{
    _qrRmAccount->bindValue(":id",static_cast<unsigned int>(id));
    _qrRmAccount->exec();
}


void DatabaseConnect::updateUser(const IUser* user)
{
    _qrUpdUser->bindValue(":password",QString::fromStdString(user->getPassword().c_str()));
    _qrUpdUser->bindValue(":login",QString::fromStdString(user->getLogin().c_str()));
    _qrUpdUser->exec();
}

void DatabaseConnect::updateAccount(const IAccount* acc)
{
    _qrUpdAccount->bindValue(":balance", acc->balance());
    _qrUpdAccount->bindValue(":payroll_date", acc->payrollDate());
    _qrUpdAccount->bindValue(":id", static_cast<unsigned int>(acc->id()));
    _qrUpdAccount->exec();
}

void DatabaseConnect::updateCard(const ICard* card)
{
    _qrUpdCard->bindValue(":pin", stdArrayToHexQString(card->pin()));
    _qrUpdCard->bindValue(":id", stdArrayToHexQString(card->pin()));
    _qrUpdCard->exec();
}

std::vector<IUser*> DatabaseConnect::getUsers()
{
    _qrGetUsers->exec();
    std::vector<IUser*> res;
    while(_qrGetUsers->next())
    {
        auto user = new UserModel(_qrGetUsers->value(1).toString().toStdString(),
                                  _qrGetUsers->value(2).toString().toStdString(),
                                  _qrGetUsers->value(3).toString().toStdString(),
                                  _qrGetUsers->value(0).toString().toStdString());

        res.push_back(user);
    }

    return res;
}

std::vector<const ITransaction*> DatabaseConnect::getAccountTransactions(const size_t id)
{
    _qrGetAccountTransactions->bindValue(":account_id", static_cast<unsigned int>(id));
    _qrGetAccountTransactions->exec();
    std::vector<const ITransaction*> res;
    while(_qrGetAccountTransactions->next())
    {
        // id, time_sent, time_received, amount, account_to, account_from, success
        auto transaction = new TransactionModel(_qrGetAccountTransactions->value(0).toUInt(),
                                                *(Storage::getInstance().getAccount(_qrGetAccountTransactions->value(4).toUInt())),
                                                *(Storage::getInstance().getAccount(_qrGetAccountTransactions->value(5).toUInt())),
                                                _qrGetAccountTransactions->value(3).toInt(),
                                                _qrGetAccountTransactions->value(6).toBool(),
                                                _qrGetAccountTransactions->value(1).toDateTime(),
                                                _qrGetAccountTransactions->value(2).toDateTime());

        if (transaction->getId() > _maxTransactionId)
            _maxTransactionId = transaction->getId();
        res.push_back(transaction);
    }

    return res;
}

std::vector<IAccount*> DatabaseConnect::getUserAccounts(const IUser* user)
{
    _qrGetUserAccounts->bindValue(":user_login", QString::fromStdString(user->getLogin()));
    _qrGetUserAccounts->exec();
    std::vector<IAccount*> res;
    while(_qrGetUserAccounts->next())
    {
        // id, balance, account_number, creation_date, payroll_date, credit_limit
        int accountTypeNumber = _qrGetUserAccounts->value(2).toInt();
        int balance = _qrGetUserAccounts->value(1).toInt();
        unsigned int id = _qrGetUserAccounts->value(0).toUInt();
        QDate creation_date = _qrGetUserAccounts->value(3).toDate();
        QDate payroll_date = _qrGetUserAccounts->value(4).toDate();
        int creditLimit = _qrGetUserAccounts->value(5).toInt();

        if (id > _maxAccountId)
            _maxAccountId = id;

        switch (accountTypeNumber) {
            case 0:
                res.push_back(new DebitAccount(user, balance, creation_date, payroll_date, creditLimit, id));
            break;
            case 1:
                res.push_back(new CreditAccount(user, balance, creation_date, payroll_date, creditLimit, id));
            break;
            case 2:
                res.push_back(new SavingsAccount(user, balance, creation_date, payroll_date, creditLimit, id));
            break;
            default:
                throw "Invalid account type";
        }
    }

    return res;
}

std::vector<ICard*> DatabaseConnect::getAccountCards(const IAccount* account)
{
    _qrGetAccountCards->bindValue(":account_id", static_cast<unsigned int>(account->id()));
    _qrGetAccountCards->exec();
    std::vector<ICard*> res;
    while(_qrGetAccountCards->next())
    {
        // id, pin, year, month
        auto card = new CardModel(hexQStringToStdArray<7>(_qrGetAccountCards->value(0).toString()),
                                  qStringToStdArray<4>(_qrGetAccountCards->value(1).toString()),
                                  { static_cast<unsigned short>(_qrGetAccountCards->value(3).toUInt()), static_cast<unsigned short>(_qrGetAccountCards->value(2).toUInt()) },
                                  *account);

        res.push_back(card);
    }

    return res;
}


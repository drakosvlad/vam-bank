#include "DatabaseConnect.h"
#include <QSqlQuery>

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
    (_qrGetAccountTransactions = new QSqlQuery(_db))->prepare("SELECT id, time_sent, time_received, amount, account_to, account_from, success WHERE account_to = :account_id OR account_from = :account_id");
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
        // id, balance, account_number
        int accountTypeNumber = _qrGetUserAccounts->value(2).toInt();
        int balance = _qrGetUserAccounts->value(1).toInt();
        unsigned int id = _qrGetUserAccounts->value(0).toUInt();
        switch (accountTypeNumber) {
            case 0:
                res.push_back(new DebitAccount(user, balance, id));
            break;
            case 1:
                res.push_back(new CreditAccount(user, balance, id));
            break;
            case 2:
                res.push_back(new SavingsAccount(user, balance, id));
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


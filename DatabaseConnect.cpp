#include <DatabaseConnect.h>
#include <QSqlQuery>

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
    (_qrUpdAccount = new QSqlQuery(_db))->prepare();
    (_qrUpdCard = new QSqlQuery(_db))->prepare();

    (_qrGetUsers=new QSqlQuery(_db))->prepare();
    (_qrGetUserAccounts = new QSqlQuery(_db))-prepare();
    (_qrGetAccountCards = new QSqlQuery(_db))->prepare();
    (_qrGetAccountTransactions = new QSqlQuery(_db))->prepare();
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
void DatabaseConnect::updateAccount(const IAccount*)
{

}
void DatabaseConnect::updateCard(const ICard*)
{

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


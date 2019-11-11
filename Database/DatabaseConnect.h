#pragma once

#include <vector>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class IUser;
class IAccount;
class ICard;
class ITransaction;
class UserProxy;

class DatabaseConnect {
private:
    static DatabaseConnect* _instance;
    DatabaseConnect();
    static QString dbHost;
    static QString dbName;
    static QString dbPass;
    static QString dbUser;
    QSqlDatabase _db;
    QSqlQuery* _qrAddAccount;
    QSqlQuery* _qrAddUser;
    QSqlQuery* _qrAddTransaction;

    QSqlQuery* _qrRmAccount;
    QSqlQuery* _qrRmUser;

    QSqlQuery* _qrUpdCard;
    QSqlQuery* _qrUpdAccount;
    QSqlQuery* _qrUpdUser;

    QSqlQuery* _qrGetUserAccounts;
    QSqlQuery* _qrGetAccountCards;
    QSqlQuery* _qrGetAccountTransactions;
    QSqlQuery* _qrGetUsers;

    size_t _maxAccountId = 1;
    size_t _maxTransactionId = 1;

public:
    static DatabaseConnect& getInstance();
    DatabaseConnect(const DatabaseConnect& )=delete;
    DatabaseConnect& operator=(const DatabaseConnect& )=delete;
    ~DatabaseConnect();

    void addAccount(const IAccount*);
    void addUser(const IUser*);
    void addTransaction(const ITransaction*);

    void removeUser(const std::string&);
    void removeAccount(const size_t);

    void updateUser(const IUser*);
    void updateAccount(const IAccount*);
    void updateCard(const ICard*);

    std::vector<IUser*> getUsers();
    std::vector<const ITransaction*> getAccountTransactions(const size_t);
    std::vector<IAccount*> getUserAccounts(const IUser* user);
    std::vector<ICard*> getAccountCards(const IAccount* account);

    size_t newAccountId() { return ++_maxAccountId; }
    size_t newTransactionId() { return ++_maxTransactionId; }
};

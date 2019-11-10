#pragma once
#include <vector>
#include "IUser.h"
#include "UserModel.h"
#include "UserProxy.h"
#include "IAccount.h"
#include "ITransaction.h"

/**
 * Singleton class that provides a global storage for all bank data
 */
class Storage
{
private:
    Storage();
    std::vector<UserProxy*> _users;

    static Storage* _instance;
public:
    static Storage& getInstance();

    ~Storage();
    Storage(const Storage &) = delete;
    Storage& operator=(const Storage &) = delete;

    IUser* getUser(const std::string login);
    IAccount* getAccount(const size_t id);
    ICard* getCard(const std::array<unsigned char, 7> id);
    const ITransaction* getTransaction(const size_t id);

    void commitUser(IUser *);
    void commitAccount(IAccount *);
    void commitCard(ICard *);

    static size_t getNextTransactionId();
};

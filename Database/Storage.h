#pragma once

#include <vector>

class Storage;
class UserProxy;
class IUser;
class IAccount;
class ICard;
class ITransaction;

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
    static size_t getNextAccountId();

    void init();

    friend class PayrollProcessor;
};

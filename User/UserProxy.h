#pragma once

#include "IUser.h"
#include <Account/AccountProxy.h>

class UserModel;

/**
 * @brief Proxy class for User model
 */
class UserProxy final: public IUser
{
private:
    UserModel& _userModel;
    mutable std::vector<AccountProxy*> _toDeleteAccounts;

    bool do_verifyPassword(const std::string &) const override;
    const std::string& do_getFirstName() const override;
    const std::string& do_getLastName() const override;
    const std::string& do_getLogin() const override;
    const std::string& do_getPassword() const override;
    const IAccount* do_getAccount(const size_t) const override;
    IAccount* do_getAccount(const size_t) override;

    void do_setFirstName(const std::string &) override;
    void do_setLastName(const std::string &) override;
    void do_setPassword(const std::string &) override;
    void do_setLogin(const std::string &) override;

    void do_addAccount(IAccount*) override;
    void do_removeAccount(const IAccount*) override;
    const std::vector<IAccount*> do_accounts() override;
public:
    UserProxy(UserModel &);
    ~UserProxy() override;
};

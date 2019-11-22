#pragma once

#include <vector>

#include "IUser.h"

class IAccount;

/**
 * @brief Class representing bank User
 */
class UserModel final: public IUser
{
private:
    std::string _firstName,_lastName, _password, _login;
    std::vector<IAccount*> _accounts;
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

    bool do_verifyPassword(const std::string&) const override;
    void do_addAccount(IAccount*) override;
    void do_removeAccount(const IAccount *) override;
    const std::vector<IAccount*> do_accounts() override;
public:
    UserModel(
            const std::string& firstName,
            const std::string& lastName,
            const std::string& password,
            const std::string& login
        );
    ~UserModel() override;
};

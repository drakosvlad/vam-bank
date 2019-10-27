#pragma once
#include <vector>
#include "IUser.h"
#include "IAccount.h"

/**
 * @brief Class representing bank User
 */
class UserModel: public IUser
{
private:
    std::string _firstName,_lastName, _password, _login;
    std::vector<IAccount> _accounts;
public:
    UserModel(
            const std::string& firstName,
            const std::string& lastName,
            const std::string& password,
            const std::string& login,
            const IAccount* account
        );
    ~UserModel() override;

    const std::string& getFirstName() const override;
    const std::string& getLastName() const override;
    const std::string& getPassword() const override;
    const std::string& getLogin() const override;

    void setFirstName(const std::string &) override;
    void setLastName(const std::string &) override;
    void setPassword(const std::string &) override;
    void setLogin(const std::string &) override;

    void addAccount(const IAccount &) override;
    IAccount& getAccount(const size_t) const override;
    void removeAccount(const size_t id) override;
};

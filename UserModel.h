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
    std::vector<IAccount*> _accounts;
public:
    UserModel(
            const std::string& firstName,
            const std::string& lastName,
            const std::string& password,
            const std::string& login
        );
    ~UserModel() override;

    const std::string& getFirstName() const override;
    const std::string& getLastName() const override;
    const std::string& getLogin() const override;
    const IAccount* getAccount(const size_t) const override;
    IAccount* getAccount(const size_t) override;

    void setFirstName(const std::string &) override;
    void setLastName(const std::string &) override;
    void setPassword(const std::string &) override;
    void setLogin(const std::string &) override;

    bool verifyPassword(const std::string&) const override;
    void addAccount(IAccount*) override;
    void removeAccount(const IAccount *) override;
    const std::vector<IAccount*>& accounts() override;

};

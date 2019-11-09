#pragma once
#include "UserModel.h"

/**
 * @brief Proxy class for User model
 */
class UserProxy: public IUser
{
private:
    const UserModel& _userModel;

public:
    UserProxy(const UserModel &);
    ~UserProxy() override;

    void verifyPassword(const std::string &) const override;
    const std::string& getFirstName() const override;
    const std::string& getLastName() const override;
    const std::string& getPassword() const override;
    const std::string& getLogin() const override;
    const IAccount& getAccount(const size_t) const override;

    void setFirstName(const std::string &) override;
    void setLastName(const std::string &) override;
    void setPassword(const std::string &) override;
    void setLogin(const std::string &) override;

    void addAccount(IAccount*) override;
    void removeAccount(const IAccount&) override;
    virtual const std::vector<IAccount*>& accounts() override;
};

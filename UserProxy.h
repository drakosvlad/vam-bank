#pragma once
#include "UserModel.h"

/**
 * @brief Proxy class for User model
 */
class UserProxy: public IUser
{
private:
    UserModel& _userModel;

public:
    UserProxy(UserModel &);
    ~UserProxy() override;

    bool verifyPassword(const std::string &) const override;
    const std::string& getFirstName() const override;
    const std::string& getLastName() const override;
    const std::string& getLogin() const override;
    const IAccount* getAccount(const size_t) const override;
    IAccount* getAccount(const size_t) override;

    void setFirstName(const std::string &) override;
    void setLastName(const std::string &) override;
    void setPassword(const std::string &) override;
    void setLogin(const std::string &) override;

    void addAccount(IAccount*) override;
    void removeAccount(const IAccount*) override;
    const std::vector<IAccount*>& accounts() override;
};

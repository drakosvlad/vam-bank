#pragma once
#include "UserModel.h"

class UserProxy: public IUser
{
private:
    const UserModel& _userModel;
public:
    UserProxy(const UserModel&);
    ~UserProxy();
    void verifyPassword(const string&) const;
    const string& getFirstName() const;
    const string& getLastName() const;
    const string& getPassword() const;
    const string& getLogin() const;

    void setFirstName(const string&);
    void setLastName(const string&);
    void setPassword(const string&);
    void setLogin(const string&);

    void addAccount(const IAccount&) const;
    void removeAccount(const size_t id);
};

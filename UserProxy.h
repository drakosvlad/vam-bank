#pragma once
#include "UserModel.h"

class UserProxy: public IUser
{
private:
    UserModel& _userModel;
public:
    // TODO constructor
    void verifyPassword(const string&) const;
    const string& getFirstName() const;
    const string& getLastName() const;
    const string& getPassword() const;
    const string& getLogin() const; 
    void setFirstName(const string&);
    void setLastName(const string&);
    void setPassword(const string&);
    void setLogin(const string&);
};

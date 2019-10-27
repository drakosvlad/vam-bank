#pragma once
#include <vector>
#include "IUser.h"
#include "IAccount.h"


class UserModel: public IUser
{
private:
    string _firstName,_lastName, _password, _login;
    vector<IAccount> _accounts;
public:
    UserModel(const string& _firstName,const string& _lastName,const string& _password, const string& _login, const IAccount*);
    ~UserModel();
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

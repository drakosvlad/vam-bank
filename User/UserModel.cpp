#include "UserModel.h"

#include <Account/IAccount.h>

UserModel::UserModel(const std::string& firstName,
                     const std::string& lastName,
            const std::string& password,
            const std::string& login)
    : _firstName(firstName), _lastName(lastName),
    _password(password), _login(login)
{}

UserModel::~UserModel(){}

const std::string& UserModel::do_getFirstName() const
{
    return _firstName;
};

const std::string& UserModel::do_getLastName() const
{
    return _lastName;
};

const std::string& UserModel::do_getLogin() const
{
    return _login;
};

const std::string& UserModel::do_getPassword() const
{
    return _password;
};

void UserModel::do_setFirstName(const std::string& firstName)
{
    _firstName = firstName;
    return;
};

void UserModel::do_setLastName(const std::string& lastName)
{
    _lastName = lastName;
    return;
};

void UserModel::do_setPassword(const std::string& password)
{
    _password = password;
    return;
};

void UserModel::do_setLogin(const std::string& login)
{
    _login=login;
    return;
};

void UserModel::do_addAccount(IAccount* account)
{
    _accounts.push_back(account);
    return;
};

const IAccount* UserModel::do_getAccount(const size_t id) const
{
    return const_cast<UserModel*>(this)->getAccount(id);
};

IAccount* UserModel::do_getAccount(const size_t id)
{
    for (std::vector<IAccount*>::iterator it = _accounts.begin(); it!=_accounts.end(); ++it){
        if ((*it)->id() == id)
            return *it;
    }
    return nullptr;
};

void UserModel::do_removeAccount(const IAccount * account)
{
    for (std::vector<IAccount*>::iterator it = _accounts.begin(); it!=_accounts.end(); ++it){
        if ((*it)->id() == account->id())
            _accounts.erase(it);
    }
};

bool UserModel::do_verifyPassword(const std::string &password) const
{
    return password == _password;
}

const std::vector<IAccount*> UserModel::do_accounts()
{
    return _accounts;
}

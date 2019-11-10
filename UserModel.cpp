#include "UserModel.h"

UserModel::UserModel(const std::string& firstName,
                     const std::string& lastName,
            const std::string& password,
            const std::string& login)
    : _firstName(firstName), _lastName(lastName),
    _password(password), _login(login)
{}

UserModel::~UserModel(){}

const std::string& UserModel::getFirstName() const
{
    return _firstName;
};

const std::string& UserModel::getLastName() const
{
    return _lastName;
};

const std::string& UserModel::getLogin() const
{
    return _login;
};

const std::string& UserModel::getPassword() const
{
    return _password;
};

void UserModel::setFirstName(const std::string& firstName)
{
    _firstName = firstName;
    return;
};

void UserModel::setLastName(const std::string& lastName)
{
    _lastName = lastName;
    return;
};

void UserModel::setPassword(const std::string& password)
{
    _password = password;
    return;
};

void UserModel::setLogin(const std::string& login)
{
    _login=login;
    return;
};

void UserModel::addAccount(IAccount* account)
{
    _accounts.push_back(account);
    return;
};

const IAccount* UserModel::getAccount(const size_t id) const
{
    return const_cast<UserModel*>(this)->getAccount(id);
};

IAccount* UserModel::getAccount(const size_t id)
{
    for (std::vector<IAccount*>::iterator it = _accounts.begin(); it!=_accounts.end(); ++it){
        if ((*it)->id() == id)
            return *it;
    }
    return nullptr;
};

void UserModel::removeAccount(const IAccount * account)
{
    for (std::vector<IAccount*>::iterator it = _accounts.begin(); it!=_accounts.end(); ++it){
        if ((*it)->id() == account->id())
            _accounts.erase(it);
    }
};

bool UserModel::verifyPassword(const std::string &password) const
{
    return password == _password;
}

const std::vector<IAccount*> UserModel::accounts()
{
    return _accounts;
}

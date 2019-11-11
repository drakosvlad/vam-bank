#include "UserProxy.h"

#include <Account/AccountProxy.h>
#include <Database/DatabaseConnect.h>
#include <Database/Storage.h>
#include <User/UserModel.h>

UserProxy::UserProxy(UserModel &model) : _userModel(model)
{

}

UserProxy::~UserProxy()
{
    for (auto p : _toDeleteAccounts)
    {
        delete p;
    }

    _toDeleteAccounts.clear();
}

bool UserProxy::verifyPassword(const std::string &password) const
{
    return _userModel.verifyPassword(password);
}

const std::string& UserProxy::getFirstName() const
{
    return _userModel.getFirstName();
}

const std::string& UserProxy::getLastName() const
{
    return _userModel.getLastName();
}

const std::string& UserProxy::getLogin() const
{
    return _userModel.getLogin();
}
const std::string& UserProxy::getPassword() const
{
    return _userModel.getPassword();
}

const IAccount* UserProxy::getAccount(const size_t id) const
{
    return const_cast<IAccount*>(const_cast<const UserProxy*>(this)->getAccount(id));
}

IAccount* UserProxy::getAccount(const size_t id)
{
    auto account = _userModel.getAccount(id);
    if (account!=nullptr){
        _toDeleteAccounts.push_back(new AccountProxy(account));
        return _toDeleteAccounts.back();
    }
    return nullptr;
}

void UserProxy::setFirstName(const std::string &name)
{
    _userModel.setFirstName(name);
    Storage::getInstance().commitUser(this);
}

void UserProxy::setLastName(const std::string &name)
{
    _userModel.setLastName(name);
    Storage::getInstance().commitUser(this);
}

void UserProxy::setPassword(const std::string &password)
{
    _userModel.setPassword(password);
    Storage::getInstance().commitUser(this);
}

void UserProxy::setLogin(const std::string &login)
{
    _userModel.setLogin(login);
    Storage::getInstance().commitUser(this);
}

void UserProxy::addAccount(IAccount *account)
{
    _userModel.addAccount(account);
    DatabaseConnect::getInstance().addAccount(account);
}

void UserProxy::removeAccount(const IAccount* account)
{
    _userModel.removeAccount(account);
    DatabaseConnect::getInstance().removeAccount(account->id());
}

const std::vector<IAccount*> UserProxy::accounts()
{
    std::vector<IAccount*> proxyAccounts;
    std::vector<IAccount*> modelAccounts = _userModel.accounts();
    for (std::vector<IAccount*>::iterator itor = modelAccounts.begin(); itor != modelAccounts.end(); ++itor)
    {
        _toDeleteAccounts.push_back(new AccountProxy(*itor));
        proxyAccounts.push_back(_toDeleteAccounts.back());
    }
    return proxyAccounts;
}

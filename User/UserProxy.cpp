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

bool UserProxy::do_verifyPassword(const std::string &password) const
{
    return _userModel.verifyPassword(password);
}

const std::string& UserProxy::do_getFirstName() const
{
    return _userModel.getFirstName();
}

const std::string& UserProxy::do_getLastName() const
{
    return _userModel.getLastName();
}

const std::string& UserProxy::do_getLogin() const
{
    return _userModel.getLogin();
}
const std::string& UserProxy::do_getPassword() const
{
    return _userModel.getPassword();
}

const IAccount* UserProxy::do_getAccount(const size_t id) const
{
    return const_cast<IAccount*>(const_cast<const UserProxy*>(this)->getAccount(id));
}

IAccount* UserProxy::do_getAccount(const size_t id)
{
    auto account = _userModel.getAccount(id);
    if (account!=nullptr){
        _toDeleteAccounts.push_back(new AccountProxy(account));
        return _toDeleteAccounts.back();
    }
    return nullptr;
}

void UserProxy::do_setFirstName(const std::string &name)
{
    _userModel.setFirstName(name);
    Storage::getInstance().commitUser(this);
}

void UserProxy::do_setLastName(const std::string &name)
{
    _userModel.setLastName(name);
    Storage::getInstance().commitUser(this);
}

void UserProxy::do_setPassword(const std::string &password)
{
    _userModel.setPassword(password);
    Storage::getInstance().commitUser(this);
}

void UserProxy::do_setLogin(const std::string &login)
{
    _userModel.setLogin(login);
    Storage::getInstance().commitUser(this);
}

void UserProxy::do_addAccount(IAccount *account)
{
    _userModel.addAccount(account);
    DatabaseConnect::getInstance().addAccount(account);
}

void UserProxy::do_removeAccount(const IAccount* account)
{
    _userModel.removeAccount(account);
    DatabaseConnect::getInstance().removeAccount(account->id());
}

const std::vector<IAccount*> UserProxy::do_accounts()
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

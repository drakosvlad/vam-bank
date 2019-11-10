#include "UserProxy.h"
#include "Storage.h"
#include "AccountProxy.h"
#include "DatabaseConnect.h"

UserProxy::UserProxy(UserModel &model) : _userModel(model)
{

}

UserProxy::~UserProxy()
{

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

const IAccount* UserProxy::getAccount(const size_t id) const
{
    // TODO delete
    auto account = _userModel.getAccount(id);
    return account == nullptr ? nullptr: new AccountProxy(account);
}

IAccount* UserProxy::getAccount(const size_t id)
{
    auto account = _userModel.getAccount(id);
    return account == nullptr ? nullptr: new AccountProxy(account);
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
        proxyAccounts.push_back(new AccountProxy(*itor));
    }
    return proxyAccounts;
}

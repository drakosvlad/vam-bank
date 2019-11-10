#include "UserProxy.h"
#include "Storage.h"
#include "AccountProxy.h"

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
    return new AccountProxy(_userModel.getAccount(id));
}

IAccount* UserProxy::getAccount(const size_t id)
{
    return new AccountProxy(_userModel.getAccount(id));
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
    Storage::getInstance().commitUser(this);
}

void UserProxy::removeAccount(const IAccount* account)
{
    _userModel.removeAccount(account);
    Storage::getInstance().commitUser(this);
}

const std::vector<IAccount*>& UserProxy::accounts()
{
    std::vector<IAccount*> proxyAccounts;
    std::vector<IAccount*> modelAccounts = _userModel.accounts();
    for (std::vector<IAccount*>::iterator itor = modelAccounts.begin(); itor != modelAccounts.end(); ++itor)
    {
        proxyAccounts.push_back(new AccountProxy(*itor));
    }
    return proxyAccounts;
}

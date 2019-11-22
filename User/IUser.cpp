#include "IUser.h"

IUser::~IUser()
{

}

bool IUser::verifyPassword(const std::string& pass) const
{
    return do_verifyPassword(pass);
}
const std::string& IUser::getFirstName() const
{
    return do_getFirstName();
}
const std::string& IUser::getLastName() const
{
    return do_getLastName();
}
const std::string& IUser::getLogin() const
{
    return do_getLogin();
}
const std::string& IUser::getPassword() const
{
    return do_getPassword();
}

void IUser::setFirstName(const std::string& firstN)
{
    do_setFirstName(firstN);
}
void IUser::setLastName(const std::string& lastN)
{
    do_setLastName(lastN);
}
void IUser::setPassword(const std::string& pass)
{
    do_setPassword(pass);
}
void IUser::setLogin(const std::string& login)
{
    do_setLogin(login);
}


void IUser::addAccount(IAccount* acc)
{
    do_addAccount(acc);
}
const IAccount* IUser::getAccount(const size_t id) const
{
    return do_getAccount(id);
}
IAccount* IUser::getAccount(const size_t id)
{
    return do_getAccount(id);
}
void IUser::removeAccount(const IAccount * acc)
{
    do_removeAccount(acc);
}
const std::vector<IAccount*> IUser::accounts()
{
    return do_accounts();
}

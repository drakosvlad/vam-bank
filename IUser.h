#pragma once
#include <string>
#include "IAccount.h"

/**
 * @brief Bank User interface
 */
class IUser
{
public:
    virtual ~IUser()=0;

    virtual void verifyPassword(const std::string&) const = 0;
    virtual const std::string& getFirstName() const = 0;
    virtual const std::string& getLastName() const = 0;
    virtual const std::string& getPassword() const = 0;
    virtual const std::string& getLogin() const = 0;

    virtual void setFirstName(const std::string&) = 0;
    virtual void setLastName(const std::string&) = 0;
    virtual void setPassword(const std::string&) = 0;
    virtual void setLogin(const std::string&) = 0;

    virtual void addAccount(const IAccount&) = 0;
    virtual IAccount& getAccount(const size_t) const = 0;
    virtual void removeAccount(const size_t) = 0;
    virtual const std::vector<IAccount*> & accounts() = 0;
};

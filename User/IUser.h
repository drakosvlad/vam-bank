#pragma once

#include <string>
class IAccount;
#include <vector>

/**
 * @brief Bank User interface
 */
class IUser
{
private:
    virtual bool do_verifyPassword(const std::string&) const = 0;
    virtual const std::string& do_getFirstName() const = 0;
    virtual const std::string& do_getLastName() const = 0;
    virtual const std::string& do_getLogin() const = 0;
    virtual const std::string& do_getPassword() const = 0;

    virtual void do_setFirstName(const std::string&) = 0;
    virtual void do_setLastName(const std::string&) = 0;
    virtual void do_setPassword(const std::string&) = 0;
    virtual void do_setLogin(const std::string&) = 0;


    virtual void do_addAccount(IAccount*) = 0;
    virtual const IAccount* do_getAccount(const size_t) const = 0;
    virtual IAccount* do_getAccount(const size_t) = 0;
    virtual void do_removeAccount(const IAccount *) = 0;
    virtual const std::vector<IAccount*> do_accounts() = 0;
public:
    virtual ~IUser();

    bool verifyPassword(const std::string&) const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getLogin() const;
    const std::string& getPassword() const;

    void setFirstName(const std::string&);
    void setLastName(const std::string&);
    void setPassword(const std::string&);
    void setLogin(const std::string&);


    void addAccount(IAccount*);
    const IAccount* getAccount(const size_t) const;
    IAccount* getAccount(const size_t);
    void removeAccount(const IAccount *);
    const std::vector<IAccount*> accounts();
};

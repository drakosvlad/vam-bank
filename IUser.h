#ifndef IUSER
#define IUSER
#include <string>
#include "IAccount.h"

using namespace std;

class IUser{
public:
    virtual ~IUser()=0;
    virtual const string& getFirstName() const =0;
    virtual const string& getSurname() const= 0;
    virtual const string& getPassword() const=0;
    virtual const string& getLogin() const=0; 
    virtual void setFirstName(const string&)=0;
    virtual void setSurname(const string&)=0;
    virtual void setPassword(const string&)=0;
    virtual void setLogin(const string&)=0;
    virtual void verifyPassword(const string&)=0;
};

#endif
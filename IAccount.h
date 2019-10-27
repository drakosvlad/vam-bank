#pragma once
#include <array>
#include <ostream>
#include <vector>

class ICard;
class ITransaction;

class IAccount
{
protected:
    /**
   * Adds the amount of received money to the account, including the fee
   */
    virtual void acceptTransfer(int amount) = 0;
public:
    virtual ~IAccount() = 0;
    virtual void transfer(IAccount& acc) = 0;
    virtual int balance() const = 0;
    virtual size_t id() const = 0;
    virtual bool isPaymentAccount() const = 0;
    virtual void addCard(ICard & card) = 0;
    virtual ICard* getCard(const std::array<unsigned char, 16> & cardNum) = 0;
    virtual void removeCard(const std::array<unsigned char, 16> & cardNum) = 0;
    virtual const std::vector<ICard*>& cards()=0;
    virtual const std::vector<ITransaction*>& transactions()=0;
};

template <typename Policy>
std::ostream& operator<<(std::ostream & out, const IAccount & account)
{
    out << "Account #" << account.id() << " with the balance of UAH" << account.balance();
}

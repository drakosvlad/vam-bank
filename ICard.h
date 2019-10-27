#pragma once
#include <array>
#include <string>
#include <IAccount.h>

/**
 * Bit field for storing card due date up to 4095 year
 */
struct DueDate
{
    unsigned short year : 12;
    unsigned short month : 4;
};

/**
 * @brief Interface for bank card
 */
class ICard
{
public:
    virtual ~ICard();
    virtual void changePin(const std::string&) = 0;
    virtual const std::array<unsigned char, 4>& verifyPin() const;
    virtual const std::array<unsigned char, 16>& getCardNumber() const = 0;
    virtual const IAccount& getAccount() const = 0;
    virtual const DueDate& getDueDate() const = 0;
};

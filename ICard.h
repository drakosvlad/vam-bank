#pragma once
#include <array>

class IAccount;

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
    virtual void changePin(const std::array<unsigned char, 4> &) = 0;
    virtual const std::array<unsigned char, 4> & pin() = 0;
    virtual bool verifyPin(const std::array<unsigned char, 4> &) const = 0;
    // Array containing 7 bytes
    virtual const std::array<unsigned char, 7> getCardId() const = 0;
    virtual const IAccount* getAccount() const = 0;
    virtual const DueDate getDueDate() const = 0;
};

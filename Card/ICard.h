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
private:
    virtual void do_changePin(const std::array<unsigned char, 4> &) = 0;
    virtual const std::array<unsigned char, 4> & do_pin() const = 0;
    virtual bool do_verifyPin(const std::array<unsigned char, 4> &) const = 0;
    virtual const std::array<unsigned char, 7> do_getCardId() const = 0;
    virtual const IAccount* do_getAccount() const = 0;
    virtual const DueDate do_getDueDate() const = 0;
public:
    virtual ~ICard();
    void changePin(const std::array<unsigned char, 4> &);
    const std::array<unsigned char, 4> & pin() const;
    bool verifyPin(const std::array<unsigned char, 4> &) const;
    // Array containing 7 bytes
    const std::array<unsigned char, 7> getCardId() const;
    const IAccount* getAccount() const;
    const DueDate getDueDate() const;
};

#pragma once
#include "ICard.h"

class CardModel : public ICard
{
private:
    std::array<unsigned char, 16> _cardNumber;
    std::string _pin;
    DueDate _dueDate;
    const IAccount& _bindedAccount;
public:
    CardModel(
        const std::array<unsigned char, 16>& cardNumber,
        const std::string& _pin,
        const DueDate& _dueDate,
        const IAccount& _bindedAccount
    );
    ~CardModel();
    CardModel(const CardModel&);
    CardModel& operator=(const CardModel&)=delete;
    void changePin(const std::string&);
    const std::array<unsigned char, 4>& verifyPin() const;
    const std::array<unsigned char, 16>& getCardNumber() const;
    const IAccount& getAccount() const;
    const DueDate& getDueDate() const;
};

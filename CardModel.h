#pragma once
#include "ICard.h"

/**
 * @brief Class representing bank card
 */
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
    ~CardModel() override;
    CardModel(const CardModel&);
    CardModel& operator=(const CardModel&)=delete;
    void changePin(const std::string&) override;
    const std::array<unsigned char, 4>& verifyPin() const override;
    const std::array<unsigned char, 16>& getCardNumber() const override;
    const IAccount& getAccount() const override;
    const DueDate& getDueDate() const override;
};

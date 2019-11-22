#pragma once

#include "ICard.h"

/**
 * @brief Class representing bank card
 */
class CardModel final: public ICard
{
private:
    std::array<unsigned char, 7> _cardId;
    std::array<unsigned char, 4> _pin;
    DueDate _dueDate;
    const IAccount& _boundAccount;

    void do_changePin(const std::array<unsigned char, 4> &) override;
    const std::array<unsigned char, 4> & do_pin() const override;
    bool do_verifyPin(const std::array<unsigned char, 4> &) const override;
    const std::array<unsigned char, 7> do_getCardId() const override;
    const IAccount* do_getAccount() const override;
    const DueDate do_getDueDate() const override;
public:
    CardModel(
        const std::array<unsigned char, 7>& cardId,
        const std::array<unsigned char, 4>& pin,
        const DueDate& dueDate,
        const IAccount& bindedAccount
    );
    ~CardModel() override;
    CardModel(const CardModel&) = delete;
    CardModel& operator=(const CardModel &) = delete;
};

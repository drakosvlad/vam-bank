#pragma once
#include "CardModel.h"

/**
 * @brief The proxy class
 */
class CardProxy : public ICard
{
private:
    CardModel& _model;
public:
    CardProxy(CardModel& model) : _model(model) {  }
    ~CardProxy() override {  }
    CardProxy(const CardProxy& proxy) = delete;
    CardProxy& operator=(CardProxy & proxy) = delete;

    void changePin(const std::array<unsigned char, 4> &) override;
    bool verifyPin(const std::array<unsigned char, 4> &) const override;
    const std::array<unsigned char, 16> getCardNumber() const override;
    const std::array<unsigned char, 7> getCardId() const override;
    const IAccount& getAccount() const override;
    const DueDate getDueDate() const override;
};

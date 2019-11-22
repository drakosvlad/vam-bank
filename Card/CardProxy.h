#pragma once

#include "CardModel.h"

/**
 * @brief The proxy class
 */
class CardProxy final: public ICard
{
private:
    CardModel& _model;
    void do_changePin(const std::array<unsigned char, 4> &) override;
    const std::array<unsigned char, 4> & do_pin() const override;
    bool do_verifyPin(const std::array<unsigned char, 4> &) const override;
    const std::array<unsigned char, 7> do_getCardId() const override;
    const IAccount* do_getAccount() const override;
    const DueDate do_getDueDate() const override;
public:
    CardProxy(CardModel& model) : _model(model) {  }
    ~CardProxy() override {  }
    CardProxy(const CardProxy& proxy) = delete;
    CardProxy& operator=(CardProxy & proxy) = delete;


};

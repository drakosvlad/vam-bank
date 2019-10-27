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
    CardProxy(const CardProxy& proxy) : _model(proxy._model) {  }
    CardProxy& operator=(CardProxy & proxy) = delete;

    void changePin(const std::string&) override;
    const std::array<unsigned char,4>& verifyPin() const override;
    const std::array<unsigned char,16>& getCardNumber() const override;
    const IAccount& getAccount() const override;
    const DueDate& getDueDate() const override;
};

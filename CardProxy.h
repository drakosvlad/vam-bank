#pragma once
#include "CardModel.h"

class CardProxy{
private:
    CardModel& _model;
public:
    CardProxy(const CardModel& model):_model(model){};
    ~CardProxy(){};
    CardProxy(const CardProxy& proxy):_model(proxy._model){};
    CardProxy& operator=(CardProxy & proxy) = delete;
    void changePin(const string&);
    const array<unsigned char,4>& verifyPin() const;
    const array<unsigned char,16>& getCardNumber() const;
    const IAccount& getAccount() const;
    const DueDate& getDueDate() const;
}
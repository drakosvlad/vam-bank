#pragma once
#include "AccountModel.h"
#include "Storage.h"
#include "CardProxy.h"

/**
 * @brief Account proxy class
 */
class AccountProxy : public IAccount {
private:
    IAccount* _model;
public:
    AccountProxy(IAccount* model);
    ~AccountProxy() override;
    AccountProxy(AccountProxy & proxy) = delete;
    AccountProxy& operator=(AccountProxy & proxy) = delete;

    void transfer(IAccount& acc, const int amount) override;
    void acceptTransfer (const int amount) override;
    int balance() const override;
    size_t id() const override;
    bool isPaymentAccount() const override;
    void addCard(ICard* card) override;
    ICard* getCard(const std::array<unsigned char, 7> & id) override;
    const ICard* getCard(const std::array<unsigned char, 7> & id) const override;
    void removeCard(const std::array<unsigned char, 7> & cardNum) override;
    const std::vector<ICard*> cards() const override;
    const std::vector<const ITransaction*> transactions() const override;
    void addTransaction(const ITransaction *) override;
    const ITransaction* getTransaction(const size_t id) const override;
};

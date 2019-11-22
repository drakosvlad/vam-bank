#pragma once

#include "AccountModel.h"

/**
 * @brief Account proxy class
 */
class AccountProxy final: public IAccount {
private:
    IAccount* _model;
    mutable std::vector<ICard*> _toDeleteCards;
    void do_transfer(IAccount& acc, const int amount) override;
    void do_acceptTransfer(const int amount) override;
    int do_balance() const override;
    size_t do_id() const override;
    const QString do_getAccountName() const override;
    bool do_isPaymentAccount() const override;
    short do_accountType() const override;
    void do_addCard(ICard* card) override;

    ICard* do_getCard(const std::array<unsigned char, 7> & id) override;
    const ICard* do_getCard(const std::array<unsigned char, 7> & id) const override;
    const IUser* do_getBoundUser() const override;
    void do_removeCard(const std::array<unsigned char, 7> & cardNum) override;
    const std::vector<ICard*> do_cards() const override;
    const std::vector<const ITransaction*> do_transactions() const override;
    void do_addTransaction(const ITransaction *) override;
    const ITransaction* do_getTransaction(const size_t id) const override;
    const QDate do_creationDate() const override;
    const QDate do_payrollDate() const override;
    int do_creditLimit() const override;

    int do_payroll() override;
public:
    AccountProxy(IAccount* model);
    ~AccountProxy() override;
    AccountProxy(AccountProxy & proxy) = delete;
    AccountProxy& operator=(AccountProxy & proxy) = delete;
};

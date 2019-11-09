#include "AccountModel.h"

/**
 * @brief Account proxy class
 */
template<typename Policy>
class AccountProxy : public IAccount {
private:
    AccountModel<Policy>& _model;
protected:
    void acceptTransfer(const int amount);
public:
    AccountProxy(AccountModel<Policy> & model) : _model(model) {  }
    ~AccountProxy() {  }
    AccountProxy(AccountProxy & proxy) : _model(proxy._model) {  }
    AccountProxy& operator=(AccountProxy & proxy) = delete;

    void transfer(IAccount& acc, const int amount) override;
    int balance() const override { return this->_balance; }
    size_t id() const override { return this->_id; }
    bool isPaymentAccount() const override { return Policy::_isPaymentAccount; }
    void addCard(ICard & card) override;
    ICard* getCard(const std::array<unsigned char, 16> & cardNum) const override;
    void removeCard(const std::array<unsigned char, 16> & cardNum) override;
    const std::vector<ICard*>& cards() override;
    const std::vector<const ITransaction*>& transactions() const override;
};


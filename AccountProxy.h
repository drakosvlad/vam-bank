#include "AccountModel.h"

/**
 * @brief Account proxy class
 */
template<typename Policy>
class AccountProxy : public IAccount {
private:
    AccountModel<Policy>& _model;
protected:
    void acceptTransfer(int amount);
public:
    AccountProxy(AccountModel<Policy> & model) : _model(model) {  }
    ~AccountProxy() {  }
    AccountProxy(AccountProxy & proxy) : _model(proxy._model) {  }
    AccountProxy& operator=(AccountProxy & proxy) = delete;

    void transfer(IAccount& acc);
    int balance() const;
    size_t id() const;
    bool isPaymentAccount() const;
    void addCard(ICard & card);
    ICard* getCard(const std::array<unsigned char, 16> & cardNum);
    void removeCard(const std::array<unsigned char, 16> & cardNum);
    const std::vector<ICard*>& cards();
};

#include "AccountProxy.h"
#include <Card/CardProxy.h>
#include <Database/Storage.h>
#include <Database/DatabaseConnect.h>

AccountProxy::AccountProxy(IAccount * model) : _model(model)
{

}

AccountProxy::~AccountProxy()
{
    for (auto p : _toDeleteCards)
    {
        delete p;
    }

    _toDeleteCards.clear();
}

void AccountProxy::do_acceptTransfer (const int amount)
{
    _model->acceptTransfer(amount);
    Storage::getInstance().commitAccount(_model);
}

void AccountProxy::do_transfer(IAccount& acc, const int amount)
{
    this->_model->transfer(acc, amount);
    Storage::getInstance().commitAccount(_model);
    Storage::getInstance().commitAccount(&acc);
}

int AccountProxy::do_balance() const
{
    return _model->balance();
}

size_t AccountProxy::do_id() const
{
    return _model->id();
}

bool AccountProxy::do_isPaymentAccount() const
{
    return _model->isPaymentAccount();
}
short AccountProxy::do_accountType() const
{
    return _model->accountType();
}

void AccountProxy::do_addCard(ICard* card)
{
    _model->addCard(card);
}

const ICard* AccountProxy::do_getCard(const std::array<unsigned char, 7> &id) const
{
    return const_cast<ICard*>(const_cast<const AccountProxy*>(this)->getCard(id));
}

ICard* AccountProxy::do_getCard(const std::array<unsigned char, 7> &id)
{
    auto cardPtr = _model->getCard(id);
    if (cardPtr != nullptr)
    {
        auto card = new CardProxy(*dynamic_cast<CardModel*>(cardPtr));
        _toDeleteCards.push_back(card);
        return _toDeleteCards.back();
    }
    return nullptr;
}

const IUser* AccountProxy::do_getBoundUser() const
{
    return _model->getBoundUser();
};
void AccountProxy::do_removeCard(const std::array<unsigned char, 7> &cardNum)
{
    _model->removeCard(cardNum);
    Storage::getInstance().commitAccount(_model);
}

const std::vector<ICard*> AccountProxy::do_cards() const
{
    // Todo delete
    std::vector<ICard*> proxyCards;
    std::vector<ICard*> modelCards = _model->cards();
    for (std::vector<ICard*>::iterator itor = modelCards.begin(); itor != modelCards.end(); itor++)
    {
        _toDeleteCards.push_back(new CardProxy(*dynamic_cast<CardModel*>(*itor)));
        proxyCards.push_back(_toDeleteCards.back());
    }

    return proxyCards;
}

const QString AccountProxy::do_getAccountName() const
{
    return _model->getAccountName();
};
const std::vector<const ITransaction*> AccountProxy::do_transactions() const
{
    return _model->transactions();
}

void AccountProxy::do_addTransaction(const ITransaction *tr)
{
    _model->addTransaction(tr);
    DatabaseConnect::getInstance().addTransaction(tr);
}

const ITransaction* AccountProxy::do_getTransaction(const size_t id) const
{
    return _model->getTransaction(id);
}

const QDate AccountProxy::do_creationDate() const
{
    return _model->creationDate();
}

const QDate AccountProxy::do_payrollDate() const
{
    return _model->payrollDate();
}

int AccountProxy::do_creditLimit() const
{
    return _model->creditLimit();
}

int AccountProxy::do_payroll()
{
    int fee = _model->payroll();
    Storage::getInstance().commitAccount(_model);
    return fee;
}

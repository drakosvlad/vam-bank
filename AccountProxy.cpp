#include "AccountProxy.h"

AccountProxy::AccountProxy(IAccount * model) : _model(model)
{

}

AccountProxy::~AccountProxy()
{

}

void AccountProxy::acceptTransfer (const int amount)
{
    _model->acceptTransfer(amount);
    Storage::getInstance().commitAccount(_model);
}

void AccountProxy::transfer(IAccount& acc, const int amount)
{
    this->_model->transfer(acc, amount);
    Storage::getInstance().commitAccount(_model);
    Storage::getInstance().commitAccount(&acc);
}

int AccountProxy::balance() const
{
    return _model->balance();
}

size_t AccountProxy::id() const
{
    return _model->id();
}

bool AccountProxy::isPaymentAccount() const
{
    return _model->isPaymentAccount();
}

void AccountProxy::addCard(ICard* card)
{
    _model->addCard(card);
    Storage::getInstance().commitAccount(_model);
}

const ICard* AccountProxy::getCard(const std::array<unsigned char, 7> &id) const
{
    return new CardProxy(*dynamic_cast<CardModel*>(_model->getCard(id)));
}

ICard* AccountProxy::getCard(const std::array<unsigned char, 7> &id)
{
    return new CardProxy(*dynamic_cast<CardModel*>(_model->getCard(id)));
}

void AccountProxy::removeCard(const std::array<unsigned char, 7> &cardNum)
{
    _model->removeCard(cardNum);
    Storage::getInstance().commitAccount(_model);
}

const std::vector<ICard*> AccountProxy::cards() const
{
    // Todo delete
    std::vector<ICard*> proxyCards;
    std::vector<ICard*> modelCards = _model->cards();
    for (std::vector<ICard*>::iterator itor = modelCards.begin(); itor != modelCards.end(); itor++)
    {
        proxyCards.push_back(new CardProxy(*dynamic_cast<CardModel*>(*itor)));
    }

    return proxyCards;
}

const std::vector<const ITransaction*> AccountProxy::transactions() const
{
    return _model->transactions();
}

void AccountProxy::addTransaction(const ITransaction *tr)
{
    _model->addTransaction(tr);
    Storage::getInstance().commitAccount(_model);
}

const ITransaction* AccountProxy::getTransaction(const size_t id) const
{
    return _model->getTransaction(id);
}

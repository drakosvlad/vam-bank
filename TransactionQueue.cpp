#include "TransactionQueue.h"
#include "Storage.h"

TransactionQueue* TransactionQueue::_instance = nullptr;

TransactionQueue& TransactionQueue::getInstance()
{
    if (_instance == nullptr)
        _instance = new TransactionQueue();

    return *_instance;
}

TransactionQueue::~TransactionQueue()
{

}

const TransactionQueue::TransactionStub TransactionQueue::removeTransaction()
{
    TransactionStub stub = _queue[0];
    _queue.pop_front();
    return stub;
}

void TransactionQueue::receiveTransaction(IAccount& fromAccount, IAccount& toAccount, int amount, size_t transactionId)
{
    TransactionStub stub {
        fromAccount,
        toAccount,
        amount,
        transactionId
    };

    _queue.push_back(stub);
}

TransactionStatus TransactionQueue::getTransactionStatus(size_t transactionId)
{
    ITransaction* transaction = Storage::getInstance().getTransaction(transactionId);
    if (transaction != nullptr)
        return transaction->getSuccess() ? TransactionStatus::Succeeded : TransactionStatus::Failed;
    return TransactionStatus::Pending;
}

bool TransactionQueue::transactionAvailable()
{
    return _queue.size() > 0;
}

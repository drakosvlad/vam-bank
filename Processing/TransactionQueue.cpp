#include "TransactionQueue.h"

#include <Database/Storage.h>
#include <Transaction/ITransaction.h>

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

const TransactionStub TransactionQueue::removeTransaction()
{
    _semaphore.lock();
    TransactionStub stub = _queue[0];
    _queue.pop_front();
    _semaphore.unlock();
    return stub;
}

void TransactionQueue::receiveTransaction(IAccount* fromAccount, IAccount* toAccount, int amount, unsigned int transactionId)
{
    TransactionStub stub {
        *fromAccount,
        *toAccount,
        amount,
        transactionId
    };

    _semaphore.lock();
    _queue.push_back(stub);
    _semaphore.unlock();
}

TransactionStatus TransactionQueue::getTransactionStatus(size_t transactionId)
{
    const ITransaction* transaction = Storage::getInstance().getTransaction(transactionId);
    if (transaction != nullptr)
        return transaction->getSuccess() ? TransactionStatus::Succeeded : TransactionStatus::Failed;
    return TransactionStatus::Pending;
}

bool TransactionQueue::transactionAvailable()
{
    size_t size = _queue.size();
    return size > 0;
}

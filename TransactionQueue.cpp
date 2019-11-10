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

const TransactionStub TransactionQueue::removeTransaction()
{
    _semaphore.acquire();
    TransactionStub stub = _queue[0];
    _queue.pop_front();
    _semaphore.release();
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

    _semaphore.acquire();
    _queue.push_back(stub);
    _semaphore.release();
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
    _semaphore.acquire();
    size_t size = _queue.size();
    _semaphore.release();
    return size > 0;
}

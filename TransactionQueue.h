#pragma once
#include <deque>
#include <QObject>
#include <QSemaphore>
#include "IAccount.h"

enum TransactionStatus {
    Pending,
    Succeeded,
    Failed
};

struct TransactionStub {
    IAccount& _from;
    IAccount& _to;
    int _amount;
    size_t _transactionId;
};

/**
 * @brief Represents a thread-safe transaction queue
 *
 * Implements a Singleton pattern
 */
class TransactionQueue : public QObject
{
    Q_OBJECT
private:
    TransactionQueue() {  }
    QSemaphore _semaphore;
    std::deque<const TransactionStub> _queue;

    static TransactionQueue* _instance;
public:
    static TransactionQueue& getInstance();
    ~TransactionQueue();
    TransactionQueue(const TransactionQueue &) = delete;
    TransactionQueue& operator=(const TransactionQueue &) = delete;

    bool transactionAvailable();
    const TransactionStub removeTransaction();
    TransactionStatus getTransactionStatus(size_t transactionId);

public slots:
    void receiveTransaction(IAccount& fromAccount, IAccount& toAccount, int amount, size_t transactionId);
};

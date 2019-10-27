#pragma once
#include <deque>
#include <QSemaphore>
#include "IAccount.h"

/**
 * @brief Singleton class that represents a thread-safe transaction queue
 */
class TransactionQueue
{
private:
    TransactionQueue() {  }

    QSemaphore _semaphore;
    /**
     * @brief Queue containing source and target account ids and amount
     */
    std::deque<std::pair<std::pair<size_t, size_t>, int>> _queue;

    TransactionQueue* _instance = nullptr;
public:
    TransactionQueue& getInstance();
    ~TransactionQueue();
    TransactionQueue(const TransactionQueue &) = delete;
    TransactionQueue& operator=(const TransactionQueue &) = delete;

    void addTransaction(const size_t fromId, const size_t toId, const int amount);
    std::pair<std::pair<size_t, size_t>, int> removeTransaction();
};

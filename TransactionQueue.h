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
     * @brief Queue containing source and target account ids
     */
    std::deque<std::pair<size_t, size_t>> _queue;
public:

};

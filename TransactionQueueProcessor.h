#pragma once

#include <QThread>

/**
 * @brief Asynchronously processes transactions queue
 */
class TransactionQueueProcessor : public QThread
{
    Q_OBJECT
private:
    TransactionQueueProcessor();
    void run() override;
public:
    TransactionQueueProcessor(QObject* parent = nullptr);
    ~TransactionQueueProcessor() override;
    TransactionQueueProcessor(const TransactionQueueProcessor&) = delete;
    TransactionQueueProcessor& operator=(const TransactionQueueProcessor&) = delete;
};

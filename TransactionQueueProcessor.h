#pragma once
#include <QThread>

/**
 * @brief Class that asynchronously processes transactions queue
 */
class TransactionQueueProcessor : public QThread
{
    Q_OBJECT
private:
    void run() override;


};

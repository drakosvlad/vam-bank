#pragma once
#include <QThread>

/**
 * @brief Class that asynchronously processes transactions queue
 */
class QueueProcessor : public QThread
{
    Q_OBJECT
private:
    void run() override;


};

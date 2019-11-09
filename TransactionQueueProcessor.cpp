#include "TransactionQueueProcessor.h"
#include "TransactionQueue.h"
#include "IAccount.h"
#include "TransactionModel.h"
#include "Storage.h"
#include <QDebug>
#include <QDateTime>

TransactionQueueProcessor::TransactionQueueProcessor(QObject* parent) : QThread(parent)
{

}

TransactionQueueProcessor::~TransactionQueueProcessor()
{

}

void TransactionQueueProcessor::run()
{
    while (true)
    {
        if (!TransactionQueue::getInstance().transactionAvailable())
        {
            sleep(20);
            continue;
        }

        bool success = true;
        const TransactionStub transaction = TransactionQueue::getInstance().removeTransaction();
        try
        {
            transaction._from.transfer(transaction._to, transaction._amount);
        }
        catch (const TransferError& error)
        {
            qDebug() << error;
            success = false;
        }

        ITransaction* transactionModel = new TransactionModel(transaction._from,
                                                         transaction._to,
                                                         transaction._amount,
                                                         success,
                                                         QDateTime::currentDateTime(),
                                                         QDateTime::currentDateTime());
        Storage::getInstance().addTransaction(transactionModel);
    }
}

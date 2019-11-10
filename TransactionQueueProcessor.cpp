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
            //qDebug() << "No transactions";
            msleep(20);
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

        ITransaction* transactionModel = new TransactionModel(transaction._transactionId,
                                                              transaction._from,
                                                             transaction._to,
                                                             transaction._amount,
                                                             success,
                                                             QDateTime::currentDateTime(),
                                                             QDateTime::currentDateTime());

        transaction._from.addTransaction(transactionModel);
        transaction._to.addTransaction(transactionModel);
        qDebug() << "Success";
    }
}

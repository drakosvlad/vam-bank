#include "TransactionQueueProcessor.h"

#include <QDebug>
#include <QDateTime>

#include "TransactionQueue.h"
#include <Account/IAccount.h>
#include <Database/Storage.h>
#include <Transaction/TransactionModel.h>


TransactionQueueProcessor::TransactionQueueProcessor(QObject* parent) : QThread(parent)
{

}

TransactionQueueProcessor::~TransactionQueueProcessor()
{

}

void TransactionQueueProcessor::run()
{
    while (_go)
    {
        if (!TransactionQueue::getInstance().transactionAvailable())
        {
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
            qDebug() << QString("Error transferring %1 UAH from %2 to %3:").arg(QString::number(transaction._amount / 100),
                                                                        QString::number(transaction._from.id()),
                                                                        QString::number(transaction._to.id()))
                     << error;
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
        if (success)
            qDebug() << QString("Transferred %1 UAH from %2 to %3").arg(QString::number(transaction._amount / 100),
                                                                        QString::number(transaction._from.id()),
                                                                        QString::number(transaction._to.id()));
    }
}

void TransactionQueueProcessor::stopProcessing()
{
    _go = false;
}

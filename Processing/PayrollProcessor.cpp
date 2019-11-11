#include <QDate>

#include "PayrollProcessor.h"
#include "TransactionQueue.h"
#include <Database/Storage.h>
#include <User/UserProxy.h>

PayrollProcessor::PayrollProcessor(QObject* parent) : QThread(parent)
{

}

PayrollProcessor::~PayrollProcessor()
{

}

void PayrollProcessor::run()
{
    while(_go)
    {
        for (IUser* user : Storage::getInstance()._users)
        {
            if (user->getLogin() == "admin")
                continue;

            for (IAccount* acc : user->accounts())
            {
                if (acc->payrollDate().daysTo(QDate::currentDate()) > 30)
                {
                    int fee = acc->payroll();
                    if (fee > 0)
                    {
                        TransactionQueue::getInstance().receiveTransaction(acc, Storage::getInstance().getAccount(0), fee, Storage::getNextTransactionId());
                    }
                    else if (fee < 0)
                    {
                        TransactionQueue::getInstance().receiveTransaction(Storage::getInstance().getAccount(0), acc, -fee, Storage::getNextTransactionId());
                    }
                }
            }
        }

        sleep(3600 * 24);
    }
}

void PayrollProcessor::stopProcessing()
{
    _go = false;
}

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "Database/Storage.h"
#include "Processing/TransactionQueueProcessor.h"
#include "Processing/PayrollProcessor.h"
#include "Processing/TerminalConnector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Storage::getInstance().init();

    TransactionQueueProcessor pr;
    pr.start();

    PayrollProcessor pp;
    pp.start();

    //TerminalConnector tc("/dev/cu.HC-06-SPPDev", *Storage::getInstance().getAccount(5));
    //tc.start();

    w.show();
    auto code = a.exec();

    // Finishing threads
    pr.stopProcessing();
    pr.wait();

    pp.stopProcessing();
    pp.wait();

    //tc.stopProcessing();
    //tc.wait();

    return code;
}

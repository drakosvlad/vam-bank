#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "Database/Storage.h"
#include "Processing/TransactionQueueProcessor.h"
#include "Processing/PayrollProcessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Storage::getInstance().init();

    TransactionQueueProcessor pr;
    pr.start();

    PayrollProcessor pp;
    pp.start();

    w.show();
    auto code = a.exec();

    // Finishing threads
    pr.stopProcessing();
    pr.wait();

    pp.stopProcessing();
    pp.wait();

    return code;
}

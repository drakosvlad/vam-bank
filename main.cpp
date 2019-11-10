#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "Storage.h"
#include "TransactionQueueProcessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    TransactionQueueProcessor pr;
    pr.start();

    w.show();
    auto code = a.exec();

    // Finishing threads
    pr.stopProcessing();
    pr.wait();

    return code;
}

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "Storage.h"
#include "TransactionQueueProcessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Storage::getInstance();

    Storage::getInstance();

    TransactionQueueProcessor pr;
    pr.start();

    w.show();
    return a.exec();
}

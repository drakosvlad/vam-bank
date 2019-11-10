#include "mainwindow.h"
#include <QApplication>
#include "Storage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Storage::getInstance();
    w.show();
    return a.exec();
}

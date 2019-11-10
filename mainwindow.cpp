#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_signinview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_B_clicked()
{
    this->hide();
   // ui->congratulation_GB->hide();
    signInView=new signinview(this);
    signInView->show();
}



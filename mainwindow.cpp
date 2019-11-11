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
    //this->hide();
    signInView = new SignInView(this);
    signInView->show();
}



#include "mainwindow.h"
#include "signinview.h"
#include "mainmenuview.h"
#include "ui_mainwindow.h"

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
    mainMenuView=new MainMenuView(this);
    mainMenuView->show();
}



#include "signinview.h"
#include "ui_signinview.h"
#include <QMessageBox>

signinview::signinview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signinview)
{
    ui->setupUi(this);
}

signinview::~signinview()
{
    delete ui;
}

void signinview::on_signIn_B_clicked()
{

    QString username = ui->username_TB->text();
    QString password = ui->username_TB->text();

    if(isCorrectCredentials(username,password))
    {
        QMessageBox::information(this, "Login", "Succesffull sign in for user "+ username);
        //TODO: click to mainWindow;

        acountList = new acountlistview(*this,this);
        acountList->show();
        this->hide();

    } else
    {
        QMessageBox::information(this, "Error", "User "+ username+ " was not found");
    }


}

bool signinview::isCorrectCredentials(QString username, QString password)
{
     //TODO: connection to database, check if user exists
    return true;
}




/*#include "signinview.h"
#include "ui_signinview.h"
#include <QMessageBox>

SignInVIew::SignInVIew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInVIew)
{
    ui->setupUi(this);
     ui->signIn_group->hide();
}

SignInVIew::~SignInVIew()
{
    delete ui;
}

void SignInVIew::on_pushButton_clicked()
{

}

void SignInVIew::on_signIn_B_clicked()
{

    QString username = ui->username_TB->text();
    QString password = ui->username_TB->text();
    if(isCorrectCredentials(username,password))
    {
        QMessageBox::information(this, "Login", "Succesffull sign in for user "+ username);
        //TODO: click to mainWindow;
        ui->signIn_group->hide();

    } else
    {
        QMessageBox::information(this, "Error", "User "+ username+ " was not found");
    }


}

bool SignInVIew::isCorrectCredentials(QString username, QString password)
{
     //TODO: connection to database, check if user exists
    return true;
}

void SignInVIew::on_signUP_B_clicked()
{
    //TODO: create new Account window
    //TODO: connection to database.
}
*/

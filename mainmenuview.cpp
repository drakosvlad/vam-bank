#include "mainmenuview.h"
#include "ui_mainmenuview.h"
#include <stdio.h>
#include <ctype.h>
#include <QMessageBox>
#include <QLineEdit>
using namespace std;
MainMenuView::MainMenuView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenuView)
{
    ui->setupUi(this);
    ui->recipient_TB->setMaxLength(16);
    ui->PropertiesMenu->hide();
    ui->WidthdrawMoney_group->hide();
    ui->TransferMoney_group->hide();
    ui->General_Info->hide();
}

MainMenuView::~MainMenuView()
{
    delete ui;
}

void MainMenuView::on_transfer_B_clicked()
{
   //TODO : connection to DB to get user`s list of accounts;
    QString strSum =ui->TrnsfSum_TB->text();
    QString strAccontToTranfer = ui->recipient_TB->text();
    if(strSum.isEmpty()||strAccontToTranfer.isEmpty())
    {
        QMessageBox::information(this, "Transfer error", "Input all fields!");
        return;
    }
    int sum = strSum.toInt();
    if(sum==0)
    {
         QMessageBox::information(this, "Transfer error", "Sum files is incorrect!");
         ui->TrnsfSum_TB->setText("");
         return;
    }

    std::string accountToTranfer = strAccontToTranfer.QString::toStdString();
    if(strAccontToTranfer.length()!=16||(!isCorrectRecipientsCard(accountToTranfer)))
    {
         QMessageBox::information(this, "Transfer error", "Recipeint`s card is incorrect!");
         ui->recipient_TB->setText("");
         return;
    }

    //TODO: connection to DB, check is current`s card money is enough and transfer
     ui->recipient_TB->setText("");
     ui->TrnsfSum_TB->setText("");
      QMessageBox::information(this, "Succesffull", "Operation succesfull!");
}

bool MainMenuView::isCorrectRecipientsCard(const std::string &cardNumber)
{
    for(size_t i =0; i<cardNumber.length();i++)
        if(!isdigit(cardNumber[i]))
            return false;
    return true;
}



void MainMenuView::on_widthdraw_B_clicked()
{
    //TODO : connection to DB to get user`s list of accounts;
     QString strSum =ui->WthdSum_TB->text();

     int sum = strSum.toInt();
     if(sum==0)
     {
          QMessageBox::information(this, "Transfer error", "Sum files is incorrect!");
          ui->WthdSum_TB->setText("");
          return;
     }

     //TODO: connection to DB, check is current`s card money is enough and transfer

      ui->WthdSum_TB->setText("");
       QMessageBox::information(this, "Succesffull", "Operation succesfull!");

}
/*-----------------------------------Sign in part----------------------------------------------------*/

void MainMenuView::on_signIn_B_clicked()
{

    QString username = ui->username_TB->text();
    QString password = ui->username_TB->text();
    if(isCorrectCredentials(username,password))
    {
        QMessageBox::information(this, "Login", "Succesffull sign in for user "+ username);
        //TODO: click to mainWindow;
        ui->signIn_group->hide();
        ui->PropertiesMenu->show();
        ui->WidthdrawMoney_group->show();
        ui->TransferMoney_group->show();
        ui->General_Info->show();
        ui->username_TB->setText("");
        ui->username_TB->setText("");

    } else
    {
        QMessageBox::information(this, "Error", "User "+ username+ " was not found");
    }


}

bool MainMenuView::isCorrectCredentials(QString username, QString password)
{
     //TODO: connection to database, check if user exists
    return true;
}

void MainMenuView::on_signUP_B_clicked()
{
    //TODO: create new Account window
    //TODO: connection to database.
}


void MainMenuView::on_signOut_B_clicked()
{
    ui->signIn_group->show();
    ui->PropertiesMenu->hide();
    ui->WidthdrawMoney_group->hide();
    ui->TransferMoney_group->hide();
    ui->General_Info->hide();
}

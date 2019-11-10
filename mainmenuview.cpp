#include "mainmenuview.h"
#include "ui_mainmenuview.h"

#include "acountlistview.h"

#include <stdio.h>
#include <ctype.h>
#include <QMessageBox>
#include <QLineEdit>

using namespace std;


MainMenuView::MainMenuView(acountlistview & acount,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenuView),acountList(acount)
{
    //TODO: change to db name and surname;
    ui->setupUi(this);
   // ui->recipient_TB->setMaxLength(16);
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

void MainMenuView::on_signOut_B_clicked()
{
    acountList.show();
    this->close();
}

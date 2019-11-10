#include "mainmenuview.h"
#include "ui_mainmenuview.h"

#include "acountlistview.h"

#include <stdio.h>
#include <ctype.h>
#include <QMessageBox>
#include <QLineEdit>

#include "TransactionQueue.h"
#include "ITransaction.h"
#include "IAccount.h"

using namespace std;


MainMenuView::MainMenuView(acountlistview & acount, IAccount* account, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenuView),acountList(acount),
    selectedAccount(account)
{
    ui->setupUi(this);
    ui->balance_label->setText(QString::number(selectedAccount->balance())+"UAH");
    ui->acoundId_label->setText(QString::number(selectedAccount->id()));
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
    //TransactionQueue::getInstance().receiveTransaction()

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

void MainMenuView::on_refreshButton_B_clicked()
{
    ui->balance_label->setText(QString::number(selectedAccount->balance())+"UAH");
    const std::vector<const ITransaction*> history =  selectedAccount->transactions();

    for(std::vector<const ITransaction*>::const_iterator itor = history.begin(); itor != history.end(); ++itor)
    {
        ui->transactionList_List->addItem(QString("From:")+ (*itor)->getSender().getAccountName()+ " to: "+(*itor)->getReciever().getAccountName()
                                          + QString::number((*itor)->getAmount())
                                          + QString("status : ")+QString::number((*itor)->getSuccess()));

    }

}

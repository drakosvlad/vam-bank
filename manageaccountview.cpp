#include "manageaccountview.h"
#include "ui_manageaccountview.h"

#include <QMessageBox>
#include <QLineEdit>

#include "mainpageview.h"
#include "Account/IAccount.h"
#include "Database/Storage.h"
#include "Processing/TransactionQueue.h"
#include "Transaction/ITransaction.h"

using namespace std;


ManageAccountView::ManageAccountView(MainPageView & acount, IAccount* account, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageAccountView),acountList(acount),
    selectedAccount(account)
{
    ui->setupUi(this);
    ui->acoundId_label->setText(QString::number(selectedAccount->id()));

    updateTransactions();
}

ManageAccountView::~ManageAccountView()
{
    delete ui;
}

void ManageAccountView::on_transfer_B_clicked()
{
    QString strSum = ui->TrnsfSum_TB->text();
    QString strAccontToTranfer = ui->recipient_TB->text();
    if(strSum.isEmpty() || strAccontToTranfer.isEmpty())
    {
        QMessageBox::information(this, "Transfer error", "Input all fields!");
        return;
    }

    int amount = strSum.toInt();

    if(amount <= 0)
    {
         QMessageBox::information(this, "Transfer error", "Invalid amount!");
         ui->TrnsfSum_TB->setText("");
         return;
    }

    size_t toId = strAccontToTranfer.toUInt();
    auto toAccount = Storage::getInstance().getAccount(toId);

    if (toAccount == nullptr)
    {
        QMessageBox::information(this, "Transfrt error", "Recipient account was not found!");
        return;
    }

    TransactionQueue::getInstance().receiveTransaction(selectedAccount,
                                                       toAccount,
                                                       amount * 100,
                                                       static_cast<unsigned int>(Storage::getNextTransactionId()));

    ui->recipient_TB->setText("");
    ui->TrnsfSum_TB->setText("");
    QMessageBox::information(this, "Pending", "Operation was sent to processing");
}

bool ManageAccountView::isCorrectRecipientsCard(const std::string &cardNumber)
{
    for(size_t i =0; i<cardNumber.length();i++)
        if(!isdigit(cardNumber[i]))
            return false;
    return true;
}


void ManageAccountView::updateTransactions()
{
    ui->balance_label->setText(QString::number(selectedAccount->balance() / 100) +"UAH");
    const std::vector<const ITransaction*> history = selectedAccount->transactions();
    ui->transactionList_List->clear();
    for(std::vector<const ITransaction*>::const_iterator itor = history.begin(); itor != history.end(); ++itor)
    {
        ui->transactionList_List->addItem(QString("%3 UAH from %1 to %2 - %4").arg((*itor)->getSender().getAccountName(),
                                                                                   (*itor)->getReciever().getAccountName(),
                                                                                   QString::number((*itor)->getAmount() / 100),
                                                                                   ((*itor)->getSuccess() ? "succeeded" : "failed")));
    }

}

void ManageAccountView::on_widthdraw_B_clicked()
{
    //TODO : connection to DB to get user`s list of accounts;
     QString strSum =ui->WthdSum_TB->text();

     int amount = strSum.toInt();
     if(amount <= 0)
     {
          QMessageBox::information(this, "Transfer error", "Sum files is incorrect!");
          ui->WthdSum_TB->setText("");
          return;
     }

     TransactionQueue::getInstance().receiveTransaction(selectedAccount,
                                                        Storage::getInstance().getAccount(0),
                                                        amount * 100,
                                                        static_cast<unsigned int>(Storage::getNextTransactionId()));

     ui->WthdSum_TB->setText("");
     QMessageBox::information(this, "Pending", "Operation was sent to procesing");
}

void ManageAccountView::on_signOut_B_clicked()
{
    acountList.refreshAccountsList();
    acountList.show();
    this->close();
}

void ManageAccountView::on_refreshButton_B_clicked()
{
    updateTransactions();
}

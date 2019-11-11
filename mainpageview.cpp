#include "mainpageview.h"
#include "ui_mainpageview.h"

#include <QMessageBox>

#include "signinview.h"
#include "mainpageview.h"
#include "Account/DebitAccount.h"
#include "Account/SavingsAccount.h"
#include "Account/CreditAccount.h"
#include "Database/Storage.h"
#include "User/IUser.h"

MainPageView::MainPageView(SignInView & signIn,IUser & user, QWidget *parent) :
    QDialog(parent), ui(new Ui::MainPageView),
    signInView(signIn),_user(user)
{
    ui->setupUi(this);
    refreshAccountsList();

    ui->setName_L->setText(QString::fromStdString(_user.getFirstName()));
    ui->setSurname_L->setText(QString::fromStdString(_user.getLastName()));
    ui->accountList_B->addItem("Debit");
    ui->accountList_B->addItem("Credit");
    ui->accountList_B->addItem("Saving");
}

void MainPageView::refreshAccountsList()
{
    std::vector<IAccount*> accounts = _user.accounts();
    ui->acountList_CB->clear();
    for (std::vector<IAccount*>::iterator itor = accounts.begin(); itor != accounts.end(); ++itor)
    {
        ui->acountList_CB->addItem((*itor)->getAccountName()+ ": " +  QString::number((*itor)->id()) + " - " + QString::number((*itor)->balance()/100) + "UAH");
    }
}

MainPageView::~MainPageView()
{
    delete ui;
}

void MainPageView::on_pushButton_clicked()
{
    signInView.show();
    this->close();
}

void MainPageView::on_manageButton_clicked()
{
    std::vector<IAccount*> accounts = _user.accounts();
    mainMenu = new ManageAccountView(*this, accounts[static_cast<size_t>(ui->acountList_CB->currentIndex())], this);
    mainMenu->show();
    this->hide();
}

void MainPageView::on_addAccount_B_clicked()
{
    std::string type = ui->accountList_B->currentText().toLocal8Bit().constData();
    if (type.compare("Debit") == 0)
    {
        auto account = new DebitAccount(&_user,0, QDate::currentDate(), QDate::currentDate(), 0, Storage::getInstance().getNextAccountId());
        _user.addAccount(account);
        QMessageBox::information(this, "202", "Successfully added ");
    }
    else  if (type.compare("Credit") == 0)
    {
        auto account = new CreditAccount(&_user,100000,QDate::currentDate(), QDate::currentDate(), 100000,  Storage::getInstance().getNextAccountId());
         _user.addAccount(account);
         QMessageBox::information(this, "202", "Successfully added ");
    }
    else if (type.compare("Saving") == 0)
    {
        auto account = new SavingsAccount(&_user, 0 ,QDate::currentDate(), QDate::currentDate(), 0,  Storage::getInstance().getNextAccountId());
         _user.addAccount(account);
         QMessageBox::information(this, "202", "Successfully added ");
    }

    refreshAccountsList();
}

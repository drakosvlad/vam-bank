#include "acountlistview.h"
#include "ui_acountlistview.h"
#include "signinview.h"
#include "Storage.h"

acountlistview::acountlistview(signinview & signIn,IUser & user, QWidget *parent) :
    QDialog(parent),ui(new Ui::acountlistview),
    signInView(signIn),_user(user)
{

    std::vector<IAccount*> accounts = _user.accounts();

    ui->setupUi(this);
    for (std::vector<IAccount*>::iterator itor = accounts.begin(); itor != accounts.end(); ++itor)
    {
        ui->acountList_CB->addItem(QString::number((*itor)->id()) + " - " + QString::number((*itor)->balance()/10) + "UAH");
    }


    ui->setName_L->setText("TEXT");
    ui->setSurname_L->setText("TEXT");
}

acountlistview::~acountlistview()
{
    delete ui;
}

void acountlistview::on_pushButton_clicked()
{
    signInView.show();
    this->close();
}

void acountlistview::on_manageButton_clicked()
{

    mainMenu = new MainMenuView(*this,this);
    mainMenu->show();
    this->hide();

}

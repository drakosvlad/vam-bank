#include "signinview.h"
#include "ui_signinview.h"
#include <QMessageBox>
#include "Storage.h"
#include "IUser.h"


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
    const std::string login = ui->username_TB->text().toLocal8Bit().constData();
    const std::string password =  ui->password_TB->text().toLocal8Bit().constData();
    user = Storage::getInstance().getUser(login);
    if(isCorrectCredentials(login,password))
    {
        QMessageBox::information(this, "Login", "Succesffull sign in for user ");
        acountList = new acountlistview(*this,*user,this);
        acountList->show();
        this->hide();
    } else
    {
        QMessageBox::information(this, "Error", "User was not found");
        return;
    }
}

bool signinview::isCorrectCredentials(const std::string &username, const std::string &password)
{

 if (user->getLogin().compare(username) != 0)
     return false;
 if (user->getPassword().compare(password) != 0)
     return false;

   return true;
}




#include "signinview.h"
#include "ui_signinview.h"

#include <QMessageBox>
#include "Database/Storage.h"
#include "User/IUser.h"


SignInView::SignInView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInView)
{
    ui->setupUi(this);
}

SignInView::~SignInView()
{
    delete ui;
}

void SignInView::on_signIn_B_clicked()
{
    const std::string login = ui->username_TB->text().toLocal8Bit().constData();
    const std::string password =  ui->password_TB->text().toLocal8Bit().constData();
    user = Storage::getInstance().getUser(login);
    if (user != nullptr && isCorrectCredentials(login,password))
    {
        QMessageBox::information(this, "Login", "Successful sign in for user ");
        acountList = new MainPageView(*this,*user,this);
        acountList->show();
        this->hide();
    }
    else
    {
        QMessageBox::information(this, "Error", "User was not found");
        return;
    }
}

bool SignInView::isCorrectCredentials(const std::string &username, const std::string &password)
{

    if (user->getLogin().compare(username) != 0)
        return false;
    if (user->getPassword().compare(password) != 0)
        return false;
    return true;
}




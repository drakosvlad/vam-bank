#pragma once

#ifndef SIGNINVIEW_H
#define SIGNINVIEW_H
#include <QDialog>

#include "manageaccountview.h"
#include "mainpageview.h"

class IUser;

namespace Ui
{
    class SignInView;
}

class SignInView : public QDialog
{
    Q_OBJECT

public:
    explicit SignInView(QWidget *parent = nullptr);
    ~SignInView();

private slots:
    void on_signIn_B_clicked();

private:
    Ui::SignInView *ui;
    bool isCorrectCredentials(const std::string&, const std::string&);
    ManageAccountView *mainMenu;
    MainPageView * acountList;
    IUser *user;
};

#endif // SIGNINVIEW_H

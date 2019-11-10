#pragma once
#ifndef SIGNINVIEW_H
#define SIGNINVIEW_H
#include <QDialog>
#include "mainmenuview.h"
#include "acountlistview.h"
namespace Ui {
class signinview;
}

class signinview : public QDialog
{
    Q_OBJECT

public:
    explicit signinview(QWidget *parent = nullptr);
    ~signinview();
private slots:
        void on_signIn_B_clicked();
private:
    Ui::signinview *ui;
    bool isCorrectCredentials(QString, QString);
    MainMenuView *mainMenu;
    acountlistview * acountList;

};

#endif // SIGNINVIEW_H

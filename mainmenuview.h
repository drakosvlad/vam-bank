#pragma once
#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H
#include <QDialog>

class signinview;
class acountlistview;;

namespace Ui {
class MainMenuView;
}

class MainMenuView : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenuView(acountlistview &, QWidget *parent = nullptr);
    ~MainMenuView();

private slots:
//Main menu part
    void on_transfer_B_clicked();
    void on_widthdraw_B_clicked();

    void on_signOut_B_clicked();

private:
    Ui::MainMenuView *ui;
    bool isCorrectRecipientsCard(const std::string&);
    acountlistview &acountList;
};

#endif // MAINMENUVIEW_H





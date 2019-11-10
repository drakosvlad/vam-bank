#ifndef ACOUNTLISTVIEW_H
#define ACOUNTLISTVIEW_H

#include <QDialog>
class signinview;
class MainMenuView;
class IUser;
namespace Ui {
class acountlistview;
}

class acountlistview : public QDialog
{
    Q_OBJECT

public:
    explicit acountlistview(signinview &,IUser &, QWidget *parent = nullptr);
    ~acountlistview();
    void refreshAccountsList();
private slots:
    void on_pushButton_clicked();

    void on_manageButton_clicked();

    void on_addAccount_B_clicked();
private:
    Ui::acountlistview *ui;
    signinview &signInView;
    IUser &_user;
    MainMenuView *mainMenu;

};

#endif // ACOUNTLISTVIEW_H

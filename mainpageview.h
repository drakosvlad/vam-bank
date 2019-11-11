#ifndef ACOUNTLISTVIEW_H
#define ACOUNTLISTVIEW_H

#include <QDialog>

class SignInView;
class ManageAccountView;
class IUser;

namespace Ui
{
    class MainPageView;
}

class MainPageView : public QDialog
{
    Q_OBJECT

public:
    explicit MainPageView(SignInView &,IUser &, QWidget *parent = nullptr);
    ~MainPageView();
    void refreshAccountsList();

private slots:
    void on_pushButton_clicked();
    void on_manageButton_clicked();
    void on_addAccount_B_clicked();

private:
    Ui::MainPageView *ui;
    SignInView &signInView;
    IUser &_user;
    ManageAccountView *mainMenu;
};

#endif // ACOUNTLISTVIEW_H

#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QDialog>

class SignInView;
class MainPageView;
class IAccount;

namespace Ui
{
    class ManageAccountView;
}

class ManageAccountView : public QDialog
{
    Q_OBJECT

public:
    explicit ManageAccountView(MainPageView &, IAccount * acc, QWidget *parent = nullptr);
    ~ManageAccountView();

private slots:
    void on_transfer_B_clicked();
    void on_widthdraw_B_clicked();
    void on_signOut_B_clicked();
    void on_refreshButton_B_clicked();

private:
    Ui::ManageAccountView *ui;
    bool isCorrectRecipientsCard(const std::string&);
    MainPageView &acountList;
    IAccount* selectedAccount;
    void  updateTransactions();
};

#endif // MAINMENUVIEW_H

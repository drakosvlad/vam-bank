#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QDialog>

namespace Ui {
class MainMenuView;
}

class MainMenuView : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenuView(QWidget *parent = nullptr);
    ~MainMenuView();

private slots:
//Main menu part
    void on_transfer_B_clicked();
    void on_widthdraw_B_clicked();

//Sign in part
    void on_signIn_B_clicked();
    void on_signUP_B_clicked();
    void on_signOut_B_clicked();

private:
    Ui::MainMenuView *ui;
    bool isCorrectRecipientsCard(const std::string&);
    bool isCorrectCredentials(QString, QString );
};

#endif // MAINMENUVIEW_H





#ifndef ACOUNTLISTVIEW_H
#define ACOUNTLISTVIEW_H

#include <QDialog>
class signinview;
class MainMenuView;
namespace Ui {
class acountlistview;
}

class acountlistview : public QDialog
{
    Q_OBJECT

public:
    explicit acountlistview(signinview &, QWidget *parent = nullptr);
    ~acountlistview();

private slots:
    void on_pushButton_clicked();

    void on_manageButton_clicked();

private:
    Ui::acountlistview *ui;
    signinview &signInView;
    MainMenuView *mainMenu;

};

#endif // ACOUNTLISTVIEW_H

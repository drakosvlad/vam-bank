#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signinview.h"
#include "mainmenuview.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
  void on_start_B_clicked();

private:
    Ui::MainWindow *ui;
    //SignInVIew *signInView;
    MainMenuView *mainMenuView;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainmenuview.h"
#include "signinview.h"
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
    signinview *signInView;
};

#endif // MAINWINDOW_H

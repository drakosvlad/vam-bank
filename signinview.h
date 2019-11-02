/*#ifndef SIGNINVIEW_H
#define SIGNINVIEW_H

#include <QDialog>

namespace Ui {
class SignInVIew;
}

class SignInVIew : public QDialog
{
    Q_OBJECT

public:
    explicit SignInVIew(QWidget *parent = nullptr);
    ~SignInVIew();


private slots:
    void on_pushButton_clicked();
    void on_signIn_B_clicked();
    void on_signUP_B_clicked();
private:
    Ui::SignInVIew *ui;
    bool isCorrectCredentials(QString, QString );
};

#endif // SIGNINVIEW_H
*/

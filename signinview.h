#ifndef SIGNINVIEW_H
#define SIGNINVIEW_H

#include <QWidget>

namespace Ui {
class signinview;
}

class signinview : public QWidget
{
    Q_OBJECT

public:
    explicit signinview(QWidget *parent = nullptr);
    ~signinview();

private:
    Ui::signinview *ui;
};

#endif // SIGNINVIEW_H

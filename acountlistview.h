#ifndef ACOUNTLISTVIEW_H
#define ACOUNTLISTVIEW_H

#include <QWidget>

namespace Ui {
class acountlistview;
}

class acountlistview : public QWidget
{
    Q_OBJECT

public:
    explicit acountlistview(QWidget *parent = nullptr);
    ~acountlistview();

private:
    Ui::acountlistview *ui;
};

#endif // ACOUNTLISTVIEW_H

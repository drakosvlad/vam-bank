#include "signinview.h"
#include "ui_signinview.h"

signinview::signinview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signinview)
{
    ui->setupUi(this);
}

signinview::~signinview()
{
    delete ui;
}

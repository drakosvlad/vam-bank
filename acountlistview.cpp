#include "acountlistview.h"
#include "ui_acountlistview.h"

acountlistview::acountlistview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::acountlistview)
{
    ui->setupUi(this);
}

acountlistview::~acountlistview()
{
    delete ui;
}

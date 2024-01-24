#include "confirm.h"
#include "ui_confirm.h"

confirm::confirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::confirm)
{
    ui->setupUi(this);
}

confirm::~confirm()
{
    delete ui;
}

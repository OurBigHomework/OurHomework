#include "registerpart.h"
#include "ui_registerpart.h"

RegisterPart::RegisterPart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterPart)
{
    ui->setupUi(this);
}

RegisterPart::~RegisterPart()
{
    delete ui;
}

#include "loginpart.h"
#include "ui_loginpart.h"

loginPart::loginPart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginPart)
{
    ui->setupUi(this);

}

loginPart::~loginPart()
{
    delete ui;
}

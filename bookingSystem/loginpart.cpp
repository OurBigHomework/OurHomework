#include "loginpart.h"
#include "ui_loginpart.h"

loginPart::loginPart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginPart)
{
    ui->setupUi(this);
    ui->stackedWidget->setFrameShape(QFrame::NoFrame);
    ui->titleText->setFrameShape(QFrame::NoFrame);


}
void loginPart::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush(Qt::white);
    p.drawRect(rect());
}
loginPart::~loginPart()
{
    delete ui;
}

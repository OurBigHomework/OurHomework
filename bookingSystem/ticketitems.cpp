#include "ticketitems.h"
#include<QPalette>
#include<QFont>

ticketItems::ticketItems(QWidget *parent) : QWidget(parent)
{
init();
}
void ticketItems::init()
{

    planeName=new QLabel(this);
    hasTicket=new QLabel(this);
    time=new QLabel(this);
    places=new QLabel(this);

    pic=new QLabel(this);
    pic->setFixedSize(140,110);
    pic->setStyleSheet("QLabel{background-image:url(:/new/prefix1/ticketImg1.jpg);}");
    pic->setScaledContents(true);

    QPalette color1;
    color1.setColor(QPalette::Text,Qt::gray);
    hasTicket->setPalette(color1);


    QPalette color2;
    color2.setColor(QPalette::Text,Qt::black);
    planeName->setPalette(color1);
    time->setPalette(color2);
    QFont f;
    f.setPointSize(16);
    time->setFont(f);
    f.setPointSize(10);
    hasTicket->setFont(f);

    pic->move(10,25);
    time->move(160,30);
    planeName->move(160,80);
    places->move(160,110);
    hasTicket->move(480,50);






}

QString ticketItems::getTime()
{
    return time->text();
}
QString ticketItems::getPlaces()
{
    return places->text();
}
QString ticketItems::getPlaneName()
{
    return  planeName->text();
}
bool ticketItems::hasTicketOrNot()
{
    if(hasTicket->text()=="yes")return true;
    return false;
}
void ticketItems::setTime(QString text)
{
    time->setText(text);
}
void ticketItems::setPlaces(QString text)
{
    places->setText(text);
}
void ticketItems::setPlaneName(QString text)
{
    planeName->setText(text);
}
void ticketItems::setHasTicket(QString text)
{
    hasTicket->setText(text);
}

void ticketItems::mousePressEvent(QMouseEvent *event)
{

dia.show();
}

#include "flightsinformation.h"
#include<QFont>
#include<QPalette>
FlightsInformation::FlightsInformation(QWidget *parent) : QWidget(parent)
{

    date=new QLabel(this);
    time=new QLabel(this);
    bPlace=new QLabel(this);
    ePlace=new QLabel(this);
    QFont font;
    font.setPointSize(12);
    QPalette color;
    color.setColor(QPalette::Text,Qt::gray);
    date->setPalette(color);
    time->setPalette(color);
    bPlace->setPalette(color);
    ePlace->setPalette(color);
    date->setFont(font);
    time->setFont(font);
    bPlace->setFont(font);
    ePlace->setFont(font);
    bPlace->move(20,20);
    ePlace->move(200,20);
    date->move(380,20);
    time->move(520,20);



}

void FlightsInformation::setDate(QString d)
{
    date->setText(d);
}
void FlightsInformation::setbegin(QString bp)
{
    bPlace->setText(bp);
}
void FlightsInformation::setend(QString ep)
{
    ePlace->setText(ep);
}
void FlightsInformation::setTime(QString t)
{
    time->setText(t);
}
//QString FlightsInformation::getDate()
//{
//    return date;
//}
//QString FlightsInformation::getTime()
//{
//    return time;
//}
//QString FlightsInformation::getEndPlace()
//{
//    return ePlace;
//}
//QString FlightsInformation::getBeginPlace()
//{
//    return bPlace;
//}

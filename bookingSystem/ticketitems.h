#ifndef TICKETITEMS_H
#define TICKETITEMS_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
/*
自定义item
*/
class ticketItems : public QWidget
{
    Q_OBJECT
public:
    explicit ticketItems(QWidget *parent = nullptr);
    void init();//初始化UI
    QString getPlaneName();
    QString getPlaces();
    QString getTime();
    int getIndex();
    QString getTicketsNum();
    bool hasTicketOrNot();
    void setPlaneName(QString text);
    void setPlaces(QString text);
    void setHasTicket(QString text);
    void setTime(QString text);
    void setIndex(int i);
    void setTicketsNum(QString t);
    void setCount(QString c);

    void mousePressEvent(QMouseEvent *event) override;


private:

    QLabel *pic;
    QLabel*planeName;
    QLabel*places;
    QLabel*hasTicket;
    QLabel*time;
    QLabel*count;
    int index;
    QString num;


signals:

    void itemClicked(ticketItems*);
};

#endif // TICKETITEMS_H

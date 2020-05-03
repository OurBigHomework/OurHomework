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
    int getRow();
    int getDayIndex();
    QString getTicketsNum();
    bool hasTicketOrNot();
    void setPlaneName(QString text);
    void setPlaces(QString text);
    void setHasTicket(QString text);
    void setTime(QString text);
    void setIndex(int i);
    void setTicketsNum(QString t);
    void setCount(QString c);
    void setRow(int i);
    void setDayIndex(int i);

    void mousePressEvent(QMouseEvent *event) override;


private:

    QLabel *pic;
    QLabel*planeName;
    QLabel*places;
    QLabel*hasTicket;
    QLabel*time;
    QLabel*count;
    int index;
    int row;
    int dayIndex;
    QString num;
    QString day;


signals:

    void itemClicked(ticketItems*);
};

#endif // TICKETITEMS_H

#ifndef TICKETITEMS_H
#define TICKETITEMS_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>

class ticketItems : public QWidget
{
    Q_OBJECT
public:
    explicit ticketItems(QWidget *parent = nullptr);
    void init();
    QString getPlaneName();
    QString getPlaces();
    QString getTime();
    bool hasTicketOrNot();
    void setPlaneName(QString text);
    void setPlaces(QString text);
    void setHasTicket(QString text);
    void setTime(QString text);

private:

    QLabel *pic;
    QLabel*planeName;
    QLabel*places;

    QLabel*hasTicket;
    QLabel*time;


signals:

};

#endif // TICKETITEMS_H
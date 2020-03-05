#ifndef FLIGHTSINFORMATION_H
#define FLIGHTSINFORMATION_H

#include <QWidget>
#include<QLabel>
class FlightsInformation : public QWidget
{
    Q_OBJECT
public:
    explicit FlightsInformation(QWidget *parent = nullptr);
    void setbegin(QString bp);
    void setend(QString ep);
    void setDate(QString d);
    void setTime(QString t);
//    QString getBeginPlace();
//    QString getEndPlace();
//    QString getDate();
//    QString getTime();

signals:

private:
    QLabel* bPlace;
     QLabel* ePlace;
     QLabel* date;
     QLabel* time;

};

#endif // FLIGHTSINFORMATION_H

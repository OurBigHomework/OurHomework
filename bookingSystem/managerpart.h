#ifndef MANAGERPART_H
#define MANAGERPART_H

#include <QWidget>
#include "flightinfodialog.h"
#include "ticketitems.h"

namespace Ui {
class managerPart;
}

class managerPart : public QWidget
{
    Q_OBJECT

public:
    explicit managerPart(QWidget *parent = nullptr);
    FlightInfoDialog dia;
    ~managerPart();
   void showSearchPage(int begin,int end,QString&date, QList<QList<QVariant>>&res);//展示页面
   void getInfo(QList<QList<QList<QVariant>>>&vars);
   void getPlaceAndDate(QVector<QString>&place,QVector<QString>&dates);//获得地点和时间
   void itemClick(ticketItems*it);//设置点击事件

private slots:
    void on_changeHead_clicked();//修改头像

    void on_comeBack_clicked();//返回主界面

    void on_mofInfo_clicked();//修改航班信息

    //void on_newFlights_clicked();

private:
    //QString formateStr(QString &str,int k);
    Ui::managerPart *ui;

    QList<QList<QVariant>> res;
    int line;
signals:
    void comeBack();
    void sendInfo(QList<QList<QList<QVariant>>>&vars);
    //void sendIndex(int i);
};

#endif // MANAGERPART_H

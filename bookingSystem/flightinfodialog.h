#ifndef FLIGHTINFODIALOG_H
#define FLIGHTINFODIALOG_H

#include <QWidget>
#include "myexcel.h"
#include "mythread.h"
#include "threadwritecell.h"
#include <QMetaType>
namespace Ui {
class FlightInfoDialog;
}

class FlightInfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FlightInfoDialog(QWidget *parent = nullptr);
    ~FlightInfoDialog();
    QList<QList<QList<QVariant>>> vars;//三维数组，存储全部的航班信息，如vars【0】【0】【0】表示mydata2第一张表位置为A1的数据
    QVector<QString>dates;//日期
    QVector<QString> places;//地点
    int sheetNum;
    int currentTimeIndex;//修改界面时间在excel表里面的列位置
    int line;//修改的item在excel表里面的行位置
    void changePage(int i);
    int dateCorrect(QString d);
    void dealDone(QList<QList<QList<QVariant>>>&vars);
    void initPlaceAndDate(QVector<QString> &place, QVector<QString> &dates);
    void initChangePage(QString&t,QString&t1,QString&t2,QString&t3);
    void dealWriteOk();

signals:
    void Search(int begin,int end,QString&date, QList<QList<QVariant>>&res);
    void send(QList<QList<QList<QVariant>>>&vars);
private slots:
    //void on_buttonOk_clicked();

    void on_buttonOk_2_clicked();

    void on_buttonChangeYes_clicked();

    void on_returnButton_clicked();

private:
    Ui::FlightInfoDialog *ui;
    myExcel e;
    MyThread*th;
    threadWriteCell w;
    int qq1,qq2;
    QString dd;


};

#endif // FLIGHTINFODIALOG_H

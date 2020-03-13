#ifndef FLIGHTINFODIALOG_H
#define FLIGHTINFODIALOG_H

#include <QWidget>
#include "myexcel.h"
#include "mythread.h"
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
    QList<QList<QList<QVariant>>> vars;
    QVector<QString>dates;
    QVector<QString> places;
    int currentTimeIndex;
    int line;
    void changePage(int i);
    int dateCorrect(QString d);
    void dealDone(QList<QList<QList<QVariant>>>&vars);
    void initPlaceAndDate(QVector<QString> &place, QVector<QString> &dates);
    void initChangePage(QString&t,QString&t1,QString&t2,QString&t3);

signals:
    void Search(int begin,int end,QString&date, QList<QList<QVariant>>&res);
    void send(QList<QList<QList<QVariant>>>&vars);
private slots:
    void on_buttonOk_clicked();

    void on_buttonOk_2_clicked();

    void on_buttonChangeYes_clicked();

private:
    Ui::FlightInfoDialog *ui;
    myExcel e;
    MyThread*th;


};

#endif // FLIGHTINFODIALOG_H

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
    QVector<QString>dates;
    QVector<QString> places;

    void changePage(int i);
    int dateCorrect(QString d);
    void dealDone(QList<QList<QList<QVariant>>>&vars);

signals:
    void Search(int begin,int end,QString&date, QList<QList<QVariant>>&res);
private slots:
    void on_buttonOk_clicked();

    void on_buttonOk_2_clicked();

private:
    Ui::FlightInfoDialog *ui;
    myExcel e;
    MyThread*th;
    QList<QList<QList<QVariant>>> vars;

};

#endif // FLIGHTINFODIALOG_H

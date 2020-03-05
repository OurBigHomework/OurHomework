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
    ~managerPart();
   void showSearchPage(int begin,int end,QString&date, QList<QList<QVariant>>&res);

private slots:
    void on_changeHead_clicked();

    void on_comeBack_clicked();

    void on_mofInfo_clicked();

    void on_newFlights_clicked();

private:
    QString formateStr(QString &str,int k);
    Ui::managerPart *ui;
    FlightInfoDialog dia;
signals:
    void comeBack();
};

#endif // MANAGERPART_H

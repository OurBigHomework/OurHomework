#ifndef LOGINPART_H
#define LOGINPART_H

#include <windows.h>
#include "myexcel.h"
#include <QMainWindow>
#include<QPainter>
#include<QVariantList>
#include <ActiveQt/QAxWidget>
#include<ActiveQt/QAxObject>
#include<QVariant>
#include<QList>
#include "ticketitems.h"
namespace Ui {
class loginPart;
}

class loginPart : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginPart(QWidget *parent = nullptr);
    ~loginPart();
    QAxObject* getWorksheet();
    QString getCalDate();
    void showSearchPage(int begin,int end,QString date,int &time);

protected:
    void paintEvent(QPaintEvent *event);



private slots:
    void on_buttonSearch_clicked();


private:
    Ui::loginPart *ui;
    QList<QList<QVariant>> res;
    myExcel e;
    int timeIndex;



};

#endif // LOGINPART_H

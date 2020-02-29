#ifndef LOGINPART_H
#define LOGINPART_H

#include <windows.h>
#include "myexcel.h"
#include <QMainWindow>
#include<QPainter>
#include<QListWidget>
#include<QListWidgetItem>
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
    //QAxObject* getWorksheet();
    QString getCalDate();//获取出发日期
    void showSearchPage(int begin,int end,QString date,int &time);//展示售票页面
    void deleteItems(QListWidget*list,int count);//删除QListWidget中的item

protected:
    void paintEvent(QPaintEvent *event);




private slots:
    void on_buttonSearch_clicked();


    void on_comeBack_clicked();

private:
    Ui::loginPart *ui;

    QList<QList<QVariant>> res;
    QVector<QString>place;
    myExcel e;
    int timeIndex;
signals:
    void openMainWindow();


};

#endif // LOGINPART_H

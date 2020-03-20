#ifndef LOGINPART_H
#define LOGINPART_H

#include "mythread.h"
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
#include "passenger.h"

namespace Ui {
class loginPart;
}

class loginPart : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginPart(QWidget *parent = nullptr);
    ~loginPart();


    QString getCalDate();//获取出发日期
    void showSearchPage(int begin,int end,QString date);//展示售票页面
    void deleteItems(QListWidget*list,int count);//删除QListWidget中的item
    void setPassenger(QString username,QString password,QString birthday,QString sex,QString name,QString phone,int index);//设置乘客信息
    void sendLoginSignal();//发送登录信号
    void setVars(QList<QList<QList<QVariant>>>& vars);//为vars赋值
   // void senInitSignal();
    void initPersonalInfo();//初始化乘客信息
    void initPlaneInfo(QList<QList<QList<QVariant>>>&vars);//初始化航班信息
    void initDateAndPlace(QList<QList<QList<QVariant>>>&v);//初始化日期和地点
    void itemClick(ticketItems*);//stackedwidget里面item点击事件处理

protected:
    void paintEvent(QPaintEvent *event);//设置背景




private slots:
    void on_buttonSearch_clicked();//点击查询按钮


    void on_comeBack_clicked();//点击返回按钮

    void on_pushButton_2_clicked();

    void on_pushButtonEdit_clicked();//点击编辑按钮

    void on_pushButtonEditOK_clicked();//点击编辑确定按钮

    void on_buttonSearchByPlace_clicked();

private:
    Ui::loginPart *ui;

    //QList<QList<QVariant>> res;
    QVector<QString>place;
    QVector<QString>dates;
    //myExcel e;
    //int timeIndex;
    Passenger passenger;
    QList<QList<QList<QVariant>>> vars;//存储所有航班信息的三维数组
    MyThread *th2;//线程，启动时间和地点的初始化

signals:
    void openMainWindow();
    void initLogin();
    void sendPlaceAndDate(QVector<QString>&place,QVector<QString>&dates);//传递地点和时间数据



};

#endif // LOGINPART_H

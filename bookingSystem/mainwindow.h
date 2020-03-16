#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registerpart.h"
#include "loginpart.h"
#include "managerpart.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool accountExist(QString pword,QString uname,int &index);//判断账号是否存在
    void openAgain();//重新打开主窗口
    //void getInfo(QList<QList<QVariant>>&res,QVector<QString>&d,QVector<QString> &place);
protected:
    void paintEvent(QPaintEvent *event) override;
    void setBackgroundImage(QString path);//设置背景图片

private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();
signals:
   // void sendMainInfo(QList<QList<QVariant>>&res,QVector<QString>&d,QVector<QString> &place);

private:
    Ui::MainWindow *ui;
    myExcel excel;
    QList<QList<QVariant>> accountInfo;//乘客信息
    QList<QList<QVariant>> indexInfo;//字母索引信息
    RegisterPart w;//注册窗口
    loginPart ww;//登录窗口
    managerPart mw;//管理员窗口

};
#endif // MAINWINDOW_H

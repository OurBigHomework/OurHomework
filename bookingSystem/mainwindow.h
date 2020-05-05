#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

protected:
    void paintEvent(QPaintEvent *event) override;
    void setBackgroundImage(QString path);//设置背景图片

private slots:
    void on_loginButton_clicked();


signals:


private:
    Ui::MainWindow *ui;
    myExcel excel;
    QList<QList<QVariant>> accountInfo;//乘客信息
    QList<QList<QVariant>> indexInfo;//字母索引信息


    loginPart ww;//登录窗口
    managerPart mw;//管理员窗口

};
#endif // MAINWINDOW_H

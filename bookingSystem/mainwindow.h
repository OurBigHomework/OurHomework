#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registerpart.h"
#include "loginpart.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool accountExist(QString pword,QString uname);//判断账号是否存在
    void openAgain();//重新打开主窗口
protected:
    void paintEvent(QPaintEvent *event) override;
    void setBackgroundImage(QString path);

private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::MainWindow *ui;
    myExcel excel;
    QList<QList<QVariant>> accountInfo;
    QList<QList<QVariant>> indexInfo;
    RegisterPart w;
    loginPart ww;
};
#endif // MAINWINDOW_H

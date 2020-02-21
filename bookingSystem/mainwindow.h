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
protected:
    void paintEvent(QPaintEvent *event) override;
    void setBackgroundImage(QString path);

private slots:
    void on_loginButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::MainWindow *ui;
    RegisterPart w;
    loginPart ww;
};
#endif // MAINWINDOW_H

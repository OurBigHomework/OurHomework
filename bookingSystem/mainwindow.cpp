#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter *p=new QPainter(this);
    p->drawPixmap(rect(),QPixmap(":/new/prefix1/sunshine.jpg"));
    p->end();
}
MainWindow::~MainWindow()
{
    delete ui;
}


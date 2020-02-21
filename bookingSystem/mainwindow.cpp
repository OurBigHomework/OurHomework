#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPalette>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
void MainWindow::setBackgroundImage(QString path)
{
    QPixmap pixmap = QPixmap(path).scaled(this->size());
        QPalette palette(this->palette());
        palette.setBrush(QPalette::Background, QBrush(pixmap));
        this->setPalette(palette);

}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/sky1.jpg"));
}
MainWindow::~MainWindow()
{
    delete ui;
}


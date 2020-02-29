#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->warningText->setVisible(false);
    ui->password->setEchoMode(QLineEdit::Password);
    connect(&ww,&loginPart::openMainWindow,this,&MainWindow::openAgain);

    excel.setPath("D:/OurHomework/bookingSystem/Data/Passengers.xlsx");
    QVariant v1=excel.readAll(1);
    excel.excelToQList(v1,accountInfo);
    QVariant v2=excel.readAll(2);
    excel.excelToQList(v2,indexInfo);



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


void MainWindow::on_loginButton_clicked()
{

    QString Uname=ui->UserName->text();
    QString Pword=ui->password->text();
    if(Uname=="Conservator"&&Pword=="123456")
    {
        hide();
    }
    else
    {
        if(Pword.isNull()||Pword.isEmpty())
        {
            ui->warningText->setText("Password must not be empty.");
            ui->warningText->setVisible(true);

        }
        else if(Uname.isNull()||Uname.isEmpty())
        {
            ui->warningText->setText("UserName must not be empty.");
            ui->warningText->setVisible(true);

        }
        else if(accountExist(Pword,Uname))
        {
            hide();
            ww.showMaximized();
        }
        else
        {
            ui->warningText->setVisible(true);
            ui->warningText->setText("Username or password error." );

        }

    }


}
void MainWindow::openAgain()
{
    ww.close();
    show();

}

bool MainWindow::accountExist(QString pword, QString uname)
{
    QString first=uname.at(0);
    int k=-1;
    for(int i=1;i<indexInfo.size();i++)
    {
        if(indexInfo[i][0].toString()==first)
        {
            k=i;
            break;
        }
    }
    if(k==-1)
    {

        return false;
    }
    int num1=indexInfo[k][2].toInt();
    int num2=indexInfo[k][1].toInt()+num1;
    int flag=0;
    int mid=num1;
    if(accountInfo[num1][0].toString()==uname)flag=1;
    else
    {
        while(num2-num1>1)
        {
            mid=(num1+num2)/2;
            if(accountInfo[mid][0].toString()==uname)
            {
                flag=1;
                break;
            }else if(QString::compare(uname,accountInfo[mid][0].toString())>0)
            {
               num1=mid;
            }else
            {
                num2=mid;
            }
        }
    }
    if(flag==1)
    {
        if(accountInfo[mid][1].toString()==pword)return true;
        else return false;
    }else
    {
        return false;
    }




//if(pword=="123"&&uname=="haha")return true;
//else return false;

}
void MainWindow::on_registerButton_clicked()
{
    hide();
    w.showMaximized();

}

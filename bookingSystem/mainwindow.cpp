#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QDebug>
#include<QElapsedTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->warningText->setVisible(false);
    ui->password->setEchoMode(QLineEdit::Password);
    setWindowIcon(QIcon(":/new/prefix1/plane3.png"));
    setWindowTitle("用户登录");
    connect(&mw,&managerPart::comeBack,this,&MainWindow::openAgain);
    connect(&ww,&loginPart::sendPlaceAndDate,&mw,&managerPart::getPlaceAndDate);

    QElapsedTimer timer;
    timer.start();
    excel.setPath("D:/OurHomework/bookingSystem/Data/Passengers.xlsx");
    QList<QList<QList<QVariant>>> mylist;
    excel.readAllSheet(mylist);
    accountInfo=mylist[0];
    indexInfo=mylist[1];

    qDebug()<< timer.elapsed()<<"--main";



}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/sky6.jpg"));
}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_loginButton_clicked()
{

    ww.setVars(mw.dia.vars);
    QString Uname=ui->UserName->text();
    QString Pword=ui->password->text();
    int index=0;
    if(Uname=="Manager"&&Pword=="123456")
    {
        mw.show();
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
        else if(accountExist(Pword,Uname,index))
        {

            hide();
            QString rname=accountInfo[index][2].toString();
            QString phone=accountInfo[index][3].toString();
            QString birday=accountInfo[index][4].toString();
            QString sex=accountInfo[index][5].toString();
            ww.allPas=accountInfo;
            QVector<QString> ticketvec;
            for(int x=6;x<=10;x++)
            {
                QString ticket=accountInfo[index][x].toString();
                ticketvec.push_back(ticket);

            }

            ww.setPassenger(Uname,Pword,birday,sex,rname,phone,index);
            ww.sendLoginSignal(ticketvec);
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
    ui->password->setText("");
    show();

}

bool MainWindow::accountExist(QString pword, QString uname,int& index)
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
        if(accountInfo[mid][1].toString()==pword)
        {
            index=mid;
            return true;
        }

        else return false;
    }else
    {
        return false;
    }




//if(pword=="123"&&uname=="haha")return true;
//else return false;

}

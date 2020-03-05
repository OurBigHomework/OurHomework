#include "flightinfodialog.h"
#include "ui_flightinfodialog.h"
#include<QDebug>
#include<QMessageBox>
#include<QElapsedTimer>

FlightInfoDialog::FlightInfoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightInfoDialog)
{
    ui->setupUi(this);


    qRegisterMetaType <QList<QList<QList<QVariant>>>>("QList<QList<QList<QVariant>>>&");
    th=new MyThread;
    th->setPath("D:/OurHomework/bookingSystem/Data/myData2.xlsx");
    th->start();

    e.setPath("D:/OurHomework/bookingSystem/Data/myData2.xlsx");
    myExcel excel;
    excel.setPath("D:/OurHomework/bookingSystem/Data/myData.xlsx");

    places= excel.getExcelVLine(1,0,"A1","A34");
   for(int i=0;i<places.size();i++)
   {
       ui->beginBox->addItem(places[i]);
       ui->endBox->addItem(places[i]);
       ui->beginBox_2->addItem(places[i]);
       ui->endBox_2->addItem(places[i]);
   }

  dates=excel.getExcelVLine(2,0,"A1","A5");

connect(th,&MyThread::isDone,this,&FlightInfoDialog::dealDone);
}

FlightInfoDialog::~FlightInfoDialog()
{
    delete ui;
}

void FlightInfoDialog::changePage(int i)
{
    ui->stackedWidget->setCurrentIndex(i);
}

int FlightInfoDialog::dateCorrect(QString d)
{


    QStringList list=d.split("-");
    int y=list[0].toInt();
    int m=list[1].toInt();
    int dd=list[2].toInt();
    QString mm=list[1];
    QString ddd=list[2];

    if(m<10)mm="0"+mm;
    if(dd<10)ddd="0"+ddd;
    d=QString("%1-%2-%3").arg(y).arg(mm).arg(ddd);

    for(int i=0;i<dates.size();i++)
    {

        if(dates[i].left(10)==d)return i;
    }
    if((y%4==0&&y%100!=0)||y%400==0)
    {
        if(m==2&&dd>29)return -1;

    }else
    {
        if(m==2&&dd>28)return -1;
    }
    if((m==4)||(m==6)||(m==9)||(m==11))
    {
        if(dd>30)return -1;
    }
    return -2;
}

void FlightInfoDialog::dealDone(QList<QList<QList<QVariant>>>&vars)
{
    th->quit();
    th->wait();
    this->vars=vars;
}


void FlightInfoDialog::on_buttonOk_clicked()
{
    QString bPlace=ui->beginBox->currentText();
    QString ePlace=ui->endBox->currentText();
    if(bPlace==ePlace)
    {
        QMessageBox::information(this,"Warning","The starting and ending points can't be the same.");
    }
    QString date=QString("%1-%2-%3").arg(ui->yearBox->text()).arg(ui->monthBox->text()).arg(ui->dayBox->text());
    int k=dateCorrect(date);
    if(k==-1)
    {
        QMessageBox::information(this,"Warning","Wrong enter date!");
    }else if(k==-2)
    {
        QMessageBox::information(this,"Tips","Tickets not open on current date!Please re-select the date. ");
    }else
    {

        QVariant v=e.readAll((k+1));

        int q1=-1,q2=-1;
        for(int i=0;i<places.size();i++)
        {
            if(bPlace==places[i])q1=i;
            if(ePlace==places[i])q2=i;
            if(q1!=-1&&q2!=-1)break;
        }


    }
    qDebug()<<bPlace<<ePlace<<date;
}

void FlightInfoDialog::on_buttonOk_2_clicked()
{
    QString bPlace=ui->beginBox_2->currentText();
    QString ePlace=ui->endBox_2->currentText();
    if(bPlace==ePlace)
    {
        QMessageBox::information(this,"Warning","The starting and ending points can't be the same.");
        return;
    }
    QString date=QString("%1-%2-%3").arg(ui->yearBox_2->text()).arg(ui->monthBox_2->text()).arg(ui->dayBox_2->text());
    int k=dateCorrect(date);
    if(k==-1)
    {
        QMessageBox::information(this,"Warning","Wrong enter date!");
    }else if(k==-2)
    {
        QMessageBox::information(this,"Tips","Tickets not open on current date!Please re-select the date. ");
    }else
    {



//        QElapsedTimer timer;
//        timer.start();
//        QVariant v=e.readAll((k+1));
//        qDebug()<<timer.elapsed()<<"ms  -read";
//        timer.restart();
//        QList<QList<QVariant>> res;
//        e.excelToQList(v,res);
//        qDebug()<<timer.elapsed()<<"ms  -save";

        int q1=-1,q2=-1;
        for(int i=0;i<places.size();i++)
        {
            if(bPlace==places[i])q1=i;
            if(ePlace==places[i])q2=i;
            if(q1!=-1&&q2!=-1)break;
        }
        if(!vars.isEmpty())
        {
            //qDebug()<<k<<vars.size();
            emit Search(q1,q2,date,vars[k]);
            close();
        }else{
            QMessageBox::information(this,"Tips","Please wait for a minute.The system is initializing...");
        }




    }
    //qDebug()<<bPlace<<ePlace<<date;
}

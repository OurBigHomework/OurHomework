#include "flightinfodialog.h"
#include "ui_flightinfodialog.h"
#include "threadwritecell.h"
#include<QDebug>
#include<QMessageBox>
#include<QElapsedTimer>

FlightInfoDialog::FlightInfoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightInfoDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/plane3.png"));
    e.setPath("D:/OurHomework/bookingSystem/Data/myData2.xlsx");
    e.readAllSheet(vars);
//    QList<QVariant> varList;
//    int c=e.sheetCount();//
//    for(int i=0;i<c;i++)
//    {
//        varList.push_back(e.readAll(i+1));
//        QList<QList<QVariant>> r;
//        e.excelToQList(varList[i],r);
//        vars.push_back(r);

//    }
connect(&w,&threadWriteCell::writeOk,this,&FlightInfoDialog::dealWriteOk);
}

FlightInfoDialog::~FlightInfoDialog()
{
    delete ui;
}

void FlightInfoDialog::changePage(int i)
{
    ui->stackedWidget->setCurrentIndex(i);
}

void FlightInfoDialog::dealWriteOk()//修改成功后线程停止
{
    w.quit();
    w.wait();

}

void FlightInfoDialog::initChangePage(QString &t, QString &t1, QString &t2, QString &t3)//初始化界面
{
    ui->time->setText(t);
    ui->ticket_1->setText(t1);
    ui->ticket_2->setText(t2);
    ui->ticket_3->setText(t3);
}

int FlightInfoDialog::dateCorrect(QString d)//判断查找日期
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
    //若日期在航班开放日期范围内，则返回日期索引
    for(int i=0;i<dates.size();i++)
    {

        if(dates[i].left(10)==d)return i;
    }
    //判断是否闰年
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
//    th->quit();
//    th->wait();
  //  this->vars=vars;


//    myExcel excel;
//    excel.setPath("D:/OurHomework/bookingSystem/Data/myData.xlsx");
//    places= excel.getExcelVLine(1,0,"A1","A34");
//   for(int i=0;i<places.size();i++)
//   {
//       ui->beginBox->addItem(places[i]);
//       ui->endBox->addItem(places[i]);
//       ui->beginBox_2->addItem(places[i]);
//       ui->endBox_2->addItem(places[i]);
//   }

//  dates=excel.getExcelVLine(2,0,"A1","A5");
//  qDebug()<<"flightDia ok";

//qDebug()<<vars.size()<<"dealDone";
  emit send(vars);

}
 void FlightInfoDialog::initPlaceAndDate(QVector<QString> &place, QVector<QString> &dates)
 {
     this->places=place;
     this->dates=dates;
     for(int i=0;i<places.size();i++)
     {

         ui->beginBox_2->addItem(places[i]);
         ui->endBox_2->addItem(places[i]);
     }

 }


void FlightInfoDialog::on_buttonOk_2_clicked()
{
    QString bPlace=ui->beginBox_2->currentText();//起点
    QString ePlace=ui->endBox_2->currentText();//终点
    if(bPlace==ePlace)
    {
        QMessageBox::information(this,"警告","起点和终点不能相同！");
        return;
    }
    //日期
    QString date=QString("%1-%2-%3").arg(ui->yearBox_2->text()).arg(ui->monthBox_2->text()).arg(ui->dayBox_2->text());
    int k=dateCorrect(date);//判断日期是否符合实际
    if(k==-1)
    {
        QMessageBox::information(this,"警告","日期不存在!");
    }else if(k==-2)
    {
        QMessageBox::information(this,"提示","该日期航班尚未开放，请重新选择日期！");
    }else
    {
        int q1=-1,q2=-1;//q1为起点索引，q2为终点索引
        for(int i=0;i<places.size();i++)
        {
            if(bPlace==places[i])q1=i;
            if(ePlace==places[i])q2=i;
            if(q1!=-1&&q2!=-1)break;
        }
        if(!vars.isEmpty())
        {
            sheetNum=k;
            qq1=q1;
            qq2=q2;
            dd=date;
            emit Search(q1,q2,date,vars[k]);//向managerpart传递信号
            close();
        }else{
            QMessageBox::information(this,"提示","请稍等，系统正在初始化中...");
        }




    }
    //qDebug()<<bPlace<<ePlace<<date;
}

void FlightInfoDialog::on_buttonChangeYes_clicked()
{
    QString t=ui->time->text();
    QString tn1=ui->ticket_1->text();
    QString tn2=ui->ticket_2->text();
    QString tn3=ui->ticket_3->text();
    QString num=QString("%1-%2-%3").arg(tn1).arg(tn2).arg(tn3);
//    myExcel*ex=new myExcel;
//    ex->setPath("D:/OurHomework/bookingSystem/Data/myData2.xlsx");
    QVector<int>rows,cols;//修改界面时间、票的索引
    rows.push_back(line);
    rows.push_back(line);
    cols.push_back(currentTimeIndex);
    cols.push_back(currentTimeIndex+1);
//    qDebug()<<"line:"<<line<<"time:"<<currentTimeIndex;
    QStringList l;
    l<<t<<num;
//    ex->writeCell(l,rows,cols,sheetNum);
    vars[sheetNum][line][currentTimeIndex]=QVariant(t);
    vars[sheetNum][line][currentTimeIndex+1]=QVariant(num);
//    qDebug()<<vars[sheetNum][line][currentTimeIndex]<<vars[sheetNum][line][currentTimeIndex+1]<<"hh-240";
    //开启线程，修改excel文件中的信息
    w.setPath("D:/OurHomework/bookingSystem/Data/myData2.xlsx");
    w.setInfo(l,rows,cols,sheetNum);
    w.start();
    ui->stackedWidget->setCurrentIndex(0);

}

void FlightInfoDialog::on_returnButton_clicked()
{
    close();
    emit Search(qq1,qq2,dd,vars[sheetNum]);
}

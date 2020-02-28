#include "loginpart.h"
#include "ui_loginpart.h"
#include<QDebug>
#include<QCoreApplication>
#include<QFile>
#include<QMessageBox>
#include<QListWidget>
#include<QListWidgetItem>
loginPart::loginPart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginPart)
{
    ui->setupUi(this);
    ui->stackedWidget->setFrameShape(QFrame::NoFrame);
    ui->titleText->setFrameShape(QFrame::NoFrame);
//    HRESULT r = OleInitialize(0);
//    if (r != S_OK && r != S_FALSE)
//    {
//        qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);
//    }


    e.setPath("D:/OurHomework/bookingSystem/Data/myData1.xlsx");
    e.init();
    QVariant var=e.readAll();

     e.excelToQList(var,res);
     ui->start->clear();
     ui->end->clear();
     for(int i=0;i<e.place.size();i++)
     {

         ui->start->addItem(e.place[i]);
         ui->end->addItem(e.place[i]);
     }





}
QString loginPart::getCalDate()
{
    QString date=ui->beginTime->selectedDate().toString("yyyy-MM-dd");

    return date;
}
void loginPart::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush(Qt::white);
    p.drawRect(rect());
}

loginPart::~loginPart()
{

    delete ui;
}

void loginPart::showSearchPage(int begin, int end, QString date,int &time)
{
   int line=begin*e.place.size()+end+1;
    //qDebug()<<line<<res[line][0]<<res[line][1]<<begin<<end<<e.place[begin]<<e.place[end];
    ui->list->setViewMode(QListView::ListMode);
    QString placeInfo=e.place[begin].append("(Starting Station)------->> ").append(e.place[end]).append("(Terminus)");
    QString t;
    if(res[line][2].toString()=="yes")t="Remaning Tickets";
    else t="No Remaning Tickets";

    for(int i=3;i<res[0].size();i++)
    {
        QString p=res[0][i].toString();
        QString planeText=e.place[begin].left(2).toUpper().append(e.place[end].left(2).toUpper());
        QString pt=planeText.append(p.left(2)).append(p.right(2));
        ticketItems *it=new ticketItems(ui->list);
        it->setTime(p);
        it->setPlaces(placeInfo);

        it->setHasTicket(t);
        it->setPlaneName(pt);

        QListWidgetItem*item=new QListWidgetItem(ui->list,0);
        item->setSizeHint(QSize(580,160));
        ui->list->setItemWidget(item,it);
        ui->titleText->setText("Flight Information");




    }
    ui->list->show();

}

void loginPart::on_buttonSearch_clicked()
{

    QString begDate=getCalDate();
    QString begPlace=ui->start->currentText();
    QString endPlace=ui->end->currentText();
    if(begPlace==endPlace)
    {
        QMessageBox::information(this,"Warning","Start and end cannot be the same");
        return;
    }

    int a=-1,b=-1;
    for(int i=0;i<e.place.size();i++)
    {
        if(e.place[i]==begPlace)a=i;
        if(e.place[i]==endPlace)b=i;
        if(a!=-1&&b!=-1)break;
    }

    showSearchPage(a,b,begDate,timeIndex);
}

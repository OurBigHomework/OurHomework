#include "managerpart.h"
#include "ui_managerpart.h"
#include "flightsinformation.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QDebug>
#include<QListWidgetItem>
managerPart::managerPart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::managerPart)
{
    ui->setupUi(this);
    setWindowTitle("管理员界面");
     qRegisterMetaType <QList<QList<QList<QVariant>>>>("QList<QList<QList<QVariant>>>&");
    connect(&dia,&FlightInfoDialog::Search,this,&managerPart::showSearchPage);
    setWindowIcon(QIcon(":/new/prefix1/plane3.png"));
    //connect(&dia,&FlightInfoDialog::send,this,&managerPart::getInfo);

}

managerPart::~managerPart()
{
    delete ui;
}

void managerPart::getPlaceAndDate(QVector<QString> &place, QVector<QString> &dates)
{

    dia.initPlaceAndDate(place,dates);
}

void managerPart::getInfo(QList<QList<QList<QVariant> > > &vars)
{
    qDebug()<<"getInfo"<<vars.size();
    emit sendInfo(vars);

}

void managerPart::showSearchPage(int begin, int end,QString&date, QList<QList<QVariant>>&res)
{

    this->res=res;
    if(ui->list->count()>0)
    {
        ui->list->clear();
    }

    ui->stackedWidget->setCurrentIndex(1);
    ui->list->setViewMode(QListView::ListMode);
        line=begin*dia.places.size()+end+1;

        ui->list->setViewMode(QListView::ListMode);
        QString temp=dia.places[begin];
         QString placeInfo=temp.append("(Starting Station)------->> ").append(dia.places[end]).append("(Terminus)");
        QString t=date;
        for(int i=1;i<(res[0].size()-3)/2+1;i++)
        {

            int index=2*i+1;
            int num=2*i+2;
           QString p=res[line][index].toString();
           QString planeText=dia.places[begin].left(2).toUpper().append(dia.places[end].left(2).toUpper());
           QString pt=planeText.append(p.left(2)).append(p.right(2));
           ticketItems *it=new ticketItems(ui->list);
           it->setTime(p);
           it->setPlaces(placeInfo);
           it->setIndex(index);
           it->setTicketsNum(res[line][num].toString());

           it->setHasTicket(t);
           it->setPlaneName(pt);

           QListWidgetItem*item=new QListWidgetItem(ui->list,0);
           item->setSizeHint(QSize(600,160));
           ui->list->setItemWidget(item,it);

           connect(it,&ticketItems::itemClicked,this,&managerPart::itemClick);


        }


        ui->list->show();


}

void managerPart::itemClick(ticketItems *it)
{
    dia.show();
    dia.changePage(1);

    QStringList strs=it->getTicketsNum().split("-");
    QString time=it->getTime();
    dia.line=line;
    dia.currentTimeIndex=it->getIndex();

   //qDebug()<<"index:"<<it->getIndex()<<"line:"<<line;
    dia.initChangePage(time,strs[0],strs[1],strs[2]);

}
void managerPart::on_changeHead_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"Open","../", "Images (*.png *.jpg)");
    if(!filePath.isEmpty())
    {
        QImage image(filePath);
            ui->head->setPixmap(QPixmap::fromImage(image));
            ui->head->resize(image.width(),image.height());
    }


}

void managerPart::on_comeBack_clicked()
{
    emit comeBack();
    close();
}

void managerPart::on_mofInfo_clicked()
{
    dia.setWindowTitle("Choose flights");
    dia.changePage(2);
    dia.show();
}

//void managerPart::on_newFlights_clicked()
//{
//    dia.setWindowTitle("Add new flight");
//    dia.changePage(0);
//    dia.show();
//}

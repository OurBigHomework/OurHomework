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
    connect(&dia,&FlightInfoDialog::Search,this,&managerPart::showSearchPage);
}

managerPart::~managerPart()
{
    delete ui;
}

QString managerPart::formateStr(QString &str, int k)
{
    while (str.size()<k) {
        str.append(" ");

    }
    return str;
}

void managerPart::showSearchPage(int begin, int end,QString&date, QList<QList<QVariant>>&res)
{
    if(ui->list->count()>0)
    {
        ui->list->clear();
    }

    ui->stackedWidget->setCurrentIndex(1);
    ui->list->setViewMode(QListView::ListMode);
        int line=begin*dia.places.size()+end+1;
        ui->list->setViewMode(QListView::ListMode);
        QString temp1=dia.places[begin];
        QString temp2=dia.places[end];

        for(int i=1;i<(res[0].size()-3)/2+1;i++)
        {

            int index=2*i+1;
            QString p=res[line][index].toString();
           FlightsInformation* info=new FlightsInformation(ui->list);
           info->setend(temp2);
           info->setbegin(temp1);
           info->setDate(date);
           info->setTime(p);

           QListWidgetItem*item=new QListWidgetItem(ui->list,0);
           item->setSizeHint(QSize(622,100));
           ui->list->setItemWidget(item,info);



        }


        ui->list->show();


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
    dia.changePage(1);
    dia.show();
}

void managerPart::on_newFlights_clicked()
{
    dia.setWindowTitle("Add new flight");
    dia.changePage(0);
    dia.show();
}

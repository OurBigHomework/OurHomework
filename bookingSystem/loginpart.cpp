#include "loginpart.h"
#include "ui_loginpart.h"
#include<QDebug>
#include<QCoreApplication>
#include<QFile>
#include<QMessageBox>

loginPart::loginPart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginPart)
{
    ui->setupUi(this);
    ui->stackedWidget->setFrameShape(QFrame::NoFrame);
    ui->titleText->setFrameShape(QFrame::NoFrame);
    setWindowIcon(QIcon(":/new/prefix1/plane1.png"));

    connect(this,&loginPart::initLogin,this,&loginPart::initPersonalInfo);

    e.setPath("D:/OurHomework/bookingSystem/Data/myData2.xlsx");
    e.getExcelRLine(1,0,"A1","F1");

    QVariant var=e.readAll(1);
    myExcel*ee=new myExcel;
    ee->setPath("D:/OurHomework/bookingSystem/Data/myData.xlsx");
    place=ee->getExcelVLine(1,0,"A1","A34");
     e.excelToQList(var,res);
     ui->start->clear();
     ui->end->clear();
     for(int i=0;i<place.size();i++)
     {

         ui->start->addItem(place[i]);
         ui->end->addItem(place[i]);
     }





}

void loginPart::initPersonalInfo()
{

    ui->labelName->setText( passenger.getUsername());
    ui->Username->setText(QString("Username:").append(passenger.getUsername()));
    ui->Name->setText(QString("Name:").append(passenger.getName()));
    ui->Birthday->setText(QString("Birthday:").append(passenger.getBirthday().left(10)));
    ui->Sex->setText(QString("Sex:").append(passenger.getSex()));
    ui->MobilePhone->setText(QString("MobilePhone:").append(passenger.getPhone()));
    ui->Password->setText(QString("Password:").append(passenger.getPassword()));
}

void loginPart::sendLoginSignal()
{
    emit initLogin();
}

void loginPart::deleteItems(QListWidget *list, int count)
{
    for(int i=0;i<count;i++)
    {
        QListWidgetItem*item=list->takeItem(0);
        delete item;
    }
}

QString loginPart::getCalDate()
{
    QString date=ui->beginTime->selectedDate().toString("yyyy-MM-dd");

    return date;
}
void loginPart::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setBrush(Qt::white);
    p.drawRect(rect());
}

loginPart::~loginPart()
{

    delete ui;
}

void loginPart::setPassenger(QString username, QString password,QString birthday,QString sex,QString name,QString phone,int index)
{

    passenger.setUsername(username);

    passenger.setPassword(password);
    passenger.setIndex(index);
    passenger.setSex(sex);
    passenger.setName(name);
    passenger.setPhone(phone);
    passenger.setBirthday(birthday);


}

void loginPart::showSearchPage(int begin, int end, QString date,int &time)
{

int line=begin*place.size()+end+1;
    ui->list->setViewMode(QListView::ListMode);
    QString temp=place[begin];
     QString placeInfo=temp.append("(Starting Station)------->> ").append(place[end]).append("(Terminus)");
    QString t;
    if(res[line][2].toString()=="yes")t="Remaning Tickets";
    else t="No Remaning Tickets";

    for(int i=1;i<(res[0].size()-3)/2+1;i++)
    {

        int index=2*i+1;
        QString p=res[line][index].toString();
        QString planeText=place[begin].left(2).toUpper().append(place[end].left(2).toUpper());
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

    if(ui->list->count()>0)
    {
        deleteItems(ui->list,ui->list->count());
    }
    ui->stackedWidget->setCurrentIndex(1);
    QString begDate=getCalDate();
    QString begPlace=ui->start->currentText();
    QString endPlace=ui->end->currentText();
    if(begPlace==endPlace)
    {
        QMessageBox::information(this,"Warning","Start and end cannot be the same");
        return;
    }

    int a=-1,b=-1;
    for(int i=0;i<place.size();i++)
    {

        if(place[i]==begPlace)a=i;

        if(place[i]==endPlace)b=i;
        if(a!=-1&&b!=-1)break;
    }


    showSearchPage(a,b,begDate,timeIndex);
}

void loginPart::on_comeBack_clicked()
{
    emit openMainWindow();
}

void loginPart::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void loginPart::on_pushButtonEdit_clicked()
{

    ui->textEdit->setEnabled(true);
}

void loginPart::on_pushButtonEditOK_clicked()
{
    ui->textEdit->setEnabled(false);
}

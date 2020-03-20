#include "loginpart.h"
#include "ui_loginpart.h"
#include<QDebug>
#include<QCoreApplication>
#include<QFile>
#include<QMessageBox>
#include "chooseticketdialog.h"
loginPart::loginPart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginPart)
{
    ui->setupUi(this);
    ui->stackedWidget->setFrameShape(QFrame::NoFrame);
    ui->titleText->setFrameShape(QFrame::NoFrame);
    setWindowIcon(QIcon(":/new/prefix1/plane1.png"));
    ui->stackedWidget->setCurrentIndex(0);

  th2=new MyThread;

    th2->setPath("D:/OurHomework/bookingSystem/Data/myData.xlsx");
    th2->start();
    qRegisterMetaType <QList<QList<QList<QVariant>>>>("QList<QList<QList<QVariant>>>&");
    connect(this,&loginPart::initLogin,this,&loginPart::initPersonalInfo);
    connect(th2,&MyThread::isDone,this,&loginPart::initDateAndPlace);



     ui->start->clear();
     ui->end->clear();
     ui->start_2->clear();
     ui->end_2->clear();
}

void loginPart::setVars(QList<QList<QList<QVariant> > > &vars)
{
    this->vars=vars;
}

void loginPart::initPersonalInfo()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelName->setText( passenger.getUsername());
    ui->Username->setText(QString("Username:").append(passenger.getUsername()));
    ui->Name->setText(QString("Name:").append(passenger.getName()));
    ui->Birthday->setText(QString("Birthday:").append(passenger.getBirthday().left(10)));
    ui->Sex->setText(QString("Sex:").append(passenger.getSex()));
    ui->MobilePhone->setText(QString("MobilePhone:").append(passenger.getPhone()));
    ui->Password->setText(QString("Password:").append(passenger.getPassword()));
    initDateAndPlace(vars);
}

void loginPart::initDateAndPlace(QList<QList<QList<QVariant>>>&v)
{
    th2->quit();
    th2->wait();

//    qDebug()<<v.size()<<v[0].size()<<v[1].size();
    for(int i=0;i<v[0].size();i++)
    {
        place.push_back(v[0][i][0].toString());
    }
    for(int i=0;i<v[1].size();i++)
    {
        dates.push_back(v[1][i][0].toString().left(10));
    }
         for(int i=0;i<place.size();i++)
         {

             ui->start->addItem(place[i]);
             ui->start_2->addItem(place[i]);
             ui->end->addItem(place[i]);
             ui->end_2->addItem(place[i]);
         }
    emit sendPlaceAndDate(place,dates);
    qDebug()<<"d and p init ok";
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
    QString week=ui->beginTime->selectedDate().toString("ddd");

    return QString("%1(%2)").arg(date).arg(week);
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
void loginPart::initPlaneInfo(QList<QList<QList<QVariant>>>&vars)
{
    this->vars=vars;
    qDebug()<<"LoginPart init ok.";

}

void loginPart::itemClick(ticketItems *it)
{
    chooseTicketDialog*dia=new chooseTicketDialog;
    dia->show();
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

void loginPart::showSearchPage(int begin, int end, QString date)
{

    if(vars.isEmpty())
    {
        QMessageBox::information(this,"Tips:","数据正在加载中，请稍后。。。");
        return;
    }
    int flag=-1;
    //qDebug()<<"Psize:"<<place.size()<<"Dsize:"<<dates.size()<<"date:"<<date;

    for(int i=0;i<dates.size();i++)
    {
        if(dates[i]==date.left(10))
        {
            flag=i;
            break;
        }
    }
    if(flag==-1)
    {
        QMessageBox::information(this,"Tips","Tickets not open on current date.Please re-select the date.");
    }
    else
    {
        int line=begin*place.size()+end+1;
            ui->list->setViewMode(QListView::ListMode);
            QString temp=place[begin];
             QString placeInfo=temp.append("(Starting Station)------->> ").append(place[end]).append("(Terminus)");
            QString t=date;
            QList<QList<QVariant>> res=vars[flag];


            for(int i=1;i<(res[0].size()-3)/2+1;i++)
            {

                int index=2*i+1;
                int num=2*i+2;
                QString p=res[line][index].toString();
                QString planeText=place[begin].left(2).toUpper().append(place[end].left(2).toUpper());
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
                ui->titleText->setText("Flight Information");
                connect(it,&ticketItems::itemClicked,this,&loginPart::itemClick);

            }
            ui->list->show();
    }


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


    showSearchPage(a,b,begDate);
}

void loginPart::on_comeBack_clicked()
{

    emit openMainWindow();
}

void loginPart::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->titleText->setText("Personal Information");
}

void loginPart::on_pushButtonEdit_clicked()
{

    ui->textEdit->setReadOnly(false);

}
void loginPart::on_pushButtonEditOK_clicked()
{
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setCursor(Qt::ArrowCursor);

}

void loginPart::on_buttonSearchByPlace_clicked()
{
    if(ui->list->count()>0)
    {
        deleteItems(ui->list,ui->list->count());
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->titleText->setText("Flight Information");

    QString begPlace=ui->start_2->currentText();
    QString endPlace=ui->end_2->currentText();
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
    if(vars.isEmpty())
    {
        QMessageBox::information(this,"Tips:","数据正在加载中，请稍后。。。");
        return;
    }
    int line=a*place.size()+b+1;
    ui->list->setViewMode(QListView::ListMode);
    QString placeInfo=begPlace.append("(Starting Station)------->> ").append(endPlace).append("(Terminus)");
    for(int i=0;i<5;i++)
    {
        QString d=dates[i];

        QList<QList<QVariant>> res=vars[i];

         for(int i=1;i<(res[0].size()-3)/2+1;i++)
         {

             int index=2*i+1;
             int num=2*i+2;
             QString p=res[line][index].toString();
             QString planeText=begPlace.left(2).toUpper().append(endPlace.left(2).toUpper());
             QString pt=planeText.append(p.left(2)).append(p.right(2));
             ticketItems *it=new ticketItems(ui->list);
             it->setTime(p);
             it->setPlaces(placeInfo);
             it->setIndex(index);
             it->setTicketsNum(res[line][num].toString());
             it->setHasTicket(d);
             it->setPlaneName(pt);

             QListWidgetItem*item=new QListWidgetItem(ui->list,0);
             item->setSizeHint(QSize(600,160));
             ui->list->setItemWidget(item,it);

             connect(it,&ticketItems::itemClicked,this,&loginPart::itemClick);

         }

    }
    ui->list->show();

}

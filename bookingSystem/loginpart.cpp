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

    th3=new MyThread;
    th3->setPath("D:/OurHomework/bookingSystem/Data/PassengersTicketsData.xlsx");
    th3->start();

    write=new threadWriteCell;

    dia=new chooseTicketDialog;

    pTickets=false;
    qRegisterMetaType <QList<QList<QList<QVariant>>>>("QList<QList<QList<QVariant>>>&");
    connect(this,&loginPart::initLogin,this,&loginPart::initPersonalInfo);
    connect(th2,&MyThread::isDone,this,&loginPart::initDateAndPlace);
    connect(th3,&MyThread::isDone,this,&loginPart::showP_TTips);
    connect(dia,&chooseTicketDialog::success,this,&loginPart::buySuccess);
    connect(dia,&chooseTicketDialog::fail,this,&loginPart::buyFail);
    connect(dia,&chooseTicketDialog::noTicket,this,&loginPart::noTicketError);
    connect(write,&threadWriteCell::writeOk,this,&loginPart::dealDone);


     ui->start->clear();
     ui->end->clear();
     ui->start_2->clear();
     ui->end_2->clear();
}

void loginPart::dealDone()
{

        write->quit();
        write->wait();
        qDebug()<<"成功修改！";
        th3->start();

}
void loginPart::noTicketError(int r, int c, int d, int n,int count)
{
    if(count<=0)return;
            QString str="尊敬的客户：\n很抱歉当前该航班没有余票，您可以选择排队候补或重新选择航班。推荐航班如下：\n同一天同一舱位等级有余票的其他航班：";
            QMessageBox*msg=new QMessageBox();
            msg->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
            msg->button(QMessageBox::Yes)->setText("候补");
            msg->button(QMessageBox::No)->setText("退出");
            for(int i=0;i<13;i++)
            {
                if(i!=c)
                {
                    QString ss=vars[d][r][i*2+4].toString();
                    QStringList l=ss.split("-");
                    if(l.at(n-1).toInt()>0)
                    {
                         str=str+vars[d][r][i*2+3].toString()+"\t";
                    }

                }
            }
            str=str+"\n";
            msg->setText(str);
            int result=msg->exec();
            if(result==QMessageBox::Yes)
            {
                if(write->isRunning())
                {
                    QMessageBox::information(this,"提示","系统繁忙，请稍后再试！");
                    return;
                }
                    write->setPath("D:/OurHomework/bookingSystem/Data/PassengersTicketsData.xlsx");
                    QStringList sl;
                    QVector<int>a,b;
                    int pindex=passenger.getIndex();
                    int cc=(c-3)/2;
                    QString ss=p_t[d][r][cc*3+n+1].toString();
                    QString ss2=QString::number(pindex)+"-"+QString::number(count);
                    sl.push_back(ss.append(ss2+"%"));
                    a.push_back(r);
                    b.push_back(cc*3+n+1);
                    qDebug()<<d<<' '<<r<<' '<<c<<' '<<sl.at(0);
                    write->setInfo(sl,a,b,d);
                    write->start();
                    msg->close();
                    dia->close();
            }else if(result==QMessageBox::No)
            {
                msg->close();
            }
}

void loginPart::buySuccess(int r, int c, int d, int n,int count)
{



}

void loginPart::buyFail()
{
    QMessageBox::information(this,"错误","当前余票数量不足，请重新选择！");
}

void loginPart::showP_TTips(QList<QList<QList<QVariant>>>&vars)
{
    p_t=vars;
    qDebug()<<"航空公司订单信息初始化完毕";
    th3->quit();
    th3->wait();

}

void loginPart::setVars(QList<QList<QList<QVariant> > > &vars)
{
    this->vars=vars;
}

void loginPart::initPersonalInfo(QVector<QString>&t)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelName->setText( passenger.getUsername());
    ui->Username->setText(QString("Username:").append(passenger.getUsername()));
    ui->Name->setText(QString("Name:").append(passenger.getName()));
    ui->Birthday->setText(QString("Birthday:").append(passenger.getBirthday().left(10)));
    ui->Sex->setText(QString("Sex:").append(passenger.getSex()));
    ui->MobilePhone->setText(QString("MobilePhone:").append(passenger.getPhone()));
    ui->Password->setText(QString("Password:").append(passenger.getPassword()));
    tickets=t;
    pTickets=true;
}

void loginPart::initDateAndPlace(QList<QList<QList<QVariant>>>&v)
{
    th2->quit();
    th2->wait();

//    qDebug()<<v.size()<<v[0].size()<<v[1].size()<<"-mm";
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

void loginPart::sendLoginSignal(QVector<QString> &tInfo)
{
    emit initLogin(tInfo);
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


    int col=it->getIndex();
    int row=it->getRow();
    int day=it->getDayIndex();
    QString s=vars[day][row][col+1].toString();
    QStringList l=s.split("-");
    dia->init(l.at(0).toInt(),l.at(1).toInt(),l.at(2).toInt(),row,col,day);
    dia->show();



}

void loginPart::clearList()
{
    if(ui->list->count()>0)
    {
        deleteItems(ui->list,ui->list->count());
    }
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
                it->setRow(line);
                it->setDayIndex(flag);


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

    clearList();
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
    clearList();
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
    for(int j=0;j<5;j++)
    {
        QString d=dates[j];

        QList<QList<QVariant>> res=vars[j];

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
             it->setRow(line);
             it->setDayIndex(j);

             QListWidgetItem*item=new QListWidgetItem(ui->list,0);
             item->setSizeHint(QSize(600,160));
             ui->list->setItemWidget(item,it);

             connect(it,&ticketItems::itemClicked,this,&loginPart::itemClick);

         }

    }
    ui->list->show();

}

void loginPart::on_myTicketsButton_clicked()
{
    if(pTickets)
    {
        clearList();

        for(int k=0;k<5;k++)
        {
            QStringList tk=tickets[k].split("#");

            for(int i=0;i<tk.size();i++)
            {
                QString m=tk.at(i);
//                qDebug()<<m;
                if(m!="")
                {
                    QStringList mlist=m.split("-");
                    int pindex=mlist.at(0).toInt();
                    int tindex=mlist.at(1).toInt();
                    QString count=mlist.at(2);
                    int seat=mlist.at(3).toInt();
//                    qDebug()<<vars[k][pindex][0]<<"-->"<<vars[k][pindex][1]<<" "<<vars[k][pindex][tindex*2+1]
//                            <<" "<<count<<' '<<seat<<"等座";
                    if(vars[k][pindex][0].toString()!=vars[k][pindex][1].toString())
                    {
                        QString placeInfo=vars[k][pindex][0].toString().append("(Starting Station)------->> ").append(vars[k][pindex][1].toString()).append("(Terminus)");
                        ticketItems *it=new ticketItems(ui->list);
                        it->setTime(vars[k][pindex][tindex*2+1].toString());
                        it->setPlaces(placeInfo);
                        it->setIndex(pindex);
                        it->setCount("x"+count);
                        it->setHasTicket(dates[k]);
                        switch (seat) {
                        case 1:it->setPlaneName("一等座");break;
                        case 2:it->setPlaneName("二等座");break;
                        case 3:it->setPlaneName("三等座");break;
                        default:break;

                        }
                        QListWidgetItem*item=new QListWidgetItem(ui->list,0);
                        item->setSizeHint(QSize(600,160));
                        ui->list->setItemWidget(item,it);

                    }

                }

            }
        }
        ui->stackedWidget->setCurrentIndex(1);
        ui->list->show();


    }
    else
    {
        QMessageBox::information(this,"提示","乘客订单正在初始化中，请稍后。。。");
    }
}

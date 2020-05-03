#include "chooseticketdialog.h"
#include "ui_chooseticketdialog.h"
#include<QMessageBox>
chooseTicketDialog::chooseTicketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseTicketDialog)
{
    ui->setupUi(this);
    setWindowTitle("Choose");
    setWindowIcon(QIcon(":/new/prefix1/plane3.png"));
}

chooseTicketDialog::~chooseTicketDialog()
{
    delete ui;
}

void chooseTicketDialog::init(int a, int b, int c,int row,int col,int day)
{
    ui->num1->setText(QString::number(a));
    ui->num2->setText(QString::number(b));
    ui->num3->setText(QString::number(c));
    changeText(a,ui->buy1);
    changeText(b,ui->buy2);
    changeText(c,ui->buy3);
    Row=row;
    Col=col;
    Day=day;

}

void chooseTicketDialog::changeText(int n,QPushButton*l)
{
   if(n>0)
   {
       l->setText("订票");
   }
   else
   {
       l->setText("候补");
   }
}

void chooseTicketDialog::buyTickets(QLabel*btn,QSpinBox*box,int k)
{
    int num=btn->text().toInt();
    int count=box->value();
    if(num==0)
    {
        emit noTicket(Row,Col,Day,k,count);

    }
    else if(count>num)
    {
        emit fail();
    }
    else
    {
        emit success(Row,Col,Day,k,count);
    }
}
void chooseTicketDialog::on_buy1_clicked()
{
    buyTickets(ui->num1,ui->spinBox1,1);
}

void chooseTicketDialog::on_buy2_clicked()
{
    buyTickets(ui->num2,ui->spinBox2,2);
}

void chooseTicketDialog::on_buy3_clicked()
{
    buyTickets(ui->num3,ui->spinBox3,3);
}

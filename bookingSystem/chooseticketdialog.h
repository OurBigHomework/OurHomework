#ifndef CHOOSETICKETDIALOG_H
#define CHOOSETICKETDIALOG_H

#include <QDialog>
#include<QLabel>
#include<QPushButton>
#include<QSpinBox>
namespace Ui {
class chooseTicketDialog;
}

class chooseTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chooseTicketDialog(QWidget *parent = nullptr);
    ~chooseTicketDialog();
    void init(int a,int b,int c,int row,int col,int day);

    void changeText(int n,QPushButton*l);
    void buyTickets(QLabel*btn,QSpinBox*box,int k);

private:
    Ui::chooseTicketDialog *ui;
    int Row;
    int Col;
    int Day;

signals:
    void success(int r,int c,int d,int n,int count);
    void noTicket(int r,int c,int d,int n,int count);
    void fail();



private slots:
    void on_buy1_clicked();
    void on_buy2_clicked();
    void on_buy3_clicked();
};

#endif // CHOOSETICKETDIALOG_H

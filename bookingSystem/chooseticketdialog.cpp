#include "chooseticketdialog.h"
#include "ui_chooseticketdialog.h"

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

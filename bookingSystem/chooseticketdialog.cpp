#include "chooseticketdialog.h"
#include "ui_chooseticketdialog.h"

chooseTicketDialog::chooseTicketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseTicketDialog)
{
    ui->setupUi(this);
}

chooseTicketDialog::~chooseTicketDialog()
{
    delete ui;
}

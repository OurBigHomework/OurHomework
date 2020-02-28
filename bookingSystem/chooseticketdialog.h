#ifndef CHOOSETICKETDIALOG_H
#define CHOOSETICKETDIALOG_H

#include <QDialog>

namespace Ui {
class chooseTicketDialog;
}

class chooseTicketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chooseTicketDialog(QWidget *parent = nullptr);
    ~chooseTicketDialog();

private:
    Ui::chooseTicketDialog *ui;
};

#endif // CHOOSETICKETDIALOG_H

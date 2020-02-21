#ifndef LOGINPART_H
#define LOGINPART_H

#include <QMainWindow>

namespace Ui {
class loginPart;
}

class loginPart : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginPart(QWidget *parent = nullptr);
    ~loginPart();

private:
    Ui::loginPart *ui;
};

#endif // LOGINPART_H

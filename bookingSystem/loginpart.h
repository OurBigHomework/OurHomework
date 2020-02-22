#ifndef LOGINPART_H
#define LOGINPART_H

#include <QMainWindow>
#include<QPainter>
namespace Ui {
class loginPart;
}

class loginPart : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginPart(QWidget *parent = nullptr);
    ~loginPart();

protected:
    void paintEvent(QPaintEvent *event);


private:
    Ui::loginPart *ui;
};

#endif // LOGINPART_H

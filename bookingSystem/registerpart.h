#ifndef REGISTERPART_H
#define REGISTERPART_H

#include <QWidget>

namespace Ui {
class RegisterPart;
}

class RegisterPart : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterPart(QWidget *parent = nullptr);
    ~RegisterPart();

private:
    Ui::RegisterPart *ui;
};

#endif // REGISTERPART_H

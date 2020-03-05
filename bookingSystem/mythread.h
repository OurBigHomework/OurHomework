#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include<myexcel.h>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread();
    //void setNum(int num);
    void setPath(QString path);

signals:

    void isDone(QList<QList<QList<QVariant>>>&vars);
protected:
    void run() override;
private:
    //int num;
    QString path;
};

#endif // MYTHREAD_H

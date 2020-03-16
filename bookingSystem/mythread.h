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
    void setPath(QString path);//设置打开的excel的路径

signals:

    void isDone(QList<QList<QList<QVariant>>>&vars);//加载完成发送的信号
protected:
    void run() override;
private:
    //int num;
    QString path;//excel路径
};

#endif // MYTHREAD_H

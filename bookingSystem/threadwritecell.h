#ifndef THREADWRITECELL_H
#define THREADWRITECELL_H

#include <QThread>
#include "myexcel.h"
#include<QVector>
class threadWriteCell : public QThread
{
    Q_OBJECT
public:
    explicit threadWriteCell(QObject *parent = nullptr);
    void setPath(QString path);//设置excel路径
    void setInfo(QStringList &str,QVector<int>&row,QVector<int>&col,int& n);//设置所要修改的内容、行索引、列索引和所处的sheet界面

signals:
    void writeOk();//修改成功后发送信号
protected:
    void run() override;
private:
    QString path;
    QStringList str;
    QVector<int>row;
    QVector<int>col;
    int n;

};

#endif // THREADWRITECELL_H

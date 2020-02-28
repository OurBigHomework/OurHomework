#ifndef MYEXCEL_H
#define MYEXCEL_H
#include<QString>
#include<QVariant>
#include<QAxObject>
#include<QAxWidget>
#include <QObject>
class myExcel
{
 //Q_OBJECT
public:
    //explicit myExcel(QObject *parent = nullptr);
    QVector<QString>place;

    myExcel(QString path);
    myExcel();

    ~myExcel();
    QString getDate();   
    void setDate(QString d);
    void excelToQList(const QVariant &var,QList<QList<QVariant>> &res);
    void init();
    void setPath(QString path);
    QVariant readAll();
private:
    QString path;
    QString date;




};

#endif // MYEXCEL_H

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
    //QVector<QString>place;

    myExcel(QString path);
    myExcel();

    ~myExcel();
    //QString getDate();
    void writeCell(QStringList str,QVector<int>row,QVector<int>col,int n);//修改excel表中第n个表第row[i]+1行col[i]+1行的数据
    void setDate(QString d);
    void excelToQList(const QVariant &var,QList<QList<QVariant>> &res);//将excel中的数据转成二维数组存储在res中
    QVector<QString> getExcelVLine(int n,int vnum,QString begin,QString end);//获取第n个工作表第vnum列begin-》end间的数据
    QVector<QString>getExcelRLine(int n,int rnum,QString begin,QString end);//获取第n个工作表第rnum行begin-》end间的数据

    void setPath(QString path);//设定excel路径
    QVariant readAll(int num);//读取第num个工作表中的所有数据
    int sheetCount();//获得工作表数量
private:
    QString path;
    QString date;





};

#endif // MYEXCEL_H

#include "myexcel.h"
#include<QDebug>
#include<QDir>
myExcel::myExcel(QString path)
{
    this->path=path;

    this->date="";

}
myExcel::myExcel()
{
    date="";
    path="";



}
int myExcel::sheetCount()
{

    QAxObject excel("Excel.Application");
    excel.dynamicCall("setVisible(bool Visible)",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject*workbook=excel.querySubObject("ActiveWorkBook");
    QAxObject*worksheets=workbook->querySubObject("WorkSheets");
    int num=worksheets->property("Count").toInt();
    excel.dynamicCall("Quit(void)");
    return num;
}
QVector<QString> myExcel::getExcelVLine(int n,int vnum,QString begin,QString end)
{
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    QAxObject*worksheet = workbook->querySubObject("Worksheets(int)", n);
    QVariantList params;
    params <<begin<< end;
    QAxObject *cells = worksheet->querySubObject("Range(QVariant,QVariant)",params);
    QVariant var=cells->dynamicCall("Value");
    QVariantList mylist=var.toList();
    QVector<QString> vec;



    for(int i=0;i<mylist.size();i++)
    {

        vec.append(mylist[i].toList()[vnum].toString());

    }


    workbook->dynamicCall("Close(Boolean)",false);
    excel.dynamicCall("Quit(void)");
    return vec;
}
QVector<QString> myExcel::getExcelRLine(int n,int rnum,QString begin,QString end)
{
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    QAxObject*worksheet = workbook->querySubObject("Worksheets(int)", n);
    QVariantList params;
    params <<begin<< end;
    QAxObject *cells = worksheet->querySubObject("Range(QVariant,QVariant)",params);
    QVariant var=cells->dynamicCall("Value");
    QVariantList mylist=var.toList();
    QVector<QString> vec;
    for(int i=0;i<mylist[rnum].toList().size();i++)
    {
        vec.append(mylist[rnum].toList()[i].toString());


    }


    workbook->dynamicCall("Close(Boolean)",false);
    excel.dynamicCall("Quit(void)");
    return vec;
}

void myExcel::setPath(QString path)
{
    this->path=path;
}
QVariant myExcel::readAll(int num)
{
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    QAxObject* sheet = workbook->querySubObject("Worksheets(int)", num);

    QVariant var;
    if (sheet != NULL && ! sheet->isNull())
    {
        QAxObject *usedRange = sheet->querySubObject("UsedRange");
        if(NULL == usedRange || usedRange->isNull())
        {
            return var;
        }
        var = usedRange->dynamicCall("Value");
        delete usedRange;
    }
    workbook->dynamicCall("Close(Boolean)",false);
    excel.dynamicCall("Quit(void)");

    return var;
}
void myExcel::excelToQList(const QVariant &var, QList<QList<QVariant>> &res)
{


        QVariantList varRows = var.toList();

        if(varRows.isEmpty())
        {
            return;
        }
        const int rowCount = varRows.size();
        QVariantList rowData;
        for(int i=0;i<rowCount;++i)
        {
            rowData = varRows[i].toList();
            res.push_back(rowData);
        }

}
void myExcel::setDate(QString date)
{

    this->date=date;
}

void myExcel::writeCell(QStringList str, QVector<int>row, QVector<int>col,int n)
{
    QString str1="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QStringList strList;
    int m=0;
    for(int i=0;i<50;i++)
    {

        if(i<26)
        {
            strList.push_back(QString(str1[i]));
        }else
        {
            int k=i/26-1;
            if(m>=26)m=0;
            QString s=strList.at(k);
            //qDebug()<<"k:"<<k;
            strList.push_back(s.append(QString(str1[m])));
        }

    m++;
    }

    if((row.size()!=col.size())||(row.size()!=str.size()))
    {
        qDebug()<<"row!=col!=str";
        return;
    }
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    QAxObject*worksheet = workbook->querySubObject("Worksheets(int)", n+1);
    //qDebug()<<n;
    int s=row.size();
    for(int i=0;i<s;i++)
    {
        int c=col[i],r=row[i];
        QString a=strList[c]+QString::number(r+1);
        qDebug()<<"a:"<<a;
        QAxObject*write=worksheet->querySubObject("Range(Qvariant,QVariant)",a);
        write->dynamicCall("SetValue(const QVariant&)",QVariant(str.at(i)));
        delete write;
    }
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close(Boolean)",false);
    excel.dynamicCall("Quit(void)");
    qDebug()<<"write ok";

}
//QString myExcel::getDate()
//{
//   return "";
//}
myExcel::~myExcel()
{

}

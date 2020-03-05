#include "myexcel.h"
#include<QDebug>
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
//QString myExcel::getDate()
//{
//   return "";
//}
myExcel::~myExcel()
{

}

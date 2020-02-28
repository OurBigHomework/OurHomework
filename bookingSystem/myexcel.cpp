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
void myExcel::init()
{
        QAxObject excel("Excel.Application");
        excel.setProperty("Visible",false);
        QAxObject *workbooks = excel.querySubObject("WorkBooks");
       workbooks->dynamicCall("Open (const QString&)", QString("D:/OurHomework/bookingSystem/Data/myData.xlsx"));

        QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
        QAxObject*worksheet = workbook->querySubObject("Worksheets(int)", 1);
        QVariantList params;
        params <<"A1"<< "A34";
        QAxObject *cells = worksheet->querySubObject("Range(QVariant,QVariant)",params);
        QVariant var=cells->dynamicCall("Value");
        QVariantList mylist=var.toList();
        for(int i=0;i<mylist.size();i++)
        {
            place.append(mylist[i].toList()[0].toString());

        }

        workbook->dynamicCall("Close(Boolean)",false);
        excel.dynamicCall("Quit(void)");

}
void myExcel::setPath(QString path)
{
    this->path=path;
}
QVariant myExcel::readAll()
{
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    QAxObject* sheet = workbook->querySubObject("Worksheets(int)", 1);

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
QString myExcel::getDate()
{
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
   workbooks->dynamicCall("Open (const QString&)", QString(path));

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    QAxObject* sheet = workbook->querySubObject("Worksheets(int)", 2);
    QAxObject*var=sheet->querySubObject("Cells(int,int)",1,1);
    date=var->dynamicCall("Value").toString();
    workbook->dynamicCall("Close(Boolean)",false);
    excel.dynamicCall("Quit(void)");
    return date;
}
myExcel::~myExcel()
{

}

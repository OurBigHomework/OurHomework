#include "threadwritecell.h"
#include<QDebug>
#include <windows.h>
threadWriteCell::threadWriteCell(QObject *parent): QThread(parent)
{

    path="";
}
void threadWriteCell::setPath(QString path)
{
    this->path=path;
}
void threadWriteCell::setInfo(QStringList &str, QVector<int> &row, QVector<int> &col, int &n)
{
    this->str=str;
    this->row=row;
    this->col=col;
    this->n=n;
}
void threadWriteCell::run()
{
    if(path!="")
    {
        HRESULT r = OleInitialize(0);
        if (r != S_OK && r != S_FALSE)
        {
            qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);
        }
        myExcel*excel=new myExcel(path);
        excel->writeCell(str,row,col,n);
        OleUninitialize();
        emit writeOk();


     }


}

#include "mythread.h"
#include<QDebug>
#include <windows.h>
MyThread::MyThread(QObject *parent) : QThread(parent)
{

    path="";
}
MyThread::~MyThread()
{

}
void MyThread::run()
{

    if(path!="")
    {
        HRESULT r = OleInitialize(0);
        if (r != S_OK && r != S_FALSE)
        {
            qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);
        }

        myExcel*excel=new myExcel;
        excel->setPath(path);
        QList<QVariant> varList;
        QList<QList<QList<QVariant>>> mylist;
        for(int i=0;i<5;i++)
        {
            varList.push_back(excel->readAll(i+1));
            QList<QList<QVariant>> res;
            excel->excelToQList(varList[i],res);
            mylist.push_back(res);
            //qDebug()<<mylist[i][0][0].toString();
        }
        qDebug()<<"ok";

        OleUninitialize();
        emit isDone(mylist);
    }


}

void MyThread::setPath(QString path)
{
    this->path=path;
}

//void MyThread::setNum(int num)
//{
//    this->num=num;
//}

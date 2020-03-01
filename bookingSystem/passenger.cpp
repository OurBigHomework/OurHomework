#include "passenger.h"

Passenger::Passenger()
{
    this->username="";
    this->password="";
    this->phone="";
    this->birthday="";
    this->name="";
    this->sex="";
    this->index=0;
}
Passenger::Passenger(QString username,QString password,QString phone,QString birthday,QString name,QString sex,int index)
{
    this->username=username;
    this->password=password;
    this->phone=phone;
    this->birthday=birthday;
    this->name=name;
    this->sex=sex;
    this->index=index;

}
void Passenger::setSex(QString sex)
{
    this->sex=sex;
}
void Passenger::setName(QString name)
{
    this->name=name;
}
void Passenger::setPhone(QString phone)
{
    this->phone=phone;
}
void Passenger::setBirthday(QString birthday)
{
    this->birthday=birthday;
}
void Passenger::setPassword(QString pword)
{
    password=pword;
}
void Passenger::setUsername(QString uname)
{
    this->username=uname;
}
void Passenger::setIndex(int index)
{
    this->index=index;
}

QString Passenger::getSex()
{
    return sex;
}
QString Passenger::getName()
{
    return name;
}
QString Passenger::getPhone()
{
    return phone;
}
QString Passenger::getBirthday()
{
    return birthday;
}
QString Passenger::getPassword()
{
    return password;
}
QString Passenger::getUsername()
{
    return username;
}
int Passenger::getIndex()
{
    return index;
}

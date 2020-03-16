#ifndef PASSENGER_H
#define PASSENGER_H

#include<QString>
class Passenger
{
public:
    Passenger();
    Passenger(QString username,QString password,QString phone,QString birthday,QString name,QString sex,int index);
    void setUsername(QString uname);
    void setPassword(QString pword);
    void setSex(QString sex);
    void setPhone(QString phone);
    void setBirthday(QString birthday);
    void setName(QString name);
    void setIndex(int index);//乘客索引
    QString getUsername();
    QString getPassword();
    QString getSex();
    QString getPhone();
    QString getBirthday();
    QString getName();
    int getIndex();


private:
    QString username;
    QString password;
    QString sex;
    QString phone;
    QString birthday;
    QString name;
    int index;

};

#endif // PASSENGER_H
